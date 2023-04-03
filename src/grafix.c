#include "grafix.h"

static int WINDOW_ID = 0;
static char grafixError[100];
static int grafixInitiated = 0;
grafixWindow* WINDOWS[MAX_WINDOW];
_grafixFrameBuffer BUFFERS[MAX_WINDOW];

void grafixInit(){
    if(grafixInitiated) return;

    WINDOW_ID = 0;
    grafixInitiated = 1;
    printf("Initiated Grafix!\n");
    
}

int isGrafixInit(){

    return grafixInitiated;

}


const char* getGrafixError(){

    const char* error = grafixError;
    return error;

}

void setGrafixError(char* errorMsg){

    strcpy(grafixError,errorMsg);

}

void clearGrafixError(){

    strcpy(grafixError,"");

}


void showGrafixWindow(grafixWindow window){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    ShowWindow(window._hwnd, SW_SHOWDEFAULT);

}

void hideGrafixWindow(grafixWindow window){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;
    
    ShowWindow(window._hwnd, SW_HIDE);

}

void fillGrafixWindow(grafixWindow window, grafixColor color){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    for(int i = 0; i < window.height * window.width * 3; i+=3){
        BUFFERS[window.id].frameBuffer[i] = color.green;
        BUFFERS[window.id].frameBuffer[i + 1] = color.blue;
        BUFFERS[window.id].frameBuffer[i + 2] = color.red;
    }
    
}


void updateGrafixWindow(grafixWindow window){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = window.width;
    bmi.bmiHeader.biHeight = -window.height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    BUFFERS[window.id].bmi = bmi;

    SetDIBitsToDevice(WINDOWS[window.id]->_hdc, 0, 0, window.width, window.height, 0, 0, 0, window.height, BUFFERS[window.id].frameBuffer, &BUFFERS[window.id].bmi, DIB_RGB_COLORS);
    
}

int createGrafixWindow(grafixWindow* window, int WIDTH, int HEIGHT, char* NAME){
    if(WINDOW_ID == MAX_WINDOW){
        strcpy(grafixError, "grafixError:Unable To CreateWindow;reason:Window Limit Reached Maximum(10);");
        return 0;
    }

    window->id = WINDOW_ID++;
    window->height = HEIGHT;
    window->width = WIDTH;
    window->_eventLength = 0;

    char name[15] = "GrafixClass_";
    name[12] = '0'+window->id;
    window->_cname = name;

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc; // WindowProc; DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = (*window)._cname;

    window->_wc = wc;
    RegisterClass( &(window->_wc) );

    window->_hwnd = CreateWindow((*window)._cname, NAME, WS_OVERLAPPEDWINDOW, 0, 0, WIDTH, HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if(window->_hwnd == NULL){
        WINDOW_ID--;
        window = NULL;
        strcpy(grafixError, "grafixError:Unable To CreateWindow;reason:No Memory Available For Window;");
        return 0;
    }
    
    window->_hdc = GetDC(window->_hwnd);

    window->isDead = 0;
    WINDOWS[window->id] = window;

    _grafixFrameBuffer frame;
    frame.id = window->id;
    frame.frameBuffer = (unsigned char*)malloc(WIDTH * HEIGHT * 3);
    if(frame.frameBuffer == NULL){
        WINDOW_ID--;
        free(WINDOWS[window->id]);window = NULL;
        strcpy(grafixError, "grafixError:Unable To CreateWindow;reason:No Memory Available For FrameBuffer;");
        return 0;
    }

    BUFFERS[frame.id] = frame;


    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = WIDTH;
    bmi.bmiHeader.biHeight = -HEIGHT;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    BUFFERS[frame.id].bmi = bmi;


    _grafixTIME time;
    time.id = window->id;
    time._tps = 0;
    time._limitTps = 0;
    time._msPerFrame = 0;
    time._waitCounter = 0;
    time._startCounter = clock();
    
    // QueryPerformanceCounter(&TIMES[time.id]._startCounter);
    // QueryPerformanceFrequency(&TIMES[time.id]._frequency);

    TIMES[time.id] = time;

}


int isGrafixWindowEnded(grafixWindow window){

    return (WINDOWS[window.id] == NULL || window.isDead);

}

void endGrafixWindow(grafixWindow window){
    if( WINDOWS[window.id] == NULL || window.isDead ) return;

    ReleaseDC(window._hwnd, window._hdc);    
    free(BUFFERS[window.id].frameBuffer);

    DestroyWindow(window._hwnd);
    
    WINDOWS[window.id] = NULL;
    window.isDead = 1;
    window.height = -1;
    window.width = -1;
    window._eventLength = -1;
    window._hdc = NULL;
    window._hwnd = NULL;
    window._cname = NULL;

    PostQuitMessage(0);
}

grafixWindow* getGrafixWindow(int id){

    return WINDOWS[id];

}