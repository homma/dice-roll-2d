#pragma once

#include "color.hpp"
#include "vector2.hpp"
#include <FL/Fl.H>
#include <numbers>

// Mesh
struct Mesh {
  float x, y;     // center
  float rotation; // radian
  Color color;

  Mesh() {};
  virtual ~Mesh() {};

  virtual auto draw() -> void = 0;

protected:
  float rad2deg = 180.0f / std::numbers::pi;
  float deg2rad = std::numbers::pi / 180.0f;
};

// BoxMesh
struct BoxMesh : Mesh {
  float width, height;

  BoxMesh(float left, float top, float width, float height, Fl_Color color);

  ~BoxMesh() {};

  auto draw() -> void;
};

// HexDiceMesh
struct HexDiceMesh : Mesh {
  float radius;
  Color color[6] = {
      Color::from_fl_color(FL_RED),    Color::from_fl_color(FL_LIGHT3),
      Color::from_fl_color(FL_LIGHT2), Color::from_fl_color(FL_BLACK),
      Color::from_fl_color(FL_DARK1),  Color::from_fl_color(FL_LIGHT1)};

  HexDiceMesh(float x, float y, float radius, float rotation);

  ~HexDiceMesh() {};

  auto draw() -> void;

private:
  auto draw_triangle(float radian, Color &color) -> void;
};
