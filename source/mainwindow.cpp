#include "mainwindow.hpp"

void MainWindow::EventHandle(sf::Event& e)
{
  if (e.type == sf::Event::MouseWheelScrolled) {
    trailTexture_.clear(sf::Color::Transparent);
    transformer_.ScaleCamera(e.mouseWheelScroll.delta);
  }
  if (e.type == sf::Event::MouseButtonPressed
      && e.mouseButton.button == sf::Mouse::Left)
  {
    move_mode_ = true;
    last_x_ = e.mouseButton.x;
    last_y_ = e.mouseButton.y;
  }
  if (e.type == sf::Event::MouseButtonReleased
      && e.mouseButton.button == sf::Mouse::Left)
  {
    move_mode_ = false;
  }
  if (e.type == sf::Event::MouseMoved && move_mode_) {
    transformer_.MoveCameraP(e.mouseMove.x - last_x_, e.mouseMove.y - last_y_);
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
  if (e.type == sf::Event::MouseMoved) {
    if (move_mode_) {
      trailTexture_.clear(sf::Color::Transparent);
    }
    last_x_ = e.mouseMove.x;
    last_y_ = e.mouseMove.y;
  }
}

void MainWindow::RenderFood()
{
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
    {
      continue;
    }
    shape.setPosition(after);
    window_.draw(shape);
  }
}

void MainWindow::RenderBactery()
{
  sf::RectangleShape fadeRect(sf::Vector2f(width_, height_));
  fadeRect.setFillColor(sf::Color(255, 255, 255, 20));
  trailTexture_.draw(fadeRect, sf::BlendAlpha);

  for (auto&& p : simulation_.GetField().GetBacterium()) {
    float radius =
        transformer_.Scale(20 * std::clamp(p->GetEnergy(), 0.0f, 80.0f) / 100);
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(radius, radius);
    sf::Vector2f after(transformer_.ScaleW(p->GetX()),
                       transformer_.ScaleH(p->GetY()));
    if (after.x < 0.0 || after.x > width_ || after.y < 0.0 || after.y > height_)
    {
      continue;
    }
    shape.setPosition(after);

    float vx = p->GetSpeedX();
    float vy = p->GetSpeedY();
    float speed = std::sqrt(vx * vx + vy * vy);

    const float max_speed = 10.0f;
    float t = std::clamp(speed / max_speed, 0.0f, 1.0f);

    sf::Uint8 r = static_cast<sf::Uint8>(255 * t);
    sf::Uint8 g = static_cast<sf::Uint8>(100 * (1 - t));
    sf::Uint8 b = static_cast<sf::Uint8>(255 * (1 - t));
    shape.setFillColor(sf::Color(r, g, b));

    trailTexture_.draw(shape);

    shape.setFillColor(sf::Color::Black);

    window_.draw(shape);
  }

  trailTexture_.display();

  sf::Sprite fadedTrail(trailTexture_.getTexture());
  fadedTrail.setColor(sf::Color(255, 255, 255, 128));  // 128 = 50% opacity
  window_.draw(fadedTrail);
}

sf::ContextSettings settings(0, 0, 8);

MainWindow::MainWindow(size_t width, size_t height)
    : transformer_(width, height)
    , window_(sf::VideoMode(width, height),
              "Bacteries",
              sf::Style::Default,
              settings)
    , width_(width)
    , height_(height)
{
  window_.setFramerateLimit(60);
  simulation_.InitRandomly();
  trailTexture_.create(width_, height_);
  trailTexture_.clear(sf::Color::Transparent);
  trailSprite_.setTexture(trailTexture_.getTexture());
}

int MainWindow::MainLoop()
{
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
      if (event.type == sf::Event::KeyReleased
          && event.key.code == sf::Keyboard::Space)
      {
        fast_mode_ = !fast_mode_;
        window_.setFramerateLimit(fast_mode_ ? 2000 : 60);
      }
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }

    window_.clear();

    scene.setRadius(transformer_.Scale(range) * 1.8);
    scene.setPosition(
        {transformer_.ScaleW(-range * 1.8), transformer_.ScaleH(-range * 1.8)});
    window_.draw(scene);

    RenderFood();
    RenderBactery();

    window_.display();

    simulation_.Run(1.0 / 8);
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
