#ifndef CORE_CONTROLLER_H
#define CORE_CONTROLLER_H

#include "base.h"
#include "cell.h"
#include "rover.h"
#include "utils.h"
#include "vec2.h"

#define SCANNING_WIDTH 5.0f
#define SCANNING_HEIGHT 5.0f

#define SCANNING_COUNT_X CEILING((int)ROVER_AREA_WIDTH, (int)SCANNING_WIDTH)

#define SCANNING_COUNT_Y CEILING((int)ROVER_AREA_HEIGHT, (int)SCANNING_HEIGHT)

#define SCANNING_COUNT SCANNING_COUNT_X *SCANNING_COUNT_Y

#define SCANNING_ALPHA 50

typedef enum ExplorationState {
	ExplorationInit,
	ExplorationIdle,
	ExplorationRunning,
	ExplorationGetBackToBase,
	ExplorationFinished
} ExplorationState;

typedef struct ControllerOutput {
	float speedLeft;
	float speedRight;
	ExplorationState state;

	/* for debug/render only */
	Cell grid[SCANNING_COUNT];
	Rover rover;
	float dt;
} ControllerOutput;

ControllerOutput ControllerRover(Rover *rover, float dt);
void ControllerOutputRender(ControllerOutput *output);

#endif /* CORE_CONTROLLER_H */