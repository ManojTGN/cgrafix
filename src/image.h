
#ifndef IMAGE_H
#define IMAGE_H

#include "grafix.h"

#define MAX_IMAGE 100

#define FT_BMP 0
#define FT_PNG 1
#define FT_JPG 2

typedef struct IMAGE {

    char* filePath;
    int fileType;
    int bitCount;

    int height;
    int width;
    int x;
    int y;

    int _isInit;
    unsigned char* _frame;

} grafixImage;


int createGrafixImage(grafixImage *image,  const char* filePath, int fileType);
void drawGrafixImage(grafixWindow window, grafixImage image, int x, int y);

#endif /* IMAGE_H */