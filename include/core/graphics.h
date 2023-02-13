#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H

#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} Color;

Color ColorMake(int r, int g, int b, int a);

void DisplayInit();

void DisplayClear();

void SetPixel(GLint x, GLint y, Color color);

Color GetPixel(GLint x, GLint y);

void SetColor(Color color);

void FillRect(float x, float y, float width, float height, Color color);

void StrokeRect(float x, float y, float width, float height, Color color);

void Translate(float x, float y);

void Rotate(float angle);

void SaveContext();

void RestoreContext();

int GetWidth();

int GetHeight();

void FillCircle(float x, float y, float radius, Color color);

void StrokeCircle(float x, float y, float radius, Color color);

void DisplayFlush();

void Line(float x1, float y1, float x2, float y2, Color color);

void Scale(float scale);

#endif /* CORE_GRAPHICS_H */
