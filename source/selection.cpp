#include "selection.hpp"

#include <iostream>

std::vector<std::shared_ptr<Bacterium>> Selection(
    const std::vector<std::shared_ptr<Bacterium>> &from) {
  std::vector<std::shared_ptr<Bacterium>> from_copy = from;
  std::sort(from_copy.rbegin(), from_copy.rend(),
            [](auto b1, auto b2) { return b1->GetEaten() < b2->GetEaten(); });

  std::cout << from_copy.front()->GetEaten() << std::endl;

  int sample_count = SelectioSettings::Generation * SelectioSettings::Sample;
  std::vector<Network> sample;
  for (int i = 0; i < sample_count; i++)
    sample.push_back(from_copy[i]->GetNetwork());

  int generation_count = SelectioSettings::Generation - sample_count;
  int mutation_count = SelectioSettings::Mutation * generation_count;
  int crossing_count = SelectioSettings::Crossing * generation_count;

  std::vector<Network> mutation;
  for (int i = 0; i < mutation_count; i++) {
    mutation.push_back(sample[i % sample.size()]);
    mutation.back().MakeMutation();
  }

  std::vector<Network> crossing;
  for (int i = 0; i < sample_count; i++) {
    for (int j = 0; j < sample_count; j++) {
      if (i == j) continue;
      if (crossing.size() == crossing_count) break;

      crossing.push_back(sample[i]);
      crossing.back().MakeCrossing(sample[j]);
    }
  }

  int random_count = SelectioSettings::Generation - sample.size() -
                     mutation.size() - crossing.size();
  Network network = Bacterium(*from_copy.front()).GetNetwork();
  const Field &field = Bacterium(*from_copy.front()).GetField();
  std::vector<Network> random;
  for (int i = 0; i < random_count; i++) {
    random.push_back(network);
    random.back().GenerateRandomly();
  }

  std::vector<std::shared_ptr<Bacterium>> result;

  for (const auto &b : sample)
    result.push_back(std::shared_ptr<Bacterium>(new Bacterium(field, b)));
  for (const auto &b : mutation)
    result.push_back(std::shared_ptr<Bacterium>(new Bacterium(field, b)));
  for (const auto &b : crossing)
    result.push_back(std::shared_ptr<Bacterium>(new Bacterium(field, b)));
  for (const auto &b : random)
    result.push_back(std::shared_ptr<Bacterium>(new Bacterium(field, b)));

  return result;
}
