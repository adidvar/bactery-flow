#ifndef FOOD_HPP
#define FOOD_HPP

#include "field.hpp"

class Food
{
public:
  Food(const Field& field);

  float GetX() const;
  float GetY() const;
  bool GetAlive() const;
  void SetAlive(bool alive);

  void PlaceRandomly();

private:
  float x_, y_;
  bool alive_ = true;
  const Field& field_;
};

#endif
