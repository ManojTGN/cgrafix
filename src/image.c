#include "image.h"

static int IMAGE_ID;
grafixImage _IMAGES[MAX_IMAGE];

int createGrafixImage(grafixImage *image, const char* filePath, int fileType){
    image->_isInit = 0;
    image->id = IMAGE_ID++;
    image->fileType = fileType;

    FILE *image_file;
    image_file = fopen(filePath, "rb");
    if (image_file == NULL){
        IMAGE_ID--;
        setGrafixError("grafixError:Unable To Load Image;Reason:No File Found");
        return 0;
    }

    image->height = 0;
    image->width = 0;
    fseek(image_file, 0x0012, SEEK_SET);
    fread(&(image->width), sizeof(image->width), 1, image_file);
    fread(&(image->height), sizeof(image->height), 1, image_file);
    fseek(image_file, 0x001C, SEEK_SET);
    fread(&(image->bitCount), sizeof(image->bitCount), 1, image_file);
    int pixelSize = (image->bitCount == 24) ? 3 : 4;
    
    image->_frame = (unsigned char*) malloc(image->width * image->height * 3);
    if(image->_frame == NULL){
        IMAGE_ID--;
        fclose(image_file);
        setGrafixError("grafixError:Unable To Load Image;Reason:No Memory Available");
        return 0;
    }

    int index = 0;unsigned char pixel[4];
    fseek(image_file, 54, SEEK_SET);
    for (int y = image->height-1; y >= 0 ; y--) {
    for (int x = 0; x < image->width; x++) {
        
        if(fread(pixel, sizeof(unsigned char), pixelSize, image_file) != pixelSize) break;

        index = ( x + y*image->width ) *3;
        image->_frame[ index+0 ] = pixel[0];
        image->_frame[ index+1 ] = pixel[1];
        image->_frame[ index+2 ] = pixel[2];
        //pixel[3]  if(bitCount == 24)
        
    }
    }

    fclose(image_file);
    image->_isInit = 1;
    
    return 1;
}

void drawGrafixImage(grafixWindow window, grafixImage image, int x, int y){

    if(WINDOWS[window.id] == NULL|| window.isDead) return;

    if(image._isInit != 1){
        setGrafixError("grafixError:Unable To Draw Image;Reason:Image Is Not Initiated;");
        return;
    }

    int index;int imageIndex;
    for (int _x = x; _x < x+image.width; _x++) {
    for (int _y = y; _y < y+image.height ; _y++) {
        
        index = (_x + _y * window.width) * 3;
        imageIndex = ( (_x-x) + (_y-y)*image.width) * 3;
        BUFFERS[window.id].frameBuffer[index] = image._frame[imageIndex];
        BUFFERS[window.id].frameBuffer[index+1] = image._frame[imageIndex+1];
        BUFFERS[window.id].frameBuffer[index+2] = image._frame[imageIndex+2];

    }
    }

}