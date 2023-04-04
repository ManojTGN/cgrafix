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

    int text_length = strlen(text);
    for (int i = 0; i < text_length; ++i) {
        if (FT_Load_Char(font.face, text[i], FT_LOAD_RENDER)) {
            continue;
        }

        pen.x += slot->advance.x >> 6;
        pen.y += slot->advance.y >> 6;

        if (pen.x > width) {
            width = pen.x;
        }
        if (pen.y > height) {
            height = pen.y;
        }
    }

    unsigned char* buffer = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    if (!buffer) {
        setGrafixError("grafixError:Unable To Create Buffer;reason:No Memory Available For Buffer;");
        return;
    }
    memset(buffer, 0, width * height * sizeof(unsigned char));

    pen.x = 0;
    pen.y = 0;
    for (int i = 0; i < text_length; ++i) {
        if (FT_Load_Char(font.face, text[i], FT_LOAD_RENDER)) {
            continue;
        }

        FT_Bitmap bitmap = slot->bitmap;
        for (int _y = 0; _y < bitmap.rows; ++_y) {
            for (int _x = 0; _x < bitmap.width; ++_x) {
                _setPixel(window,x+_x+pen.x,y+_y+pen.y,(grafixColor){bitmap.buffer[y * bitmap.width + x],0,0});
                // BUFFERS[window.id].frameBuffer[(pen.y + y) * width + pen.x + x] = bitmap.buffer[(y * bitmap.width + x) ];
                // BUFFERS[window.id].frameBuffer[((pen.y + y) * width + pen.x + x)+1] = bitmap.buffer[(y * bitmap.width + x)+1 ];
                // BUFFERS[window.id].frameBuffer[((pen.y + y) * width + pen.x + x)+2] = bitmap.buffer[(y * bitmap.width + x)+2 ];
            }
        }

        pen.x += slot->advance.x >> 6;
        pen.y += slot->advance.y >> 6;
    }

}
