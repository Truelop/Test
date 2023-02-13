#ifndef CORE_BASE_H
#define CORE_BASE_H

#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#define Sleep(msec) usleep((msec)*1000)

#include "timer.h"
#include "graphics.h"

extern float FPS;

int main(int argc, char **argv);

extern int SimulationMain(int argc, char **argv);

extern void SimulationLoop(float dt);

extern void SimulationUpdate(float dt);

#endif /* CORE_BASE_H */