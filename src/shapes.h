#include <windows.h>

#ifndef SHAPES_H
#define SHAPES_H

#include "grafix.h"

#define FM_EMPTY 0
#define FM_OUTLINE 1
#define FM_FILL 2

void _setPixel(grafixWindow, int, int, grafixColor);
void drawGrafixLine(grafixWindow, int, int, int, int, grafixColor color);

void drawGrafixRect(grafixWindow, int, int, int, int, grafixColor, int, int);
void drawGrafixCircle(grafixWindow, int, int, int, grafixColor, int, int);

//I haven't created a seperate header file
void drawGrafixImage(grafixWindow,const char*, int, int);
void drawGrafixText(grafixWindow, int, int, char*, int, grafixColor);

#endif /* SHAPES_H */