#include "scene.hpp"
#include "mesh.hpp"

auto Scene::repeat_callback(void *data) -> void {
  auto scene = (Scene *)data;
  scene->update();
  Fl::repeat_timeout(scene->fps, Scene::repeat_callback, scene);
}

Scene::Scene(Lt_Gl_Window &win) : window(win) {
  this->world = World();
  this->world_id = world.id;

  win.draw_callback([&](Lt_Gl_Window &win) { this->draw(); });
}

auto Scene::init() -> void {
  // remove callback
  Fl::remove_timeout(Scene::repeat_callback);

  // destroy world
  b2DestroyWorld(this->world_id);

  // create world
  this->world = World();
  this->world_id = world.id;

  // clear nodes
  this->platform.clear();
  this->dices.clear();
  this->hud.clear();
}

auto Scene::deploy_dice() -> void {
  // create and add walls and a floor
  auto green = 61;
  auto left_wall = PlatformNode(world_id, 0.0, 0.0, 10.0, 480.0, 61);
  this->platform.push_back(left_wall);

  auto right_x = 640 - 10;
  auto right_wall = PlatformNode(world_id, right_x, 0.0, 10.0, 480.0, green);
  this->platform.push_back(right_wall);

  auto bottom_y = 480 - 10;
  auto bottom_floor = PlatformNode(world_id, 0.0, bottom_y, 640.0, 10.0, green);
  this->platform.push_back(bottom_floor);

  // create and add dices
  {
    float x = 300.0;
    float y = 0.0;
    float radius = 30.0;
    float rotation = 0.0;
    auto d0 = DiceNode(world_id, x, y, radius, rotation);
    this->dices.push_back(d0);
  }

  {
    float x = 330.0;
    float y = 130.0;
    float radius = 30.0;
    float rotation = 0.0;
    auto d1 = DiceNode(world_id, x, y, radius, rotation);
    this->dices.push_back(d1);
  }

  // create and add HUD
  {
    float x = 30.0;
    float y = 30.0;
    auto h0 = HUDNode(x, y, this->dices);
    this->hud.push_back(h0);
  }
}

auto Scene::start() -> void {
  this->last_update_time = Fl::now();

  for (auto &node : this->dices) {
    auto base = 100000000000000.0;
    auto rnd = std::rand() % 100 + 1;
    auto torque = -base * rnd;
    b2Body_ApplyTorque(node.body_id, torque, false);
  }

  Fl::add_timeout(this->fps, Scene::repeat_callback, this);
}

auto Scene::update() -> void {
  auto now = Fl::now();
  auto delta = Fl::seconds_between(now, last_update_time);
  this->last_update_time = now;

  this->world.update(delta);

  for (auto &node : this->platform) {
    node.update();
  }

  for (auto &node : this->dices) {
    node.update();
  }

  for (auto &node : this->hud) {
    node.update();
  }

  // to be fixed
  this->window.redraw();
}

auto Scene::draw() -> void {
  this->window.make_current();

  if (not window.valid()) {
    glLoadIdentity();
    glViewport(0, 0, window.pixel_w(), window.pixel_h());
    glOrtho(0, window.w(), window.h(), 0, 0, 1);
    window.valid(1);
  };

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &node : this->platform) {
    node.draw();
  }

  for (auto &node : this->dices) {
    node.draw();
  }

  for (auto &node : this->hud) {
    node.draw();
  }

  glFlush();
}
