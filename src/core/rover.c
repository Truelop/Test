#include <core/rover.h>

Rover RoverBuild() {
	Rover rover = {0};
	rover.width = 0.8f;
	rover.height = 2.4f;
	return rover;
}

void RoverPlace(Rover *rover, int x, int y, int angle) {
	rover->origin = Vec2Make(x, y);
	rover->origin_angle = angle;
	rover->position = Vec2Make(x, y);
	rover->angle = angle;
}

void RoverRender(Rover *rover) {
	SaveContext();

	Translate(rover->position.x, rover->position.y);
	Rotate(rover->angle - 90);

	FillRect(
		-rover->width / 2.0f,
		-rover->height / 2.0f + 0.4f,
		rover->width,
		rover->height,
		ColorMake(255, 0, 0, 255));

	FillRect(
		-rover->width / 2,
		-rover->height / 2,
		rover->width,
		rover->height,
		ColorMake(0, 0, 255, 255));

	float dy = rover->height / 3;
	SaveContext();
	Translate(-rover->width / 2, 0);
	for (int i = 0; i < 3; i++) {
		FillCircle(
			0, (i - 1) * dy, ROVER_WHEEL_DIAMETER, ColorMake(255, 0, 255, 255));
	}
	RestoreContext();
	SaveContext();
	Translate(rover->width / 2, 0);
	for (int i = 0; i < 3; i++) {
		FillCircle(
			0, (i - 1) * dy, ROVER_WHEEL_DIAMETER, ColorMake(255, 0, 255, 255));
	}
	RestoreContext();

	RestoreContext();
}

void RoverSetSpeed(Rover *rover, int motor_id, float speed) {
	rover->wheels[motor_id].speed = speed;
}

void RoverUpdatePosition(Rover *rover, float dt) {
	float avg_left = (rover->wheels[0].speed + rover->wheels[1].speed +
					  rover->wheels[2].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_right = (rover->wheels[3].speed + rover->wheels[4].speed +
					   rover->wheels[5].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_v = ((avg_left + avg_right) / 2.0f);
	rover->angle +=
		(avg_left - avg_right) / 2.0f * 180.0f / (M_PI * rover->width) * dt;
	rover->position.x += avg_v * cos(rover->angle * M_PI / 180.0f) * dt;
	rover->position.y += avg_v * sin(rover->angle * M_PI / 180.0f) * dt;
}

void RoverSetSpeedHelper(Rover *rover, float speedLeft, float speedRight) {
	RoverSetSpeedLeft(rover, speedLeft);
	RoverSetSpeedRight(rover, speedRight);
}

void RoverSetSpeedLeft(Rover *rover, float speed) {
	RoverSetSpeed(rover, ROVER_MOTOR_1, speed / 3.0f);
	RoverSetSpeed(rover, ROVER_MOTOR_2, speed / 3.0f);
	RoverSetSpeed(rover, ROVER_MOTOR_3, speed / 3.0f);
}
void RoverSetSpeedRight(Rover *rover, float speed) {
	RoverSetSpeed(rover, ROVER_MOTOR_4, speed / 3.0f);
	RoverSetSpeed(rover, ROVER_MOTOR_5, speed / 3.0f);
	RoverSetSpeed(rover, ROVER_MOTOR_6, speed / 3.0f);
}

void RoverEmulateEnv(Rover *rover, Env *env) {
	EnvCell *ec = EnvSearchCell(env, rover->position);
	if (ec) {
		rover->temperature = ec->temperature;
		rover->pressure = ec->pressure;
		// todo (ray tracing)
		for (int i = 0; i < ROVER_SENSOR_TELEMETRY_COUNT; i++) {
			rover->telemetries[i] = 0.0f;
		}
	} else {
		rover->temperature = 0.0f;
		rover->pressure = 0.0f;
		for (int i = 0; i < ROVER_SENSOR_TELEMETRY_COUNT; i++) {
			rover->telemetries[i] = 0.0f;
		}
	}
}

#ifdef DEBUG
void RoverDebug(Rover *rover) {
	printf(
		"Env :\n   Temperature : %5.2f\n   Pressure    : %5.2f\n",
		rover->temperature,
		rover->pressure);
	for (int i = 0; i < ROVER_SENSOR_TELEMETRY_COUNT; i++) {
		printf("   Telemetry %d : %5.2f\n", i, rover->telemetries[i]);
	}
}
#endif
