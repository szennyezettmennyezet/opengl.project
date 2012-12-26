#ifndef __HRTIMER__
#define __HRTIMER__

#include "Windows.h"


class HRTimer {
public:

    HRTimer(void);

    double getFrequency(void);
    void startTimer(void) ;
    double stopTimer(void);

private:

    LARGE_INTEGER start;
    LARGE_INTEGER stop;

    double frequency;
    //..

};




#endif
