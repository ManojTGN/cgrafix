
#include "grafix.h"
#include "time.h"
#include <time.h>

int ID = 0;
grafixWindow WINDOWS[MAX_WINDOW];
_grafixFrameBuffer BUFFERS[MAX_WINDOW];

void grafixInit(){

    printf("\nInitiated Grafix!\n");

}

grafixWindow createGrafixWindow(int WIDTH, int HEIGHT, char* NAME){
    
    grafixWindow window;
    window.id = ID++;
    window.height = HEIGHT;
    window.width = WIDTH;

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "GrafixClass_"+window.id;
    RegisterClass(&wc);

    window._wc = wc;
    window._hwnd = CreateWindow("GrafixClass_"+window.id, NAME, WS_OVERLAPPEDWINDOW, 100, 100, WIDTH, HEIGHT, NULL, NULL, GetModuleHandle(NULL), NULL);
    window._hdc = GetDC(window._hwnd);
    
    WINDOWS[window.id] = window;

    _grafixFrameBuffer frame;
    frame.id = window.id;
    frame.frameBuffer = (unsigned char*)malloc(WIDTH * HEIGHT * 3);

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
    time.id = window.id;
    time._tps = 0;
    time._limitTps = 0;
    time._msPerFrame = 0;
    time._waitCounter = 0;
    time._startCounter = clock();
    
    // QueryPerformanceCounter(&TIMES[time.id]._startCounter);
    // QueryPerformanceFrequency(&TIMES[time.id]._frequency);

    TIMES[time.id] = time;


    return window;

}

void endGrafixWindow(grafixWindow window){

    ReleaseDC(window._hwnd, window._hdc);
    free(BUFFERS[window.id].frameBuffer);
    
}

void showGrafixWindow(grafixWindow window){

    ShowWindow(window._hwnd, SW_SHOWDEFAULT);

}

void hideGrafixWindow(grafixWindow window){
    
    ShowWindow(window._hwnd, SW_HIDE);

}

void fillGrafixWindow(grafixWindow window, grafixColor color){

    for(int i = 0; i < window.height * window.width * 3; i+=3){
        BUFFERS[window.id].frameBuffer[i] = color.green;
        BUFFERS[window.id].frameBuffer[i + 1] = color.blue;
        BUFFERS[window.id].frameBuffer[i + 2] = color.red;
    }
    
}

void updateGrafixWindow(grafixWindow window){

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = window.width;
    bmi.bmiHeader.biHeight = -window.height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    BUFFERS[window.id].bmi = bmi;

    SetDIBitsToDevice(WINDOWS[window.id]._hdc, 0, 0, window.width, window.height, 0, 0, 0, window.height, BUFFERS[window.id].frameBuffer, &BUFFERS[window.id].bmi, DIB_RGB_COLORS);

}