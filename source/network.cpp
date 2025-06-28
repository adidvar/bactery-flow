#include "network.hpp"

#include <cmath>

#include "nparam.hpp"

///< generates number in -1 -- 1 range
float GenerateRandom() { return ((float)rand() / RAND_MAX) * 2 - 1; }

Network::Network(std::vector<int> layers_sizes) : layers_size_(layers_sizes) {
  matrixes_.resize(layers_size_.size() - 1);

  for (size_t i = 0; i < matrixes_.size(); i++)
    matrixes_[i] = Eigen::MatrixXf(layers_sizes[i + 1], layers_sizes[i] + 1);
}

Eigen::VectorXf Network::Calculate(const Eigen::VectorXf &input) const {
  Eigen::VectorXf output = input;

  for (const auto &matrix : matrixes_) {
    Eigen::VectorXf with_1_neuro(output.size() + 1);
    with_1_neuro << output, 1;
    output = matrix * with_1_neuro;

    for (int i = 0; i < output.size(); i++) output(i) = std::tanh(output(i));
  }
  return output;
}

void Network::GenerateRandomly() {
  for (auto &layer : matrixes_)
    layer = Eigen::MatrixXf::Random(layer.rows(), layer.cols());
}

void Network::MakeMutation() {
  int size = 0;

  for (auto &matrix : matrixes_) size += matrix.size();

  int mutation_count = std::max<int>(size * MutationSetting::Rate, 1);

  for (int i = 0; i < mutation_count; i++) {
    auto point = rand() % size;

    for (auto &matrix : matrixes_) {
      if (point >= matrix.size())
        point -= matrix.size();
      else {
        auto x = point % matrix.rows();
        auto y = point / matrix.rows();

        auto delta = MutationSetting::Delta * GenerateRandom();
        matrix(x, y) = delta;
        break;
      }
    }
  }
}

void Network::MakeCrossing(const Network &net) {
  for (size_t i = 0; i < matrixes_.size(); i++) {
    for (int x = 0; x < matrixes_[i].rows(); x++)
      for (int y = 0; y < matrixes_[i].cols(); y++) {
        matrixes_[i](x, y) =
            rand() % 2 ? matrixes_[i](x, y) : net.matrixes_[i](x, y);
      }
  }
}
