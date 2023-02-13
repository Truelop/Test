#include <core/controller.h>

ControllerOutput ControllerRover(Rover *rover, float dt) {
	static bool init = false;
	static vec2 paths[SCANNING_COUNT] = {0};
	static Cell grid[SCANNING_COUNT] = {0};
	static int index = 1;
	static ExplorationState state = ExplorationInit;

	/* initialize controller */
	if (state == ExplorationInit) {
		state = ExplorationRunning;

		/* create path */
		bool reverse = false;
		for (int i = 0; i < SCANNING_COUNT_X; i++) {
			for (int j = 0; j < SCANNING_COUNT_Y; j++) {
				paths[i * SCANNING_COUNT_Y + j] = Vec2Make(
					i * SCANNING_WIDTH,
					(reverse ? SCANNING_COUNT_Y - j - 1 : j) *
						-SCANNING_HEIGHT);
			}
			reverse = !reverse;
		}

		/* set color cells */
		reverse = false;
		for (int i = 0; i < SCANNING_COUNT_X; i++) {
			for (int j = 0; j < SCANNING_COUNT_Y; j++) {
				grid[i * SCANNING_COUNT_Y + j].position = Vec2Make(
					i * SCANNING_WIDTH,
					(reverse ? SCANNING_COUNT_Y - j - 1 : j) *
						-SCANNING_HEIGHT);
				grid[i * SCANNING_COUNT_Y + j].size =
					Vec2Make(SCANNING_WIDTH, SCANNING_HEIGHT);
				grid[i * SCANNING_COUNT_Y + j].color =
					ColorMake(255, 255, 255, SCANNING_ALPHA);
			}
			reverse = !reverse;
		}
	}

	/* inegrate x, y and angle to estimate position/angle */
	static vec2 position = Vec2Zero;
	static float angle = 0.0f;

	/* speed command sent to the motors */
	static float speedLeft = 0.0f;
	static float speedRight = 0.0f;

	/* fetch current target point */
	vec2 target = paths[index];
	int cellindex = CellSearch(grid, SCANNING_COUNT, target);

	/* estimate the diff angle with target */
	float relangle = ToDeg(Vec2Angle(target, position));

	// printf("angle: %f, relangle: %f\n",angle,relangle);

	/* if exploration is running or going to base */

	if (state == ExplorationRunning || state == ExplorationGetBackToBase) {
		/* check if rover is looking at the target */
		if (EqualFloatEps(angle, relangle, 5.0f)) {
			/* if yes, then go forward at 2km/h if rover is not already arrived
			 */
			if (!(Vec2Distance(target, position) < 1.0f)) {
				float diff = (relangle - angle) / 30.0f;
				speedLeft = 5.0f + diff;
				speedRight = 5.0f - diff;
				grid[cellindex].color = ColorMake(255, 125, 0, SCANNING_ALPHA);
			}

			/* else, we need to go to the next step */
			else if (state == ExplorationRunning) {
				index++;
				if (index >= SCANNING_COUNT) {
					index = 0;
					state = ExplorationGetBackToBase;
				}
				grid[cellindex].color = ColorMake(0, 240, 0, SCANNING_ALPHA);
			}

			/* if exploration is finished */
			else if (state == ExplorationGetBackToBase) {
				state = ExplorationFinished;
				speedLeft = 0.0f;
				speedRight = 0.0f;
				grid[cellindex].color = ColorMake(0, 240, 240, SCANNING_ALPHA);
			}
		}

		/* if rover no looking at the target, continue to rotate */
		else {
			/* Proportional Corrector */
			float diff = 3.0 * (relangle - angle) / 30.0f;
			speedLeft = diff;
			speedRight = -diff;
			// grid[cellindex].color = ColorMake(255,125,0,SCANNING_ALPHA);
			grid[cellindex].color = ColorMake(240, 240, 0, SCANNING_ALPHA);
		}
	}

	speedLeft = speedLeft / (1.0f + rover->temperature * 10.0f);
	speedRight = speedRight / (1.0f + rover->temperature * 10.0);

	// estimate relative x and y and angle

	float avg_left = (rover->wheels[0].speed + rover->wheels[1].speed +
					  rover->wheels[2].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_right = (rover->wheels[3].speed + rover->wheels[4].speed +
					   rover->wheels[5].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_v = ((avg_left + avg_right) / 2.0f);
	angle +=
		(avg_left - avg_right) / 2.0f * 180.0f / (M_PI * rover->width) * dt;
	if (angle > 360.0f)
		angle -= 360.0f;
	position.x += avg_v * cos(angle * M_PI / 180.0f) * dt;
	position.y += avg_v * sin(angle * M_PI / 180.0f) * dt;

	/* for debug purposes */

	/* build output */
	ControllerOutput output = {0};
	output.rover = *rover;
	output.dt = dt;
	output.speedLeft = speedLeft;
	output.speedRight = speedRight;
	output.state = state;
	for (int i = 0; i < SCANNING_COUNT; i++)
		output.grid[i] = grid[i];

	/* return output */
	return output;
}

void ControllerOutputRender(ControllerOutput *output) {
	Rover rover = output->rover;

	SaveContext();
	Translate(rover.origin.x, rover.origin.y);
	Rotate(rover.origin_angle);
	Translate(-SCANNING_WIDTH / 2, -SCANNING_HEIGHT / 2);
	for (int i = 0; i < SCANNING_COUNT; i++) {
		CellRender(&output->grid[i]);
	}
	RestoreContext();

	SaveContext();

	Translate(rover.origin.x, rover.origin.y);
	Rotate(rover.origin_angle - 90);
	Translate(-SCANNING_WIDTH / 2, -SCANNING_HEIGHT / 2);

	// draw scanning rect
	int amount_y = ceil(ROVER_AREA_HEIGHT / SCANNING_HEIGHT);
	int amount_x = ceil(ROVER_AREA_WIDTH / SCANNING_WIDTH);
	for (int y = 0; y < amount_y; y++) {
		for (int x = 0; x < amount_x; x++) {
			StrokeRect(
				x * SCANNING_WIDTH,
				y * SCANNING_HEIGHT,
				SCANNING_WIDTH,
				SCANNING_HEIGHT,
				ColorMake(50, 50, 50, 255));
		}
	}

	// draw 25x25m area
	StrokeRect(
		0, 0, ROVER_AREA_WIDTH, ROVER_AREA_HEIGHT, ColorMake(0, 0, 0, 255));

	RestoreContext();
}

/*#define ACTION_IDLE 0
#define ACTION_GO 1
#define ACTION_TURN_LEFT 2
#define ACTION_TURN_RIGHT 3

void RoverSetSpeedLeft(Rover *rover, float speed);
void RoverSetSpeedRight(Rover *rover, float speed);

void RoverController(Rover *rover, float dt) {
	static float x = 0.0f;
	static float y = 0.0f;
	static float angle = 0.0f;
	static float index = 1;

	float speed = 0.0f;

	int mode = 0;

  static bool a = false;
	static bool b = false;
  static bool c = false;

	// printf("%f,%f,%f,%f,%s,%s\n", x, y, index, angle, a ? "true" : "false",b
? "true" : "false");

  if (x > ROVER_AREA_WIDTH - SCANNING_WIDTH && index >= ceil(ROVER_AREA_HEIGHT /
SCANNING_HEIGHT)) { c = true; mode = ACTION_IDLE;
  }
	if (!c && x > ROVER_AREA_WIDTH - SCANNING_WIDTH) {
		mode = ACTION_TURN_LEFT;
		if (angle < -90) {
			mode = ACTION_GO;
			if (y < -SCANNING_WIDTH * index) {
				mode = ACTION_TURN_LEFT;
				if (angle < -180) {
					mode = ACTION_GO;
					if (!a) {
						index++;
						a = true;
						b = false;
					}
				}
			}
		}
	} else if (!c) {
		mode = ACTION_GO;
		if (x < 0) {
			mode = ACTION_TURN_RIGHT;
			if (angle >= -92) {
				mode = ACTION_GO;
				if (y < -SCANNING_WIDTH * index) {
					mode = ACTION_TURN_RIGHT;
					if (angle > 0) {
						mode = ACTION_GO;
						if (!b) {
							index++;
							b = true;
							a = false;
						}
						x = 0;
					}
				}
			}
		}
	}

	switch (mode) {
	case ACTION_IDLE:
	RoverSetSpeedLeft(rover, 0);
		RoverSetSpeedRight(rover, 0);
		break;
	case ACTION_GO: {
		speed = KMHToMS(10.0f);
		RoverSetSpeedLeft(rover, speed);
		RoverSetSpeedRight(rover, speed);
	} break;
	case ACTION_TURN_LEFT: {
		speed = KMHToMS(1.0f);
		RoverSetSpeedLeft(rover, -speed);
		RoverSetSpeedRight(rover, speed);
	} break;
	case ACTION_TURN_RIGHT: {
		speed = KMHToMS(1.0f);
		RoverSetSpeedLeft(rover, speed);
		RoverSetSpeedRight(rover, -speed);
	} break;
	default:
		break;
	}

	// printf("(%f,%f)\n", x, y);

	// estimate relative x and y and angle

	float avg_left = (rover->wheels[0].speed + rover->wheels[1].speed +
					  rover->wheels[2].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_right = (rover->wheels[3].speed + rover->wheels[4].speed +
					   rover->wheels[5].speed) *
		((M_PI * ROVER_WHEEL_DIAMETER) / 360.0f);
	float avg_v = ((avg_left + avg_right) / 2.0f);
	angle +=
		(avg_left - avg_right) / 2.0f * 180.0f / (M_PI * rover->width) * dt;
	x += avg_v * cos(angle * M_PI / 180.0f) * dt;
	y += avg_v * sin(angle * M_PI / 180.0f) * dt;
}*/