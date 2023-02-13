#ifndef CORE_UTILS_H
#define CORE_UTILS_H

#include "base.h"

#define CEILING(x,y) (((x) + (y) - 1) / (y))

#define EPS 0.0001f

/**
 * Convert km/h to m/s
 */
float KMHToMS(float speed);

/**
 * Convert m/s to km/h
 */
float MSToKMH(float speed);

bool EqualFloat(float a, float b);

bool EqualFloatEps(float a, float b, float eps);

float ToDeg(float rad);

float ToRad(float deg);

float RandomFloat(float min, float max);

#endif /* CORE_UTILS_H */