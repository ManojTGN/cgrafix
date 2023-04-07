#include "../src/grafix.h"
#include <math.h>


void draw_cube(grafixWindow window, double angle_x, double angle_y, int pos_x, int pos_y, int scale, grafixColor color) {
    int vertices[8][3] = {
        {-50, -50, -50},
        {50, -50, -50},
        {50, 50, -50},
        {-50, 50, -50},
        {-50, -50, 50},
        {50, -50, 50},
        {50, 50, 50},
        {-50, 50, 50},
    };

    int edges[12][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
    };

    double s_x = sin(angle_x);
    double c_x = cos(angle_x);
    for (int i = 0; i < 8; i++) {
        int y = vertices[i][1];
        int z = vertices[i][2];
        vertices[i][1] = y * c_x - z * s_x;
        vertices[i][2] = y * s_x + z * c_x;
    }

    double s_y = sin(angle_y);
    double c_y = cos(angle_y);
    for (int i = 0; i < 8; i++) {
        int x = vertices[i][0];
        int z = vertices[i][2];
        vertices[i][0] = x * c_y - z * s_y;
        vertices[i][2] = x * s_y + z * c_y;
    }

    for (int i = 0; i < 8; i++) {
        vertices[i][0] *= scale;
        vertices[i][1] *= scale;
        vertices[i][2] *= scale;
    }
    for (int i = 0; i < 12; i++) {
        int v0 = edges[i][0];
        int v1 = edges[i][1];
        drawGrafixLine(window, vertices[v0][0] + pos_x, vertices[v0][1] + pos_y, vertices[v1][0] + pos_x, vertices[v1][1] + pos_y,color);
    }
}

int main(){
    grafixInit();
    
    grafixWindow window;
    createGrafixWindow(&window,800,800,"GrafixWindow");
    showGrafixWindow(window);

    float angle = 0;
    grafixColor color = {255,255,255};
    grafixEvent* event;int eventSize;

    while(!isGrafixWindowEnded(window)){
        
        fillGrafixWindow(window,(grafixColor){0,0,0});

        angle+=.01;
        if(angle >= 360) angle = 0;
        
        draw_cube(window,angle,angle,400,400,3,color);
        updateGrafixWindow(window);

        manageGrafixEvent(window,&event,&eventSize);
        for(int i = 0; i < eventSize; i++){
            if(event[i].type == WM_DESTROY){
                endGrafixWindow(window);
                return 0;
            }
        }

        updateGrafixTime(window);
        tickGrafix(window,100);
    }

    endGrafixWindow(window);
    return 0;
}
