
#ifndef TIME_H
#define TIME_H

#include "grafix.h"
#include <time.h>

typedef struct TIME{
    int id;

    // LARGE_INTEGER _startCounter;
    // LARGE_INTEGER _endCounter;
    // LARGE_INTEGER _frequency;
    // LARGE_INTEGER _tmpCounts;
    
    // LARGE_INTEGER _tpsCounter;
    // LARGE_INTEGER _msCounter;

    int _msPerFrame;
    int _limitTps;
    int _tps;
    
    clock_t _startCounter;
    clock_t _endCounter;
    int _waitCounter;

} _grafixTIME;

extern _grafixTIME TIMES[MAX_WINDOW];

int getGrafixFPS(grafixWindow window);
void tickGrafix(grafixWindow window, int);
void waitGrafixWindow(grafixWindow window, int millisecond);
void updateGrafixTime(grafixWindow window);

//only for dev
void dev_DEBUG_TIME(grafixWindow window);

#endif /* TIME_H */