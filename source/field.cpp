#include "field.hpp"

std::vector<std::shared_ptr<Food> > &Field::GetEats() { return foods_; }

std::vector<std::shared_ptr<Bacterium> > &Field::GetBacterium() {
  return bacteria_;
}

const std::vector<std::shared_ptr<Food> > &Field::GetEats() const {
  return foods_;
}

const std::vector<std::shared_ptr<Bacterium> > &Field::GetBacterium() const {
  return bacteria_;
}

int Field::GetRange() const { return map_range_; }
