#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

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
static char grafixError[100];
static int grafixInitiated;
extern grafixWindow* WINDOWS[MAX_WINDOW];
extern _grafixFrameBuffer BUFFERS[MAX_WINDOW];

void grafixInit();
int isGrafixInit();

const char* getGrafixError();
void setGrafixError(char* errorMsg);
void clearGrafixError();

void showGrafixWindow(grafixWindow window);
void hideGrafixWindow(grafixWindow window);
void fillGrafixWindow(grafixWindow window, grafixColor color);

void updateGrafixWindow(grafixWindow window);
int createGrafixWindow(grafixWindow* window, int width, int height, char* name);


int isGrafixWindowEnded(grafixWindow window);
void endGrafixWindow(grafixWindow window);
grafixWindow* getGrafixWindow(int id);

#endif /* GRAFIX_H */