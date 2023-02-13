#include <core/base.h>
#include <core/controller.h>
#include <core/env.h>
#include <core/perlin.h>
#include <core/rover.h>

#ifdef TEST
#include <tests/all.h>
#endif

float FPS = 30.0f;
Env env;
Rover rover;
ControllerOutput output = {0};
EnvCell customMapper(EnvCell ec);
EnvCell customUpdater(EnvCell ec);

void SimulationLoop(float dt) {
	/* Update simulation */
	SimulationUpdate(dt); // update frame

	/* Render simulation */
	DisplayClear();
	EnvRender(&env);
	ControllerOutputRender(&output);
	RoverRender(&rover);
	DisplayFlush();
}

void SimulationUpdate(float dt) {
	/* update environment */
	EnvUpdate(&env, customUpdater);

	/* update rover's sensors environment simuled based */
	RoverEmulateEnv(&rover, &env);

	/* execute the controller of the rover */
	output = ControllerRover(&rover, dt);

	/* send command to motors */
	RoverSetSpeedHelper(&rover, output.speedLeft, output.speedRight);

	/* update the rover position in the world */
	RoverUpdatePosition(&rover, dt);
}

int SimulationMain(int argc, char **argv) {
	// Init
	env = *EnvCreate(customMapper);
	rover = RoverBuild();
	RoverPlace(&rover, 10, 20, 53);

	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("max_test_suite", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "max_test_1", max_test_1)) ||
		(NULL == CU_add_test(pSuite, "max_test_2", max_test_2)) ||
		(NULL == CU_add_test(pSuite, "max_test_3", max_test_3)) ||
		(NULL == CU_add_test(pSuite, "max_test_4", max_test_4)) ||
		(NULL == CU_add_test(pSuite, "max_test_5", max_test_5)) ||
		(NULL == CU_add_test(pSuite, "max_test_6", max_test_6))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Run all tests using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);

	// Run all tests using the automated interface
	CU_automated_run_tests();
	CU_list_tests_to_file();

	// Run all tests using the console interface
	// CU_console_run_tests();

	/* Clean up registry and return */
	CU_cleanup_registry();
	return CU_get_error();
}

EnvCell customMapper(EnvCell ec) {
	vec2 pos = ec.cell.position;
	ec.temperature = perlin2d(pos.x + 30, pos.y + 5, 0.1f, 1);
	ec.pressure = perlin2d(pos.x, pos.y, 0.5f, 2);
	ec.cell.color = ColorMake(ec.temperature * 255.0f, 0, 0, 255);
	return ec;
}

EnvCell customUpdater(EnvCell ec) {
	ec.a.x += 10.0f / (1000.0f / FPS);
	ec.a.y += 7.0f / (1000.0f / FPS);
	if (!ec.c)
		ec.c = 1;
	ec.b += ec.c * 3.0f / (1000.0f / FPS);
	if (ec.b > 4.0f) {
		ec.c *= -1;
	} else if (ec.b < 1.0f) {
		ec.c *= -1;
	}
	vec2 pos = ec.cell.position;
	ec.temperature = perlin2d(
		pos.x + ec.a.x + 30, pos.y + ec.a.y + 5, 0.1f, 1 + ec.b * 2.0f);
	ec.pressure = perlin2d(pos.x + ec.a.x, pos.y + ec.a.y, 0.5f, 2);
	ec.cell.color = ColorMake(ec.temperature * 255.0f, 0, 0, 255);
	return ec;
}
