#include "image.h"

int createGrafixImage(grafixImage *image, const char* filePath, int fileType){
    image->_isInit = 0;
    image->fileType = fileType;

    FILE *image_file;
    image_file = fopen(filePath, "rb");
    if (image_file == NULL){
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
        
        if(_x < 0 || _y < 0 || _x >= window.width || y >= window.height) continue;

        index = (_x + _y * window.width) * 3;
        imageIndex = ( (_x-x) + (_y-y)*image.width) * 3;
        BUFFERS[window.id].frameBuffer[index] = image._frame[imageIndex];
        BUFFERS[window.id].frameBuffer[index+1] = image._frame[imageIndex+1];
        BUFFERS[window.id].frameBuffer[index+2] = image._frame[imageIndex+2];

    }
    }

}

void rotateGrafixImage(grafixImage *image, float angle){
    
    int padding = ceil(sqrt(image->width * image->width + image->height * image->height)) - (image->width + image->height) / 2;
    int padded_w = image->width + 2 * padding;
    int padded_h = image->height + 2 * padding;

    unsigned char* temp_buffer = (unsigned char*)malloc(padded_w * padded_h * 3 * sizeof(unsigned char));

    float cos_theta = cos(angle);
    float sin_theta = sin(angle);
    float matrix[] = { cos_theta, -sin_theta, 0, sin_theta, cos_theta, 0, 0, 0, 1 };

    float inv_matrix[] = { cos_theta, sin_theta, 0, -sin_theta, cos_theta, 0, 0, 0, 1 };

    for (int y = -padding; y < image->height + padding; y++) {
        for (int x = -padding; x < image->width + padding; x++) {

            float xf = x * matrix[0] + y * matrix[1] + (image->width / 2) * (1 - matrix[0]) - (image->height / 2) * matrix[1];
            float yf = x * matrix[3] + y * matrix[4] + (image->height / 2) * (1 - matrix[4]) - (image->width / 2) * matrix[3];

            int ix = (int)round(xf);
            int iy = (int)round(yf);

            float dx = xf - ix;
            float dy = yf - iy;

            if (ix < 0) ix = 0;
            if (iy < 0) iy = 0;
            if (ix >= image->width - 1) ix = image->width - 2;
            if (iy >= image->height - 1) iy = image->height - 2;

            int idx = (iy * padded_w + ix) * 3;
            float r = temp_buffer[idx] * (1 - dx) * (1 - dy);
            float g = temp_buffer[idx + 1] * (1 - dx) * (1 - dy);
            float b = temp_buffer[idx + 2] * (1 - dx) * (1 - dy);

            idx = (iy * padded_w + ix + 1) * 3;
            r += temp_buffer[idx] * dx * (1 - dy);
            g += temp_buffer[idx + 1] * dx * (1 - dy);
            b += temp_buffer[idx + 2] * dx * (1 - dy);

            idx = ((iy + 1) * padded_w + ix) * 3;
            r += temp_buffer[idx] * (1 - dx) * dy;
            g += temp_buffer[idx + 1] * (1 - dx) * dy;
            b += temp_buffer[idx + 2] * (1 - dx) * dy;

            idx = ((iy + 1) * padded_w + ix + 1) * 3;
            r += temp_buffer[idx] * dx * dy;
            g += temp_buffer[idx + 1] * dx * dy;
            b += temp_buffer[idx + 2] * dx * dy;

            idx = ((y + padding) * padded_w + (x + padding)) * 3;
            temp_buffer[idx] = (unsigned char)r;
            temp_buffer[idx + 1] = (unsigned char)g;
            temp_buffer[idx + 2] = (unsigned char)b;
        }
    }

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            int src_idx = ((y + padding) * padded_w + (x + padding)) * 3;
            int dst_idx = (y * image->width + x) * 3;
            image->_frame[dst_idx] = temp_buffer[src_idx];
            image->_frame[dst_idx + 1] = temp_buffer[src_idx + 1];
            image->_frame[dst_idx + 2] = temp_buffer[src_idx + 2];
        }
    }

    free(temp_buffer);

}