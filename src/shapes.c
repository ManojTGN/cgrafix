#include "shapes.h"

void _setPixel(grafixWindow window, int x, int y, grafixColor color){
    if(WINDOWS[window.id] == NULL|| window.isDead  || x >= window.width || y >= window.height || x < 0 || y < 0) return;

    int index = (x + y * window.width) * 3;
    BUFFERS[window.id].frameBuffer[index] = color.blue;
    BUFFERS[window.id].frameBuffer[index + 1] = color.green;
    BUFFERS[window.id].frameBuffer[index + 2] = color.red;

}

void drawGrafixLine(grafixWindow window, int x0, int y0, int x1, int y1, grafixColor color){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

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

void drawGrafixRect(grafixWindow window, int x, int y, int width, int height, grafixColor color, int fillMode, int owidth){
    if( WINDOWS[window.id] == NULL|| window.isDead || fillMode == FM_EMPTY) return;

    if(x >= window.width || y >= window.height || x < 0 || y < 0) return;

    width = x+width >= window.width? window.width - x : width;
    height = y+height >= window.height? window.height - y : height;
    
    if(fillMode == FM_OUTLINE){
        for(int w = owidth; w >= -owidth; w--){
            drawGrafixLine(window,x-w,y-w,x+width+w,y-w,color);
            drawGrafixLine(window,x+width+w,y-w,x+width+w,y+height+w,color);
            drawGrafixLine(window,x+width+w,y+height+w,x-w,y+height+w,color);
            drawGrafixLine(window,x-w,y+height+w,x-w,y-w,color);
        }

        return;
    }

    if(fillMode == FM_FILL){
        for(int _y = y-owidth; _y < y+height+owidth; _y++){
            drawGrafixLine(window,x-owidth,_y,x+width+owidth,_y,color);
        }

        return;
    }

}

void drawGrafixCircle(grafixWindow window, int xc, int yc, int r, grafixColor color, int fillMode, int owidth){
    if( WINDOWS[window.id] == NULL|| window.isDead || fillMode == FM_EMPTY) return;

    int x = 0;
    int y = r;
    int d = 1 - r;

    if(fillMode == FM_OUTLINE){
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

        if(owidth == 0) return;
        for(int w = owidth; w >= -owidth; w--){
            drawGrafixCircle( window, xc, yc, r+w, color, fillMode, 0);
        }

        return;
    }

    if(fillMode == FM_FILL){
        int centerX = xc, centerY = yc;
        x = r, y = 0, d = 0;

        while (x >= y) {
            for (int i = centerX - x; i <= centerX + x; i++) {
                _setPixel(window, i, centerY + y, color);
                _setPixel(window, i, centerY - y, color);
            }
            for (int i = centerX - y; i <= centerX + y; i++) {
                _setPixel(window, i, centerY + x, color);
                _setPixel(window, i, centerY - x, color);
            }

            if (d <= 0) {
                y++;
                d += 2*y + 1;
            }

            if (d > 0) {
                x--;
                d -= 2*x + 1;
            }
        }

        return;
    }

}
