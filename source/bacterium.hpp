#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <memory>
#include <vector>

#include "field.hpp"
#include "network.hpp"

class Bacterium {
 public:
  Bacterium(const Field &field, const Network &net);
  Bacterium(const Field &field);

  float GetX() const;
  float GetY() const;
  int GetEaten() const;
  float GetEnergy() const;
  void PushEnergy(float energy);
  void Eat();

  Network GetNetwork();
  const Field &GetField() const;

  void Play(float delta_time);
  void PlaceRandomly();
  void Mutation();
  void RandomGen();
  void Crossing(const Bacterium &b);

 private:
  const Field &field_;
  float x_, y_;
  float energy_ = 100;
  int eaten_ = 0;
  Network network_;
};

#endif
