#include "shapes.h"


void _setPixel(grafixWindow window, int x, int y, grafixColor color){
    
    int index = (x + y * window.width) * 3;
    BUFFERS[window.id].frameBuffer[index] = color.blue;
    BUFFERS[window.id].frameBuffer[index + 1] = color.green;
    BUFFERS[window.id].frameBuffer[index + 2] = color.red;

}

void drawGrafixLine(grafixWindow window, int x0, int y0, int x1, int y1, grafixColor color){

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        _setPixel(window, x0, y0, color);
        int e2 = err << 1;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    _setPixel(window, x1, y1, color);

}

void drawGrafixRect(grafixWindow window, int x, int y, int width, int height, grafixColor color){
    drawGrafixLine(window,x,y,x+width,y,color);
    drawGrafixLine(window,x+width,y,x+width,y+height,color);
    drawGrafixLine(window,x+width,y+height,x,y+height,color);
    drawGrafixLine(window,x,y+height,x,y,color);
}

void drawGrafixCircle(grafixWindow window, int xc, int yc, int r, grafixColor color){
    
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        _setPixel(window, xc + x, yc + y, color);
        _setPixel(window, xc + y, yc + x, color);
        _setPixel(window, xc - x, yc + y, color);
        _setPixel(window, xc - y, yc + x, color);
        _setPixel(window, xc + x, yc - y, color);
        _setPixel(window, xc + y, yc - x, color);
        _setPixel(window, xc - x, yc - y, color);
        _setPixel(window, xc - y, yc - x, color);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }

}