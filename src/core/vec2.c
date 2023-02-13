#include <core/vec2.h>

vec2 Vec2Make(float x, float y) {
	return (vec2){x, y};
}

vec2 Vec2Clone(vec2 v) {
	return Vec2Make(v.x, v.y);
}

float Vec2Argument(vec2 v) {
	return atan2(v.y, v.x);
}

float Vec2Magnitude(vec2 v) {
	return sqrt(Vec2MagnitudeSquared(v));
}

float Vec2MagnitudeSquared(vec2 v) {
	return Vec2Dot(v, v);
}

float Vec2Dot(vec2 v, vec2 u) {
	return v.x * u.x + v.y * u.y;
}

float Vec2Cross(vec2 v, vec2 u) {
	return v.x * u.y - v.y * u.x;
}

vec2 Vec2Add(vec2 v, vec2 u) {
	return Vec2Make(v.x + u.x, v.y + u.y);
}

vec2 Vec2AddScalar(vec2 v, float scalar) {
	return Vec2Add(v, Vec2Make(scalar, scalar));
}

vec2 Vec2Sub(vec2 v, vec2 u) {
	return Vec2Make(v.x - u.x, v.y - u.y);
}

vec2 Vec2SubScalar(vec2 v, float scalar) {
	return Vec2Sub(v, Vec2Make(scalar, scalar));
}

vec2 Vec2Mul(vec2 v, vec2 u) {
	return Vec2Make(v.x * u.x, v.y * u.y);
}

vec2 Vec2MulScalar(vec2 v, float scalar) {
	return Vec2Mul(v, Vec2Make(scalar, scalar));
}

vec2 Vec2Div(vec2 v, vec2 u) {
	return Vec2Make(v.x / u.x, v.y / u.y);
}

vec2 Vec2DivScalar(vec2 v, float scalar) {
	return Vec2Div(v, Vec2Make(scalar, scalar));
}

vec2 Vec2Negate(vec2 v) {
	return Vec2Make(-v.x, -v.y);
}

vec2 Vec2Normalize(vec2 v) {
	return Vec2DivScalar(v, Vec2Magnitude(v));
}

float Vec2Distance(vec2 v, vec2 u) {
	return Vec2Magnitude(Vec2Sub(v, u));
}

float Vec2Angle(vec2 v, vec2 u) {
	return Vec2Argument(Vec2Sub(v, u));
}

vec2 Vec2Transpose(vec2 v) {
	return Vec2Make(v.y, v.x);
}

vec2 Vec2Orthogonal(vec2 v) {
	return Vec2Make(-v.y, v.x);
}

vec2 Vec2Project(vec2 v, vec2 u) {
	return Vec2MulScalar(v, Vec2Dot(v, Vec2Normalize(u)));
}

vec2 Vec2Floor(vec2 v) {
	return Vec2Make(floor(v.x), floor(v.x));
}

vec2 Vec2Ceil(vec2 v) {
	return Vec2Make(floor(v.x), floor(v.x));
}

vec2 Vec2Round(vec2 v) {
	return Vec2Make(floor(v.x), floor(v.x));
}

vec2 Vec2Abs(vec2 v) {
	return Vec2Make(floor(v.x), floor(v.x));
}

bool Vec2Equal(vec2 v, vec2 u) {
  return EqualFloat(v.x,u.x) && EqualFloat(v.y,u.y);
}