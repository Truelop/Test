#ifndef CORE_ROVER_H
#define CORE_ROVER_H

#include "base.h"
#include "vec2.h"
#include "wheel.h"
#include "env.h"

#define ROVER_AREA_WIDTH 25.0f
#define ROVER_AREA_HEIGHT 25.0f

#define ROVER_WHEEL_DIAMETER 0.2f

#define ROVER_SENSOR_TELEMETRY_COUNT 5

#define ROVER_MOTOR_1 0
#define ROVER_MOTOR_2 1
#define ROVER_MOTOR_3 2
#define ROVER_MOTOR_4 3
#define ROVER_MOTOR_5 4
#define ROVER_MOTOR_6 5

typedef struct Rover {
	// only for drawing
	/* private */ vec2 origin;
	/* private */ float origin_angle;

	// only for internal simulation world
	vec2 position;
	float angle;

	// dimension
	float width;
	float height;

	// wheel motors
	Wheel wheels[6];

	// captors
	float temperature;
	float pressure;
	float telemetries[ROVER_SENSOR_TELEMETRY_COUNT];

} Rover;

Rover RoverBuild();
void RoverPlace(Rover *rover, int x, int y, int angle);
void RoverRender(Rover *rover);
void RoverSetSpeed(Rover *rover, int motor_id, float speed);
void RoverUpdatePosition(Rover *rover, float dt);
void RoverSetSpeedLeft(Rover *rover, float speed);
void RoverSetSpeedRight(Rover *rover, float speed);
void RoverSetSpeedHelper(Rover *rover, float speedLeft, float speedRight);
void RoverEmulateEnv(Rover *rover, Env *env);

#ifdef DEBUG
void RoverDebug(Rover *rover);
#endif

#endif /* CORE_ROVER_H */