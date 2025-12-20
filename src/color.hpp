#pragma once

#include <FL/Enumerations.H>
#include <FL/Fl.H>

struct Color {
  float r, g, b;

  static auto from_fl_color(Fl_Color color) -> Color;

private:
  static auto uchar2float(uchar u) -> float;
};
