#include <windows.h>

#ifndef SHAPES_H
#define SHAPES_H

#include "grafix.h"

void _setPixel(grafixWindow, int, int, grafixColor);
void drawGrafixLine(grafixWindow, int, int, int, int, grafixColor color);

void drawGrafixRect(grafixWindow, int, int, int, int, grafixColor);
void drawGrafixCircle(grafixWindow, int, int, int, grafixColor);

#endif /* SHAPES_H */