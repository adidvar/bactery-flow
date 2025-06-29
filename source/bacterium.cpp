#include "bacterium.hpp"

#include "food.hpp"

Bacterium::Bacterium(const Field& field, const Network& net)
    : field_(field)
    , network_(net)
{
}

Bacterium::Bacterium(const Field& field)
    : field_(field)
    , network_({2, 8, 8, 2})
{
}

float Bacterium::GetX() const
{
  return x_;
}

float Bacterium::GetY() const
{
  return y_;
}

float Bacterium::GetSpeedX() const
{
  return speed_x_;
}

float Bacterium::GetSpeedY() const
{
  return speed_y_;
}

int Bacterium::GetEaten() const
{
  return eaten_;
}

float Bacterium::GetEnergy() const
{
  return energy_;
}

void Bacterium::PushEnergy(float energy)
{
  energy_ += energy;
  energy_ = std::min<float>(energy_, 150);
}

void Bacterium::Eat()
{
  eaten_++;
}

Network Bacterium::GetNetwork()
{
  return network_;
}

const Field& Bacterium::GetField() const
{
  return field_;
}

void Bacterium::Play(float delta_time)
{
  Eigen::VectorXf input(2);
  // input(0) = energy_;
  // input(0) = x_ / field_.GetRange();
  // input(1) = y_ / field_.GetRange();
  float mind = std::numeric_limits<float>::max();
  if (field_.GetEats().size() != 0) {
    std::shared_ptr<Food> cFood;
    for (auto food : field_.GetEats()) {
      float d = sqrt(pow(x_ - food->GetX(), 2) + pow(y_ - food->GetY(), 2));
      if (d < mind) {
        mind = d;
        cFood = food;
      }
    }
    float size = field_.GetRange();
    input(0) = (cFood->GetX() - x_) / (mind + 0.001);
    input(1) = (cFood->GetY() - y_) / (mind + 0.001);
  } else {
    input(0) = 0;
    input(1) = 0;
  }

  const float max_force = 50;
  const float control_force = 150;

  auto output = network_.Calculate(input);

  float control_ax = control_force * output(0);
  float control_ay = control_force * output(1);

  float distance = std::sqrt(x_ * x_ + y_ * y_);
  float range = field_.GetRange() * 2.0;

  float norm_x = (distance > 0) ? -x_ / distance : 0.0f;
  float norm_y = (distance > 0) ? -y_ / distance : 0.0f;

  float control_weight = std::clamp(1.0f - (distance / range), 0.0f, 1.0f);
  float force_weight = 1.0f - control_weight;

  float center_ax = norm_x * max_force;
  float center_ay = norm_y * max_force;

  float final_ax = control_ax * control_weight + center_ax * force_weight;
  float final_ay = control_ay * control_weight + center_ay * force_weight;

  float speed_x = final_ax * delta_time;
  float speed_y = final_ay * delta_time;

  x_ += speed_x;
  y_ += speed_y;

  speed_x_ = speed_x;
  speed_y_ = speed_y;

  /*
  x_ = std::min<float>(x_, field_.GetRange());
  y_ = std::min<float>(y_, field_.GetRange());

  x_ = std::max<float>(x_, -field_.GetRange());
  y_ = std::max<float>(y_, -field_.GetRange());
  */

  energy_ -= 5 * delta_time;
  // energy_ = std::min<float>(energy_, 1000);
  energy_ = std::max<float>(energy_, 0);
}

void Bacterium::PlaceRandomly()
{
  float range = field_.GetRange();
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
  float radius = std::sqrt(static_cast<float>(rand()) / RAND_MAX) * range;

  x_ = radius * std::cos(angle);
  y_ = radius * std::sin(angle);
  energy_ = 100;
}

void Bacterium::Mutation()
{
  network_.MakeMutation();
}

void Bacterium::RandomGen()
{
  network_.GenerateRandomly();
}

void Bacterium::Crossing(const Bacterium& b)
{
  network_.MakeCrossing(b.network_);
}
