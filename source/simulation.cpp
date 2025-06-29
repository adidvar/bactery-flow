#include <algorithm>
#include <iostream>

#include "simulation.hpp"

#include "selection.hpp"

const float radius = 30;

Simulation::Simulation() {}

void Simulation::PushBactery(Bacterium b)
{
  b.PlaceRandomly();
  field_.GetBacterium().push_back(std::shared_ptr<Bacterium>(new Bacterium(b)));
}

void Simulation::PushFood(const Food& bacterium)
{
  std::shared_ptr<Food> b(new Food(bacterium));
  field_.GetEats().push_back(b);
}

void Simulation::Run(float delta_time)
{
  for (auto& bactery : field_.GetBacterium()) {
    bactery->Play(delta_time);
  }
  auto it = std::partition(field_.GetBacterium().begin(),
                           field_.GetBacterium().end(),
                           [](const auto& b) { return b->GetEnergy() > 0; });

  for (auto i = it; i != field_.GetBacterium().end(); ++i) {
    assert(*it != nullptr);
    dead_.push_back(*i);
  }

  field_.GetBacterium().erase(it, field_.GetBacterium().end());

  for (auto b : field_.GetBacterium()) {
    for (auto e : field_.GetEats()) {
      if (abs(b->GetX() - e->GetX()) < radius
          && abs(b->GetY() - e->GetY()) < radius && e->GetAlive())
      {
        e->SetAlive(false);
        b->PushEnergy(50);
        b->Eat();
      }
    }
  }

  auto ite = std::remove_if(field_.GetEats().begin(),
                            field_.GetEats().end(),
                            [](auto b) { return b->GetAlive() == false; });
  field_.GetEats().erase(ite, field_.GetEats().end());

  from_epoch_start += delta_time;
  from_last_food_spawn_ += delta_time;

  // if (from_last_food_spawn_ > 2) {
  //  auto f = Food(GetField());
  //  f.PlaceRandomly();
  //  PushFood(f);
  // from_last_food_spawn_ = 0;
  // }
  if (field_.GetBacterium().empty()) {
    InitNewGeneration();
  }
}

void Simulation::InitRandomly()
{
  for (size_t i = 0; i < 100; i++) {
    auto b = Bacterium(GetField());
    b.RandomGen();
    PushBactery(b);
  }
  for (size_t i = 0; i < 100; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }
}

void Simulation::InitNewGeneration()
{
  field_.GetBacterium().clear();
  field_.GetEats().clear();

  field_.GetBacterium() = Selection(dead_);
  for (auto& b : field_.GetBacterium()) {
    b->PlaceRandomly();
  }
  dead_.clear();

  for (size_t i = 0; i < 1000; i++) {
    auto f = Food(GetField());
    f.PlaceRandomly();
    PushFood(f);
  }

  assert(dead_.size() == 0);
  assert(field_.bacteria_.size() == 100);
}

const Field& Simulation::GetField() const
{
  return field_;
}
