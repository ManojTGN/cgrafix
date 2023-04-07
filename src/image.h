
#ifndef IMAGE_H
#define IMAGE_H

#include "grafix.h"

#define M_PI 3.14159265358979323846

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
void rotateGrafixImage(grafixImage *image, float angle);

#endif /* IMAGE_H */