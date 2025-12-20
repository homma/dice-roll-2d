#pragma once

#include "lt_gl_window.hpp"
#include "node.hpp"
#include "world.hpp"
#include <vector>

struct Scene {
  float fps = 1 / 60.0;

  Fl_Timestamp last_update_time;

  Lt_Gl_Window &window;

  World world;
  b2WorldId world_id;

  std::vector<PlatformNode> platform;
  std::vector<DiceNode> dices;
  std::vector<HUDNode> hud;

  Scene(Lt_Gl_Window &win);

  auto init() -> void;
  auto deploy_dice() -> void;
  auto start() -> void;
  auto update() -> void;
  auto draw() -> void;

  static auto repeat_callback(void *data) -> void;
};
