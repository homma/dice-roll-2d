#pragma once

#include "vector2.hpp"
#include <vector>

struct Model {
  virtual ~Model() {};

  virtual auto get_points() -> std::vector<Vector2> = 0;
};

struct BoxModel : Model {
  float width, height;

  BoxModel(float width, float height) : width(width), height(height) {};
  ~BoxModel() {};

  auto get_points() -> std::vector<Vector2>;
};

struct HexModel : Model {
  float radius;

  HexModel(float radius) : radius(radius) {};
  auto get_points() -> std::vector<Vector2>;
};
