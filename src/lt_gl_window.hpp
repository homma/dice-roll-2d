#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <functional>

// Lt_Gl_Window
struct Lt_Gl_Window : public Fl_Gl_Window {
  Lt_Gl_Window(int x, int y, int w, int h, const char *label = 0);
  auto draw_callback(std::function<void(Lt_Gl_Window &)>) -> void;

protected:
  auto draw() -> void;

private:
  std::function<void(Lt_Gl_Window &)> draw_callback_fn = [](Lt_Gl_Window &win) {
  };
};
