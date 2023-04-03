
#ifndef EVENT_H
#define EVENT_H

#include "grafix.h"
#define MAX_EVENTS 20

// typedef struct EVENT{

//     int id;
//     unsigned int type;
//     unsigned long keyCode;

// }grafixEvent;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void manageGrafixEvent(grafixWindow window, grafixEvent** event, int* size);

#endif /* EVENT_H */