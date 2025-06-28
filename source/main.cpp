#include <chrono>
#include <random>

#include "mainwindow.hpp"

int main() {
  srand(std::chrono::high_resolution_clock().now().time_since_epoch().count());
  MainWindow window(1280, 720);
  return window.MainLoop();
}
