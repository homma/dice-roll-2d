#include "model.hpp"

auto BoxModel::get_points() -> std::vector<Vector2> {
  auto half_w = width / 2.0f;
  auto half_h = height / 2.0f;

  auto p0 = Vector2{-half_w, -half_h};
  auto p1 = Vector2{-half_w, half_h};
  auto p2 = Vector2{half_w, half_h};
  auto p3 = Vector2{half_w, -half_h};

  return std::vector<Vector2>{p0, p1, p2, p3};
}

auto HexModel::get_points() -> std::vector<Vector2> {
  std::vector<Vector2> vec;
  for (auto i = 0; i < 6; ++i) {
    auto p = Vector2::from_angle_distance(i * 60, this->radius);
    vec.push_back(p);
  }

  return vec;
}
