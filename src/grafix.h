#include <windows.h>
#include <stdio.h>

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

    HDC _hdc;
    HWND _hwnd;
    WNDCLASS _wc;
} grafixWindow;

typedef struct FRAME{
    int id;
    unsigned char* frameBuffer;
    BITMAPINFO bmi;
} _grafixFrameBuffer;


extern _grafixFrameBuffer BUFFERS[MAX_WINDOW];

//from shapes.h (will be removed after solving the implicit warning)
void drawGrafixLine(grafixWindow, int, int, int, int, grafixColor);
void drawGrafixRect(grafixWindow, int, int, int, int, grafixColor);
void drawGrafixCircle(grafixWindow, int, int, int, grafixColor);


void grafixInit();

void showGrafixWindow(grafixWindow);
void hideGrafixWindow(grafixWindow);
void fillGrafixWindow(grafixWindow, grafixColor);

void updateGrafixWindow(grafixWindow);
grafixWindow createGrafixWindow(int, int, char*);
void endGrafixWindow(grafixWindow);

#endif /* GRAFIX_H */