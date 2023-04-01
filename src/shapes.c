#include "shapes.h"

void _setPixel(grafixWindow window, int x, int y, grafixColor color){
    if(x >= window.width || y >= window.height || x < 0 || y < 0) return;

    int index = (x + y * window.width) * 3;
    BUFFERS[window.id].frameBuffer[index] = color.blue;
    BUFFERS[window.id].frameBuffer[index + 1] = color.green;
    BUFFERS[window.id].frameBuffer[index + 2] = color.red;

}

void drawGrafixLine(grafixWindow window, int x0, int y0, int x1, int y1, grafixColor color){
    if( window.isDead ) return;

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
    if( window.isDead || fillMode == FM_EMPTY) return;

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
    if( window.isDead || fillMode == FM_EMPTY) return;

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

void drawGrafixImage(grafixWindow window, char* imagePath, int x, int y, int width, int height){
    
    // HBITMAP hBitmap = LoadBitmapFromFile(imagePath,width,height);
    // if (!hBitmap) {
    //     printf("E_0 ");
    //     return;
    // }

    // FILE* fp = _wfopen(hBitmap, _T("rb"));
    // if (!fp){
    //     printf("E_1 ");
    //     return;
    // }

    // fseek(fp, 0, SEEK_END);
    // int fileSize = ftell(fp);
    // fseek(fp, 0, SEEK_SET);
    // unsigned char* fileData = (unsigned char*)malloc(fileSize);

    // if (!fileData) {
    //     printf("E_2 ");
    //     fclose(fp);
    //     return;
    // }

    // fread(fileData, 1, fileSize, fp);
    // fclose(fp);

    // BITMAPFILEHEADER* bmfh = (BITMAPFILEHEADER*)fileData;
    // BITMAPINFOHEADER* bmih = (BITMAPINFOHEADER*)(fileData + sizeof(BITMAPFILEHEADER));

    // if (bmfh->bfType != 'MB' || bmih->biSize != sizeof(BITMAPINFOHEADER)) {
    //     printf("E_3 ");
    //     free(fileData);
    //     return;
    // }

    // unsigned char* imageData = fileData + bmfh->bfOffBits;
    // int imageWidth = bmih->biWidth;
    // int imageHeight = bmih->biHeight;
    // int imageDepth = bmih->biBitCount / 8;

    // void* bits;
    // BITMAPINFO bmi = { sizeof(BITMAPINFOHEADER), imageWidth, imageHeight, 1, 24, BI_RGB };
    // HBITMAP _hBitmap = CreateDIBSection(window._hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);


    // unsigned char* data = (unsigned char*)bits;
    // for (int y = 0; y < imageHeight; y++) {
    //     for (int x = 0; x < imageWidth; x++) {
    //         data[(y * imageWidth + x) * 3 + 0] = imageData[(y * imageWidth + x) * imageDepth + 2]; // blue
    //         data[(y * imageWidth + x) * 3 + 1] = imageData[(y * imageWidth + x) * imageDepth + 1]; // green
    //         data[(y * imageWidth + x) * 3 + 2] = imageData[(y * imageWidth + x) * imageDepth + 0]; // red
    //     }
    // }

    // SetDIBitsToDevice(window._hdc, x, y, width, height, 0, 0, 0, imageHeight, bits, &bmi, DIB_RGB_COLORS);

    // DeleteObject(hBitmap);
    // DeleteObject(_hBitmap);
    // free(fileData);

}

void drawGrafixText(grafixWindow window, int x, int y, char* text, grafixColor color){
    
    // HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
    //     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    //     DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    // HFONT hOldFont = (HFONT)SelectObject(window._hdc, hFont);

    // SetTextColor(window._hdc, RGB(color.red, color.green, color.blue));
    // SetBkColor(window._hdc, TRANSPARENT);
    
    // TextOut(window._hdc, x, y, text, strlen(text));


    // SelectObject(window._hdc, hOldFont);
    // DeleteObject(hFont);


    HDC hdc = CreateCompatibleDC(NULL);

    SIZE size;
    GetTextExtentPoint32(hdc, text, strlen(text), &size);

    RECT rc = { 0, 0, size.cx, size.cy };
    DrawText(hdc, text, -1, &rc, DT_CALCRECT);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = size.cx;
    bmi.bmiHeader.biHeight = size.cy;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;
    unsigned char* pixels = (unsigned char*)malloc(bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * 3);
    pixels[0];

    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
    HGDIOBJ hOldBitmap = SelectObject(hdc, hBitmap);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(color.red, color.green, color.blue));
    DrawText(hdc, text, -1, &rc, DT_LEFT | DT_TOP);

    int index = 0;int pindex = 0;
    for(int i = x; i < x+size.cx; i++){
    for(int j = y; j < y+size.cy; j++){
        index = (i + j * window.width) * 3;
        pindex = ( (i-x) + (j-y) * size.cx) * 3;
        //printf("(%d %d) %d %d\n",index, pindex,size.cx,size.cy);
        BUFFERS[window.id].frameBuffer[index] = pixels[pindex];
        BUFFERS[window.id].frameBuffer[index + 1] = pixels[pindex + 1];
        BUFFERS[window.id].frameBuffer[index + 2] = pixels[pindex + 2];
    }
    }

    SelectObject(hdc, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hdc);

}
