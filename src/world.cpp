#include "world.hpp"

World::World() {
  // set units
  b2SetLengthUnitsPerMeter(one_meter);

  // create a world
  auto world_def = b2DefaultWorldDef();

  // set gravity
  world_def.gravity.y = this->gravity;

  this->id = b2CreateWorld(&world_def);
}

auto World::update(float delta_time) -> void {
  b2World_Step(this->id, delta_time, this->substep_count);
}
