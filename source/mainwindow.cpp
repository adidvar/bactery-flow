#include "mainwindow.hpp"

void MainWindow::EventHandle(sf::Event& e) {
  if (e.type == sf::Event::MouseWheelScrolled) {
    transformer_.ScaleCamera(e.mouseWheelScroll.delta);
  }
  if (e.type == sf::Event::MouseButtonPressed &&
      e.mouseButton.button == sf::Mouse::Left) {
    move_mode_ = true;
    last_x_ = e.mouseButton.x;
    last_y_ = e.mouseButton.y;
  }
  if (e.type == sf::Event::MouseButtonReleased &&
      e.mouseButton.button == sf::Mouse::Left)
    move_mode_ = false;
  if (e.type == sf::Event::MouseMoved && move_mode_) {
    transformer_.MoveCameraP(e.mouseMove.x - last_x_, e.mouseMove.y - last_y_);
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
  if (e.type == sf::Event::MouseMoved) {
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
}

void MainWindow::RenderFood() {
  for (auto&& p : simulation_.GetField().GetEats()) {
    float radius = transformer_.Scale(10);
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(radius, radius);
    // shape.setOutlineColor(sf::Color::White);
    // shape.setOutlineThickness(transformer_.Scale(2));
    sf::Vector2f after(transformer_.ScaleW(p->GetX()),
                       transformer_.ScaleH(p->GetY()));
    if (after.x < 0.0 || after.x > width_ || after.y < 0.0 || after.y > height_)
      continue;
    shape.setPosition(after);
    window_.draw(shape);
  }
}

void MainWindow::RenderBactery() {
  for (auto&& p : simulation_.GetField().GetBacterium()) {
    float radius = transformer_.Scale(20 * p->GetEnergy() / 100);
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    // shape.setOutlineColor(sf::Color::White);
    // shape.setOutlineThickness(transformer_.Scale(2));
    shape.setOrigin(radius, radius);
    sf::Vector2f after(transformer_.ScaleW(p->GetX()),
                       transformer_.ScaleH(p->GetY()));
    if (after.x < 0.0 || after.x > width_ || after.y < 0.0 || after.y > height_)
      continue;
    shape.setPosition(after);
    window_.draw(shape);
  }
}

sf::ContextSettings settings(0,0,8);

MainWindow::MainWindow(size_t width, size_t height)
    : transformer_(width, height),
      window_(sf::VideoMode(width, height), "Bacteries",sf::Style::Default,settings),
      width_(width),
      height_(height) {
  window_.setFramerateLimit(60);
  simulation_.InitRandomly();
}

int MainWindow::MainLoop() {
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  float range = simulation_.GetField().GetRange();
  sf::CircleShape scene;

  scene.setFillColor(sf::Color::White);
  scene.setOutlineThickness(2);
  scene.setPointCount(128);

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      EventHandle(event);
      if (event.type == sf::Event::KeyReleased &&
          event.key.code == sf::Keyboard::Space) {
        fast_mode_ = !fast_mode_;
        window_.setFramerateLimit(fast_mode_ ? 2000 : 60);
      }
      if (event.type == sf::Event::Closed) window_.close();
    }

    window_.clear();

    scene.setRadius(transformer_.Scale(range)* 1.8);
    scene.setPosition(
        {transformer_.ScaleW(-range*1.8), transformer_.ScaleH(-range*1.8)});
    window_.draw(scene);

    RenderFood();
    RenderBactery();

    window_.display();

    simulation_.Run(1.0 / 2);
  }

  return 0;
}
/*
if (core.get() == nullptr) {
  RenderFileMenu();
  return;
}

if (core->IsLoading()) {
  DrawText(std::to_string(core->GetProgress()), sf::Color::Red, 40,
           {width / 2.0f, height / 2.0f}, {0.5, 0.5});
  window.display();
  return;
}

DrawText(core->GetTimeDump(), sf::Color::White, 20);

if (console_e) DrawText(console.Text(), sf::Color::White, 20, {0, 400});

if (core->SlowDownWarning())
  DrawText("Slow down error", sf::Color::Red, 40, {width / 2.0f, height / 2.0f},
           {0.5, 1.35});

DrawText(std::to_string(core->GetSpeed()), sf::Color::Red, 20,
         {static_cast<float>(width), 0}, {1, 0});

RenderPlanets();

window.display();

    void DrawText(std::string txt, sf::Color color, size_t size,
                  sf::Vector2f position, sf::Vector2f relative_origin) {
*/
/*
sf::Text text(txt, mfont, size);
text.setFillColor(color);
text.setStyle(sf::Text::Bold);

 sf::FloatRect textRect = text.getLocalBounds();
 text.setOrigin(textRect.width * relative_origin.x,
                textRect.height * relative_origin.y);
 text.setPosition(position.x, position.y);
 window.draw(text);
*/
