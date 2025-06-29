#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <vector>

#include <bacterium.hpp>

std::vector<std::shared_ptr<Bacterium>> Selection(
    const std::vector<std::shared_ptr<Bacterium>>& from);

struct SelectioSettings
{
  constexpr const static int Generation = 100;
  constexpr const static float Sample = 0.08;

  constexpr const static float Mutation = 0.5;
  constexpr const static float Crossing = 0.4;
};

#endif
