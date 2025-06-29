#ifndef FIELD_HPP
#define FIELD_HPP

#include <memory>
#include <vector>

class Food;
class Bacterium;

class Field
{
  friend class Simulation;

public:
  std::vector<std::shared_ptr<Food>>& GetEats();
  std::vector<std::shared_ptr<Bacterium>>& GetBacterium();

  const std::vector<std::shared_ptr<Food>>& GetEats() const;
  const std::vector<std::shared_ptr<Bacterium>>& GetBacterium() const;

  int GetRange() const;

private:
  int map_range_ = 1000;
  std::vector<std::shared_ptr<Food>> foods_;
  std::vector<std::shared_ptr<Bacterium>> bacteria_;
};

#include "food.hpp"
#include "bacterium.hpp"

#endif
