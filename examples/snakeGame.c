#include "../src/grafix.h"
#include <stdlib.h>

int main(){
    grafixInit();
    
    grafixWindow window;
    createGrafixWindow(&window,800,800,"GrafixWindow");
    showGrafixWindow(window);

    int eventSize;
    grafixColor WHITE = {255,255,255};
    grafixEvent* event;

    typedef struct body{
        int x;int y;
        int height;int width;
        grafixColor color;

        struct body* next;
        struct body* prev;
    } SB;

    typedef struct head{
        int x;int y;
        int height;int width;
        grafixColor color;

        int dir[2];
        int bodyLength;
        int speed;
        
        SB* top;
        SB* end;
    } SH;

    typedef struct food{
        int x;int y;
        int height;int width;
        grafixColor color;
    } F;

    SH SnakeHead;
    SnakeHead.x = 800/2;SnakeHead.y = 800/2;
    SnakeHead.height = 15;SnakeHead.width = 15;
    SnakeHead.color = (grafixColor){0,255,0};
    SnakeHead.dir[0] = 1;SnakeHead.dir[1] = 0;
    SnakeHead.bodyLength = 5;SnakeHead.speed =1;

    SB* tmpBody;
    for(int i = 1; i <= 5; i++){
        SB* body = (SB*) malloc(sizeof(SB));
        body->height = 15;body->width = 15;
        body->x = (800/2)-(15*i);body->y = (800/2);
        body->color = (grafixColor){0,150-(i*10),0};
        body->next = NULL;body->prev = NULL;
        if(i == 1){
            SnakeHead.top = body;
            tmpBody = body;
        }else {
            body->prev = tmpBody;
            tmpBody->next = body;
            tmpBody = tmpBody->next;
        }
    }SnakeHead.end = tmpBody;
    
    F food;
    food.x = rand() % 800;
    food.y = rand() % 800;
    food.height = 5;food.width = 5;
    food.color = (grafixColor){255,0,0};

    int isPaused = 0;
    int tmpX = 0,tmpY = 0;int cl = 1;
    while(!isGrafixWindowEnded(window)){
        
        fillGrafixWindow(window,(grafixColor){0,0,0});
        manageGrafixEvent(window,&event,&eventSize);
        
        for(int i = 0; i < eventSize; i++){
            
            if(event[i].type == WM_DESTROY){
                endGrafixWindow(window);
                return 0;
            }else if(event[i].type == WM_KEYDOWN){
                if(event[i].wkeyCode == VK_UP){
                    SnakeHead.dir[0] = 0;
                    SnakeHead.dir[1] = -1;
                }else if(event[i].wkeyCode == VK_DOWN){
                    SnakeHead.dir[0] = 0;
                    SnakeHead.dir[1] = 1;
                }else if(event[i].wkeyCode == VK_LEFT){
                    SnakeHead.dir[0] = -1;
                    SnakeHead.dir[1] = 0;
                }else if(event[i].wkeyCode == VK_RIGHT){
                    SnakeHead.dir[0] = 1;
                    SnakeHead.dir[1] = 0;
                }else if(event[i].wkeyCode == VK_SPACE){
                    isPaused = isPaused?0:1;
                }
            }
            
        }
        if(!isPaused){
        if(
            food.x < SnakeHead.x + SnakeHead.width &&
            food.x + food.width > SnakeHead.x &&
            food.y < SnakeHead.y + SnakeHead.height &&
            food.height + food.y > SnakeHead.y
        ){
            food.x = rand() % 700 + 100;
            food.y = rand() % 700 + 100;

            tmpBody = (SB*) malloc(sizeof(SB));
            tmpBody->height = 15;tmpBody->width = 15;
            tmpBody->x = SnakeHead.end->x;tmpBody->y = SnakeHead.end->y;
            if(SnakeHead.end->color.green <= 100)cl = +1;
            else if(SnakeHead.end->color.green >=250)cl = -1;
            tmpBody->color = (grafixColor){0,SnakeHead.end->color.green+(cl*10),0};
            tmpBody->next = NULL;tmpBody->prev = SnakeHead.end;
            SnakeHead.end->next = tmpBody;
            SnakeHead.end = tmpBody;
            SnakeHead.bodyLength++;
        }

        tmpBody = SnakeHead.end;
        while(tmpBody->prev != NULL){
            tmpX = tmpBody->prev->x;
            tmpY = tmpBody->prev->y;
            tmpBody->x = tmpX;
            tmpBody->y = tmpY;
            tmpBody = tmpBody->prev;
        }

        SnakeHead.top->x = SnakeHead.x;
        SnakeHead.top->y = SnakeHead.y;

        SnakeHead.x += SnakeHead.dir[0]*SnakeHead.speed*SnakeHead.width;
        SnakeHead.y += SnakeHead.dir[1]*SnakeHead.speed*SnakeHead.width;
        
        }
        drawGrafixLine(window,SnakeHead.x,SnakeHead.y,food.x,food.y,(grafixColor){100,100,100});
        drawGrafixRect(window,food.x,food.y,food.width,food.height,food.color,FM_FILL,0);
        drawGrafixRect(window,SnakeHead.x,SnakeHead.y,SnakeHead.width,SnakeHead.height,SnakeHead.color,FM_FILL,0);
        tmpBody = SnakeHead.top;
        while(tmpBody != NULL){
            drawGrafixRect(window,tmpBody->x,tmpBody->y,tmpBody->width,tmpBody->height,tmpBody->color,FM_FILL,0);
            tmpBody = tmpBody->next;
        }
    

        updateGrafixWindow(window);
        updateGrafixTime(window);
        tickGrafix(window,20);
        
    }

    
    return 0;
}
