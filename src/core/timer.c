#include <core/timer.h>

Timer TimerMake() {
  Timer timer = {0};
  return timer;
}

void TimerStart(Timer *timer) {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer->start);
}

void TimerStop(Timer *timer) {
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer->stop);
}

float TimerGetElapsed(Timer *timer) {
  return ((timer->stop.tv_sec - timer->start.tv_sec) * 1e6 +
						  (timer->stop.tv_nsec - timer->start.tv_nsec) / 1e3) /
			1e6;
}
