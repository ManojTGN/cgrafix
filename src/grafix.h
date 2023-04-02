#include <windows.h>
#include <stdio.h>

#include "shapes.h"
#include "time.h"
#include "event.h"

#ifndef GRAFIX_H
#define GRAFIX_H

#define MAX_WINDOW 10

typedef struct COLOR{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} grafixColor;

typedef struct WINDOW{
    int id;
    int height;
    int width;
    int isDead;

    HDC _hdc;
    HWND _hwnd;
    char* _cname;
    WNDCLASS _wc;
} grafixWindow;

typedef struct FRAME{
    int id;
    unsigned char* frameBuffer;
    BITMAPINFO bmi;
} _grafixFrameBuffer;

static int ID;
extern grafixWindow* WINDOWS[MAX_WINDOW];
extern _grafixFrameBuffer BUFFERS[MAX_WINDOW];

void grafixInit();

void showGrafixWindow(grafixWindow);
void hideGrafixWindow(grafixWindow);
void fillGrafixWindow(grafixWindow, grafixColor);

void updateGrafixWindow(grafixWindow);
int createGrafixWindow(grafixWindow*, int, int, char*);

int isGrafixWindowEnded(grafixWindow);
void endGrafixWindow(grafixWindow);


#endif /* GRAFIX_H */