#ifndef _DEPENDENCIES_H_
#define _DEPENDENCIES_H_

#include <stdlib.h>
#include <windows.h>
#include <windowsX.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#endif /* _DEPENDENCIES_H_ */

#ifndef _GRAFIX_DEPENDENCIES_H_
#define _GRAFIX_DEPENDENCIES_H_

#include "shapes.h"
#include "event.h"
#include "time.h"
#include "image.h"

#endif /* _GRAFIX_DEPENDENCIES_H_ */

#ifndef GRAFIX_H
#define GRAFIX_H

#define MAX_WINDOW 10
//todo: will be removed {
#define MAX_EVENTS 20
typedef struct EVENT{

    int id;
    unsigned int type;
    unsigned long wkeyCode;
    unsigned long lkeyCode;

    int cursorX;
    int cursorY;

}grafixEvent;
// }

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

    grafixEvent _events[MAX_EVENTS];
    int _eventLength;
} grafixWindow;

typedef struct FRAME{
    int id;
    unsigned char* frameBuffer;
    BITMAPINFO bmi;
} _grafixFrameBuffer;

static int WINDOW_ID;
static int grafixInitiated;
static char grafixError[100];
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