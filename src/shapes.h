
#ifndef SHAPES_H
#define SHAPES_H

#include "grafix.h"

#define FM_EMPTY 0
#define FM_OUTLINE 1
#define FM_FILL 2

void _setPixel(grafixWindow window, int x, int y, grafixColor color);
void drawGrafixLine(grafixWindow window, int x1, int y1, int x2, int y2, grafixColor color);

void drawGrafixRect(grafixWindow window, int x, int y, int width, int height, grafixColor color, int fillMode, int borderWidth);
void drawGrafixCircle(grafixWindow window, int x, int y, int radius, grafixColor color, int fillMode, int borderWidth);

#endif /* SHAPES_H */