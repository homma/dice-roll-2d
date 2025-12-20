#pragma once

#include "mesh.hpp"
#include "model.hpp"
#include "node.hpp"
#include <box2d/box2d.h>
#include <vector>

struct Node {
  virtual ~Node() {};

  virtual auto update() -> void = 0;
  virtual auto draw() -> void = 0;
};

struct PlatformNode : Node {
  b2WorldId world_id;
  b2BodyId body_id;

  BoxModel model;
  BoxMesh mesh;

  float left, top, width, height;
  Fl_Color color;

  PlatformNode(b2WorldId world_id, float left, float top, float width,
               float height, Fl_Color color);
  ~PlatformNode() {};

  auto update() -> void;
  auto draw() -> void;
};

struct DiceNode : Node {
  int value = 0;

  b2WorldId world_id;
  b2BodyId body_id;

  HexModel model;
  HexDiceMesh mesh;

  float x, y;
  float radius;
  float rotation = 0.0f;
  Fl_Color color;

  DiceNode(b2WorldId world_id, float x, float y, float radius, Fl_Color color);
  ~DiceNode() {};

  auto update() -> void;
  auto draw() -> void;
};

struct HUDNode : Node {
  // Scene *scene;
  std::vector<DiceNode> &dices;

  float left, top;

  std::vector<int> values;

  HUDNode(float left, float top, std::vector<DiceNode> &dices);
  ~HUDNode() {};

  auto update() -> void;
  auto draw() -> void;
};
