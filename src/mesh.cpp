#include "mesh.hpp"
#include <FL/gl.h>

BoxMesh::BoxMesh(float left, float top, float width, float height,
                 Fl_Color color)
    : width(width), height(height) {
  this->x = left + (width / 2.0f);
  this->y = top + (height / 2.0f);
  this->rotation = 0.0f;

  this->color = Color::from_fl_color(color);
}

auto BoxMesh::draw() -> void {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glTranslatef(this->x, this->y, 0);
  glRotatef(this->rotation * this->rad2deg, 0, 0, 1.0);

  glBegin(GL_POLYGON);

  glColor3f(this->color.r, this->color.g, this->color.b);
  glVertex2f(-this->width, -this->height);
  glVertex2f(-this->width, this->height);
  glVertex2f(this->width, this->height);
  glVertex2f(this->width, -this->height);

  glEnd();

  glPopMatrix();
}

HexDiceMesh::HexDiceMesh(float x, float y, float radius, float rotation)
    : radius(radius) {
  this->x = x;
  this->y = y;
  this->rotation = rotation;
}

auto HexDiceMesh::draw() -> void {
  for (auto i = 0; i < 6; ++i) {
    auto radian = i * this->deg2rad * 60 + this->rotation;
    auto color = this->color[i];

    this->draw_triangle(radian, color);
  }
}

auto HexDiceMesh::draw_triangle(float radian, Color &color) -> void {

  auto p0 = Vector2{this->radius, 0.0};
  auto p1 = Vector2{0.0, 0.0};
  auto p2 = Vector2::from_angle_distance(60, this->radius);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glTranslatef(this->x, this->y, 0);
  glRotatef(radian * this->rad2deg, 0, 0, 1.0);

  glBegin(GL_TRIANGLES);

  glColor3f(color.r, color.g, color.b);
  glVertex2f(p0.x, p0.y);
  glVertex2f(p1.x, p1.y);
  glVertex2f(p2.x, p2.y);

  glEnd();

  glPopMatrix();
}
