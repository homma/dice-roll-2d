#include "lt_gl_window.hpp"

Lt_Gl_Window::Lt_Gl_Window(int x, int y, int w, int h, const char *label)
    : Fl_Gl_Window(x, y, w, h, label) {}

auto Lt_Gl_Window::draw_callback(std::function<void(Lt_Gl_Window &)> draw_cb)
    -> void {
  this->draw_callback_fn = draw_cb;
}

auto Lt_Gl_Window::draw() -> void {
  this->draw_callback_fn(*this);
  Fl_Gl_Window::draw();
}
