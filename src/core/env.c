#include <core/env.h>

Env EnvMake(EnvMapper mapper) {
	Env env = {0};
	for (int i = 0; i < ENV_GRID_CELL_COUNT_X; i++) {
		for (int j = 0; j < ENV_GRID_CELL_COUNT_Y; j++) {
			EnvCell c = {0};
			c.cell = CellMake(
				Vec2Make(
					i * ENV_GRID_CELL_SIZE_X - ENV_GRID_SIZE_X / 2.0f,
					j * ENV_GRID_CELL_SIZE_Y - ENV_GRID_SIZE_Y / 2.0f),
				Vec2Make(ENV_GRID_CELL_SIZE_X, ENV_GRID_CELL_SIZE_Y),
				ColorMake(255, 255, 255, 255));
			env.grid[i * ENV_GRID_CELL_COUNT_Y + j] = mapper(c);
		}
	}
	return env;
}

Env *EnvCreate(EnvMapper mapper) {
	Env *env = malloc(sizeof(Env));
	for (int i = 0; i < ENV_GRID_CELL_COUNT_X; i++) {
		for (int j = 0; j < ENV_GRID_CELL_COUNT_Y; j++) {
			EnvCell c = {0};
			c.cell = CellMake(
				Vec2Make(
					i * ENV_GRID_CELL_SIZE_X - ENV_GRID_SIZE_X / 2.0f,
					j * ENV_GRID_CELL_SIZE_Y - ENV_GRID_SIZE_Y / 2.0f),
				Vec2Make(ENV_GRID_CELL_SIZE_X, ENV_GRID_CELL_SIZE_Y),
				ColorMake(255, 255, 255, 255));
			env->grid[i * ENV_GRID_CELL_COUNT_Y + j] = mapper(c);
		}
	}
	return env;
}

void EnvDelete(Env *env) {
	free(env);
}

void EnvRender(Env *env) {
	// Cell c = CellMake(Vec2Make(10,10),Vec2Make(5,5),ColorMake(255,0,0));
	// CellRender(&c);
	for (int i = 0; i < ENV_GRID_CELL_COUNT; i++) {
		CellRender(&env->grid[i].cell);
	}
}

EnvCell *EnvSearchCell(Env *env, vec2 position) {
	EnvCell *c = &env->grid[0];
	float dist = Vec2Distance(position, env->grid[0].cell.position);
	for (int i = 1; i < ENV_GRID_CELL_COUNT; i++) {
		float cdist = Vec2Distance(position, env->grid[i].cell.position);
		if (cdist < dist) {
			c = &env->grid[i];
			dist = cdist;
		}
	}
	return c;
}

void EnvUpdate(Env *env, EnvMapper mapper) {
	for (int i = 0; i < ENV_GRID_CELL_COUNT_X; i++) {
		for (int j = 0; j < ENV_GRID_CELL_COUNT_Y; j++) {
			env->grid[i * ENV_GRID_CELL_COUNT_Y + j] =
				mapper(env->grid[i * ENV_GRID_CELL_COUNT_Y + j]);
		}
	}
}