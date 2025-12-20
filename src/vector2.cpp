#include "vector2.hpp"
#include <cmath>
#include <numbers>

auto Vector2::from_angle_distance(float degree, float distance) -> Vector2 {
  auto deg2rad = std::numbers::pi / 180.0;

  auto theta = degree * deg2rad;
  float x = std::cos(theta) * distance;
  float y = std::sin(theta) * distance;

  return Vector2{x, y};
}

auto Vector2::translate(Vector2 &move) -> void {
  this->x += move.x;
  this->y += move.y;
}
