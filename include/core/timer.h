#ifndef CORE_TIMER_H
#define CORE_TIMER_H

#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef struct Timer {
	struct timespec start, stop;
} Timer;

Timer TimerMake();
void TimerStart(Timer *timer);
void TimerStop(Timer *timer);
float TimerGetElapsed(Timer *timer);

#endif /* CORE_TIMER_H */