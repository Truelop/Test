#ifndef CORE_WHEEL_H
#define CORE_WHEEL_H

#include "base.h"

typedef struct Wheel {

  // speed
  float speed;

} Wheel;

Wheel WheelBuild();
void WheelRender(Wheel* Wheel, int x, int y);

#endif /* CORE_WHEEL_H */