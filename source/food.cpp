#include "food.hpp"
#include <cmath>

Food::Food(const Field &field) : field_(field) {}

float Food::GetX() const { return x_; }

float Food::GetY() const { return y_; }

bool Food::GetAlive() const { return alive_; }

void Food::SetAlive(bool alive) { alive_ = alive; }

void Food::PlaceRandomly() {
  float range = field_.GetRange();
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
  float radius = std::sqrt(static_cast<float>(rand()) / RAND_MAX) * range;

  x_ = radius * std::cos(angle);
  y_ = radius * std::sin(angle);
}
