#pragma once

#include <box2d/box2d.h>

// physics system
struct World {
  b2WorldId id;

  World();

  auto update(float delta_time) -> void;

private:
  float one_meter = 100.0;
  float gravity = 9.8f * one_meter;
  int substep_count = 4;
};
