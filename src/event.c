#include "event.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    int id;
    for(id = 0; id < MAX_WINDOW; id++){
        if(WINDOWS[id] != NULL && WINDOWS[id]->_hwnd == hwnd) break;
    }

    if(id >= MAX_WINDOW) 
        return DefWindowProc(hwnd, uMsg, wParam, lParam);

    if(WINDOWS[id]->_eventLength+1 < MAX_EVENTS){
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].id = id;
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].type = uMsg;
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].wkeyCode = wParam;
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].lkeyCode = lParam;

        if(uMsg == WM_MOUSEMOVE || uMsg == WM_NCMOUSEMOVE){
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].cursorX = (int)(lParam) & 0xFFFF; 
        WINDOWS[id]->_events[ WINDOWS[id]->_eventLength ].cursorY = ((int)(lParam) >> 16) & 0xFFFF;
        }
        
        WINDOWS[id]->_eventLength++;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

void manageGrafixEvent(grafixWindow window, grafixEvent** event, int* size){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;
    
    WINDOWS[window.id]->_eventLength = 0;

    MSG msg = { };
    while(PeekMessage(&msg, window._hwnd, 0, 0, PM_REMOVE) > 0){

        if (!TranslateAccelerator(window._hwnd, 0, &msg)){
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }

    }

    *size = WINDOWS[window.id]->_eventLength;
    *event = WINDOWS[window.id]->_events;
    
}