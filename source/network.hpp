#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Eigen/Dense>
#include <vector>

/**
 * @brief The Network class describes network
 */
class Network final {
 public:
  Network(std::vector<int> layers_sizes);
  Network(const Network& other) = default;

  Eigen::VectorXf Calculate(const Eigen::VectorXf& input) const;

  void GenerateRandomly();
  void MakeMutation();
  void MakeCrossing(const Network& net);

 private:
  std::vector<int> layers_size_;
  std::vector<Eigen::MatrixXf> matrixes_;
};

#endif
