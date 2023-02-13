#include <core/graphics.h>

void DisplayIdle() {
	glutPostRedisplay();
}

void DisplayInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor4f(0.0, 0.0, 0.0, 0.0);
	// gluOrtho2D(0.0, 640.0, 0.0, 480.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 640.0, 480.0, 0.0, -1.0, 1.0);
	// glScalef(1.0f,-1.0f,0.0f);
	glPointSize(1.0f);
}

void DisplayClear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void DisplayFlush() {
	glFlush();
	glutIdleFunc(DisplayIdle);
	glutSwapBuffers();
}

Color ColorMake(int r, int g, int b, int a) {
	return (Color){(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f};
}

void SetPixel(int x, int y, Color color) {
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

Color GetPixel(int x, int y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, &color);
	return color;
}

void SetColor(Color color) {
	glColor4d(color.r, color.g, color.b, color.a);
}

void FillRect(float x, float y, float width, float height, Color color) {
	glBegin(GL_QUADS);
	SetColor(color);
	glVertex2f(x, y);
	SetColor(color);
	glVertex2f(x, y + height);
	SetColor(color);
	glVertex2f(x + width, y + height);
	SetColor(color);
	glVertex2f(x + width, y);
	glEnd();
}

void StrokeRect(float x, float y, float width, float height, Color color) {
	glBegin(GL_LINE_LOOP);
	SetColor(color);
	glVertex2f(x, y);
	SetColor(color);
	glVertex2f(x, y + height);
	SetColor(color);
	glVertex2f(x + width, y + height);
	SetColor(color);
	glVertex2f(x + width, y);
	glEnd();
}

void Translate(float x, float y) {
	glTranslatef(x, y, 0.0f);
}

void Rotate(float angle) {
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void SaveContext() {
	glPushMatrix();
}

void RestoreContext() {
	glPopMatrix();
}

int GetWidth() {
	// https://www.opengl.org/resources/libraries/glut/spec3/node70.html
	return glutGet(GLUT_WINDOW_WIDTH);
}

int GetHeight() {
	// https://www.opengl.org/resources/libraries/glut/spec3/node70.html
	return glutGet(GLUT_WINDOW_HEIGHT);
}

void FillCircle(float x, float y, float radius, Color color) {
	float i = 0.0f;
	SetColor(color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // Center
	for (i = 0.0f; i <= 360; i++) {
		glVertex2f(
			radius * cos(M_PI * i / 180.0) + x,
			radius * sin(M_PI * i / 180.0) + y);
	}
	glEnd();
}

void StrokeCircle(float x, float y, float radius, Color color) {
	float i = 0.0f;
	SetColor(color);
	glBegin(GL_LINE_LOOP);
	// glVertex2f(x, y); // Center
	for (i = 0.0f; i <= 360; i++) {
		glVertex2f(
			radius * cos(M_PI * i / 180.0) + x,
			radius * sin(M_PI * i / 180.0) + y);
	}
	glEnd();
}

void Line(float x1, float y1, float x2, float y2, Color color) {
	SetColor(color);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void Scale(float scale) {
	glScalef(scale, scale, scale);
}
