#include "time.h"

_grafixTIME TIMES[MAX_WINDOW];

void dev_DEBUG_TIME(grafixWindow window){
    printf(
        "ms:%d tps:%d lt:%d start:%d end:%d wc:%d\n",
        TIMES[window.id]._msPerFrame,
        TIMES[window.id]._tps,
        TIMES[window.id]._limitTps,
        TIMES[window.id]._startCounter,
        TIMES[window.id]._endCounter,
        TIMES[window.id]._waitCounter
    );
}

int getGrafixFPS(grafixWindow window){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return -1;

    return TIMES[window.id]._tps;

}

void tickGrafix(grafixWindow window, int tick){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    if(TIMES[window.id]._limitTps != tick){
        TIMES[window.id]._limitTps = tick;
    }

    Sleep( TIMES[window.id]._waitCounter );

    TIMES[window.id]._waitCounter = 0;
    TIMES[window.id]._startCounter = clock();
}

void updateGrafixTime(grafixWindow window){
    if( WINDOWS[window.id] == NULL|| window.isDead ) return;

    TIMES[window.id]._endCounter = clock();
    TIMES[window.id]._msPerFrame = TIMES[window.id]._endCounter - TIMES[window.id]._startCounter;

    if(TIMES[window.id]._limitTps != 0 ){
        TIMES[window.id]._waitCounter = round( (double)1000/TIMES[window.id]._limitTps ) - TIMES[window.id]._msPerFrame;
        TIMES[window.id]._waitCounter = TIMES[window.id]._waitCounter <= 0 ? 0 : TIMES[window.id]._waitCounter;
    }

    TIMES[window.id]._tps = round( (double)1000 / (TIMES[window.id]._msPerFrame + TIMES[window.id]._waitCounter) );
    TIMES[window.id]._startCounter = clock();
    
}