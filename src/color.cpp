#include "color.hpp"

auto Color::uchar2float(uchar u) -> float {
  char u0 = u - 128;
  float u1 = u0 / 128.0f;
  return u1;
}

auto Color::from_fl_color(Fl_Color color) -> Color {
  uchar r0, g0, b0;
  Fl::get_color(color, r0, g0, b0);

  auto r1 = Color::uchar2float(r0);
  auto g1 = Color::uchar2float(g0);
  auto b1 = Color::uchar2float(b0);

  return Color{r1, g1, b1};
}
