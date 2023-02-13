#include <core/base.h>

void loop();

int main(int argc, char **argv) {
	srand(time(NULL));
	int result;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
	// glutInitWindowPosition(50,100);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Rover");
	DisplayInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glScalef(10.0f, 10.0f, 10.0f);
	glPushMatrix();
	result = SimulationMain(argc, argv);
#ifndef TEST
	glutDisplayFunc(loop);
	glutMainLoop();
#endif
	return result;
}

void loop() {
	Timer timer = TimerMake();
	float dt = 1000.0 / FPS;
	while (true) {
		TimerStart(&timer);
		SimulationLoop(dt);
		TimerStop(&timer);
		float elapsed = TimerGetElapsed(&timer);
		if (elapsed < dt)
			Sleep(dt - elapsed);
	}
}
