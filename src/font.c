#include "font.h"

int createGrafixFont(grafixFont *font, char* directory ,int fontSize){

    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        setGrafixError("grafixError:Unable To Load Library;reason:Can't Init FreeType;");
        return 0;
    }

    if (FT_New_Face(library, directory, 0, &font->face)) {
        setGrafixError("grafixError:Unable To Load Face;reason:unknow;");
        return 0;
    }

    font->fontSize = fontSize;
    font->directory = directory;
    font->slot = font->face->glyph;

    return 1;
}


void drawGrafixText(grafixWindow window, grafixFont font, int x, int y, char* text, grafixColor color){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    if (FT_Set_Pixel_Sizes(font.face, 0, font.fontSize)) {
        setGrafixError("grafixError:Unable To Set FontSize;reason:unknow;");
        return;
    }

    int width = 0, height = 0;
    FT_GlyphSlot slot = font.face->glyph;
    FT_Vector pen = {0, 0};

    pen.x = 0;
    pen.y = 0;
    for (int i = 0; i < strlen(text); ++i) {
        if (FT_Load_Char(font.face, text[i], FT_LOAD_RENDER)) {
            continue;
        }

        FT_Bitmap bitmap = slot->bitmap;
        for (int _y = 0; _y < bitmap.rows; ++_y) {
            for (int _x = 0; _x < bitmap.width; ++_x) {
                _setPixel(window,x+_x+pen.x,y+_y+pen.y,(grafixColor){bitmap.buffer[_y * bitmap.width + _x],bitmap.buffer[_y * bitmap.width + _x],bitmap.buffer[_y * bitmap.width + _x]});
            }
        }

        pen.x += slot->advance.x >> 6;
        pen.y += slot->advance.y >> 6;
    }

}
