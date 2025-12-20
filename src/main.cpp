#include "lt_gl_window.hpp"
#include "node.hpp"
#include "scene.hpp"
#include "vector2.hpp"
#include "world.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

auto main() -> int {

  Fl_Window *win;
  {
    auto width = 800;
    auto height = 600;
    auto left = (Fl::w() - width) / 2.0;
    auto top = (Fl::h() - height) / 2.0;
    auto title = "Dice Roll";
    win = new Fl_Window(left, top, width, height, title);

    win->color(54);
  }

  Lt_Gl_Window *gl_win;
  {
    auto width = 640;
    auto height = 480;
    auto left = (win->w() - width) / 2.0;
    auto top = 30;
    gl_win = new Lt_Gl_Window(left, top, width, height);

    gl_win->color(FL_WHITE);
    gl_win->mode(FL_RGB);
    gl_win->end();
  }

  Fl_Button *button;
  {
    auto width = 300;
    auto height = 40;
    auto left = (win->w() - width) / 2.0;
    auto top = 535;
    auto text = "reroll";
    button = new Fl_Button(left, top, width, height, text);
  }

  button->type(FL_NORMAL_BUTTON);
  button->color(FL_WHITE);

  win->end();
  win->show();

  auto scene = Scene(*gl_win);
  scene.deploy_dice();
  scene.start();

  button->callback(
      [](Fl_Widget *w, void *data) {
        auto scene = (Scene *)data;
        scene->init();
        scene->deploy_dice();
        scene->start();
      },
      (void *)(&scene));

  return Fl::run();
}
