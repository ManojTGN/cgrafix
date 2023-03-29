#include "event.h"
#include "grafix.h"

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    int id;
    for(id = 0; id < MAX_WINDOW; id++){
        if(WINDOWS[id] != NULL && WINDOWS[id]->_hwnd == hwnd) break;
    }

    if(id >= MAX_WINDOW) return DefWindowProc(hwnd, uMsg, wParam, lParam);

    switch (uMsg){
    case WM_DESTROY:
    {
        WINDOWS[id]->isDead = 1;
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

void manageGrafixEvent(grafixWindow window){
    
    MSG msg = { };
    while(PeekMessage(&msg, window._hwnd, 0, 0, PM_REMOVE) > 0){
        
        if (msg.message == WM_DESTROY)
        {
            printf("QUIT TRIGGERED");
            return;
        }

        if (!TranslateAccelerator(window._hwnd, 0, &msg)){
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }

    }
    
}