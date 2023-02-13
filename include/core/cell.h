#ifndef CORE_CELL_H
#define CORE_CELL_H

#include "base.h"
#include "vec2.h"

typedef struct Cell {
	vec2 position;
	vec2 size;
	Color color;
} Cell;

Cell CellMake(vec2 position, vec2 size, Color color);

void CellRender(Cell *cell);

int CellSearch(Cell *grid, int size, vec2 position);

#endif /* CORE_CELL_H */