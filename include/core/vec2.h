#ifndef CORE_VEC2_H
#define CORE_VEC2_H

#include "base.h"
#include "utils.h"

typedef struct vec2 {
  float x;
  float y;
} vec2;

#define Vec2Zero (vec2){0.0f,0.0f};

vec2 Vec2Make(float x, float y);
vec2 Vec2Clone(vec2 v);
float Vec2Argument(vec2 v);
float Vec2Magnitude(vec2 v);
float Vec2MagnitudeSquared(vec2 v);
float Vec2Dot(vec2 v, vec2 u);
float Vec2Cross(vec2 v, vec2 u);
vec2 Vec2Add(vec2 v, vec2 u);
vec2 Vec2AddScalar(vec2 v, float scalar);
vec2 Vec2Sub(vec2 v, vec2 u);
vec2 Vec2SubScalar(vec2 v, float scalar);
vec2 Vec2Mul(vec2 v, vec2 u);
vec2 Vec2MulScalar(vec2 v, float scalar);
vec2 Vec2Div(vec2 v, vec2 u);
vec2 Vec2DivScalar(vec2 v, float scalar);
vec2 Vec2Negate(vec2 v);
vec2 Vec2Normalize(vec2 v);
float Vec2Distance(vec2 v, vec2 u);
float Vec2Angle(vec2 v, vec2 u);
vec2 Vec2Transpose(vec2 v);
vec2 Vec2Orthogonal(vec2 v);
vec2 Vec2Project(vec2 v, vec2 u);
vec2 Vec2Floor(vec2 v);
vec2 Vec2Ceil(vec2 v);
vec2 Vec2Round(vec2 v);
vec2 Vec2Abs(vec2 v);
bool Vec2Equal(vec2 v, vec2 u);


#endif /* CORE_WHEEL_H */