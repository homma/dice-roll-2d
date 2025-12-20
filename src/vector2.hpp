#pragma once

struct Vector2 {
  float x;
  float y;

  static auto from_angle_distance(float degree, float distance) -> Vector2;
  auto translate(Vector2 &move) -> void;
};
