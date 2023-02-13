#include <core/cell.h>

Cell CellMake(vec2 position, vec2 size, Color color) {
	return (Cell){position, size, color};
}

void CellRender(Cell *cell) {
	FillRect(
		cell->position.x, cell->position.y, cell->size.x, cell->size.y, cell->color);
}

int CellSearch(Cell *grid, int size, vec2 position) {
	for (int i = 0; i < size; i++) {
		if (Vec2Equal(position, grid[i].position)) {
			return i;
		}
	}
	return -1;
}