#ifndef FONT_H
#define FONT_H

#include "grafix.h"

typedef struct FONT{
    char* directory;
    int fontSize;
    FT_Face face;
    FT_GlyphSlot slot;
}grafixFont;

int createGrafixFont(grafixFont *font, char* directory ,int fontSize);
void drawGrafixText(grafixWindow window, grafixFont font, int x, int y, char* text, grafixColor color);


#endif /* FONT_H */