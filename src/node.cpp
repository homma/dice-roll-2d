#include "node.hpp"
#include <FL/gl.h>
#include <cmath>
#include <format>
#include <numbers>

PlatformNode::PlatformNode(b2WorldId world_id, float left, float top,
                           float width, float height, Fl_Color color)
    : world_id(world_id), model(width, height),
      mesh(left, top, width, height, color) {

  // ### init physics ###

  // create body
  auto body_def = b2DefaultBodyDef();

  body_def.type = b2_staticBody;

  auto x = left + (width / 2.0f);
  auto y = top + (height / 2.0f);
  body_def.position = b2Vec2{x, y};

  this->body_id = b2CreateBody(world_id, &body_def);

  // create shape
  auto shape_def = b2DefaultShapeDef();

  auto vector2_points = this->model.get_points();

  const auto n = 4;
  b2Vec2 points[n];

  for (auto i = 0; i < n; ++i) {
    auto p = vector2_points[i];
    points[i] = b2Vec2{p.x, p.y};
  }

  auto hull = b2ComputeHull(points, n);
  auto polygon = b2MakePolygon(&hull, 0.0f);

  b2CreatePolygonShape(this->body_id, &shape_def, &polygon);
}

auto PlatformNode::update() -> void {
  // retrieve physics info

  // get position
  auto offset = b2Vec2{0, 0};
  auto p = b2Body_GetWorldPoint(this->body_id, offset);

  // get rotation angle
  auto rotation = b2Body_GetRotation(this->body_id);
  auto radians = b2Rot_GetAngle(rotation);

  // update mesh
  this->mesh.x = p.x;
  this->mesh.y = p.y;
  this->mesh.rotation = radians;
}

auto PlatformNode::draw() -> void { this->mesh.draw(); }

DiceNode::DiceNode(b2WorldId world_id, float x, float y, float radius,
                   Fl_Color color)
    : world_id(world_id), x(x), y(y), radius(radius), model(radius),
      mesh(x, y, radius, color) {

  // ### init physics ###

  // create body
  auto body_def = b2DefaultBodyDef();

  body_def.type = b2_dynamicBody;

  body_def.position = b2Vec2{this->x, this->y};

  this->body_id = b2CreateBody(world_id, &body_def);

  // create shape
  auto shape_def = b2DefaultShapeDef();
  shape_def.density = 0.01f;
  shape_def.material.friction = 0.1f;
  shape_def.material.restitution = 0.6f;

  auto vector2_points = this->model.get_points();

  const auto n = 6;
  b2Vec2 points[n];

  for (auto i = 0; i < n; ++i) {
    auto p = vector2_points[i];
    points[i] = b2Vec2{p.x, p.y};
  }

  auto hull = b2ComputeHull(points, n);
  auto polygon = b2MakePolygon(&hull, 0.0f);

  b2CreatePolygonShape(this->body_id, &shape_def, &polygon);
}

auto DiceNode::update() -> void {
  // retrieve physics info

  // get position
  auto offset = b2Vec2{0, 0};
  auto p = b2Body_GetWorldPoint(this->body_id, offset);

  // get rotation angle
  auto rotation = b2Body_GetRotation(this->body_id);
  auto radians = b2Rot_GetAngle(rotation);

  // update mesh
  this->mesh.x = p.x;
  this->mesh.y = p.y;
  this->mesh.rotation = radians;

  // update number
  auto rad2deg = 180.0 / std::numbers::pi;
  auto degrees = (int)floor(radians * rad2deg) + 180;

  if ((31 <= degrees) and (degrees <= 90)) {
    // around 60
    this->value = 1;
  } else if ((degrees <= 30) or (331 <= degrees)) {
    // around 0
    this->value = 2;
  } else if ((271 <= degrees) and (degrees <= 330)) {
    // around 300
    this->value = 3;
  } else if ((91 <= degrees) and (degrees <= 150)) {
    // around 120
    this->value = 4;
  } else if ((151 <= degrees) and (degrees <= 210)) {
    // around 180
    this->value = 5;
  } else if ((211 <= degrees) and (degrees <= 270)) {
    // around 240
    this->value = 6;
  }
}

auto DiceNode::draw() -> void { this->mesh.draw(); }

HUDNode::HUDNode(float left, float top, std::vector<DiceNode> &dices)
    : left(left), top(top), dices(dices) {}

inline auto HUDNode::update() -> void {
  this->values.clear();

  auto dices = this->dices;
  for (auto &dice : dices) {
    this->values.push_back(dice.value);
  }
}

auto HUDNode::draw() -> void {
  for (auto i = 0; i < this->values.size(); i++) {
    auto x = this->left;
    auto y = this->top + i * 30;
    auto text = std::format("{}", this->values[i]);

    /*
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(3.0, 3.0, 0.0);
    */

    glColor3f(0.0, 0.0, 0.0);
    gl_draw(text.c_str(), x, y);

    // glPopMatrix();
  }
}
