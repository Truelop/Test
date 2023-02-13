#ifndef CORE_ENV_H
#define CORE_ENV_H

#include "base.h"
#include "cell.h"
#include "vec2.h"

#define ENV_GRID_SIZE_X 150
#define ENV_GRID_SIZE_Y 150
#define ENV_GRID_SIZE ENV_GRID_SIZE_X *ENV_GRID_SIZE_Y
#define ENV_GRID_CELL_SIZE_X 2
#define ENV_GRID_CELL_SIZE_Y 2
#define ENV_GRID_CELL_SIZE ENV_GRID_CELL_SIZE_X *ENV_GRID_CELL_SIZE_Y
#define ENV_GRID_CELL_COUNT_X CEILING(ENV_GRID_SIZE_X, ENV_GRID_CELL_SIZE_X)
#define ENV_GRID_CELL_COUNT_Y CEILING(ENV_GRID_SIZE_Y, ENV_GRID_CELL_SIZE_Y)
#define ENV_GRID_CELL_COUNT ENV_GRID_CELL_COUNT_X *ENV_GRID_CELL_COUNT_Y

typedef struct EnvCell {
	Cell cell;
	float temperature;
	float pressure;
	bool isObstacle;

	vec2 a;
	float b;
	int c;
} EnvCell;

typedef EnvCell (*EnvMapper)(EnvCell cell);

typedef struct Env {
	EnvCell grid[ENV_GRID_SIZE_X * ENV_GRID_SIZE_Y];
} Env;

Env *EnvCreate(EnvMapper mapper);
void EnvDelete(Env *env);
Env EnvMake(EnvMapper mapper);
void EnvRender(Env *env);
EnvCell *EnvSearchCell(Env *env, vec2 position);
void EnvUpdate(Env *env, EnvMapper mapper);

#endif /* CORE_ENV_H */