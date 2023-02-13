#include <core/utils.h>

/**
 * Convert km/h to m/s
 */
float KMHToMS(float speed) {
	return speed / 3.6f;
}

/**
 * Convert m/s to km/h
 */
float MSToKMH(float speed) {
	return speed * 3.6f;
}

bool EqualFloat(float a, float b) {
	return a + EPS > b && a - EPS < b;
}

bool EqualFloatEps(float a, float b, float eps) {
	return a + eps > b && a - eps < b;
}

float ToDeg(float rad) {
	return rad * 180.0f / M_PI;
}

float ToRad(float deg) {
	return deg * M_PI / 180.0f;
}

float RandomFloat(float min, float max) {
	float scale = rand() / (float)RAND_MAX;
	return min + scale * (max - min);
}