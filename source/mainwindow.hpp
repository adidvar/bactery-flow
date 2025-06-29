#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <filesystem>

#include <SFML/Graphics.hpp>

#include "ptransform.hpp"
#include "simulation.hpp"
#include "food.hpp"

class MainWindow
{
public:
  MainWindow(size_t width, size_t height);
  int MainLoop();

private:
  void EventHandle(sf::Event& e);
  void DrawText(std::string txt,
                sf::Color color,
                size_t size,
                sf::Vector2f position = {0, 0},
                sf::Vector2f relative_origin = {0, 0});

  void RenderFood();
  void RenderBactery();

private:
  Simulation simulation_;
  PTransformer transformer_;
  sf::RenderWindow window_;
  size_t width_, height_;

  sf::RenderTexture trailTexture_;
  sf::Sprite trailSprite_;

  bool move_mode_ = false;
  bool fast_mode_ = false;

  int last_x_ = 0;
  int last_y_ = 0;
};

#endif
