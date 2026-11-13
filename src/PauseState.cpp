// Author: Mashhood Ali
#include "PauseState.h"

PauseState::PauseState(AssetManager& assetManager)
{
    assets = &assetManager;
    resumeRequested = false;
}

void PauseState::handleInput(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        const sf::Event::KeyPressed* key = event.getIf<sf::Event::KeyPressed>();
        if (key != nullptr && key->code == sf::Keyboard::Key::P)
        {
            resumeRequested = true;
        }
    }
}

void PauseState::update(float dt)
{
    (void)dt; // nothing moves on the pause screen, on purpose
}

void PauseState::drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color)
{
    if (!assets->hasFont())
    {
        return;
    }
    sf::Text label(assets->getFont(), text, size);
    label.setFillColor(color);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2});
    label.setPosition({cx, y});
    window.draw(label);
}

void PauseState::draw(sf::RenderWindow& window)
{
    // A dim layer over the frozen scene
    sf::RectangleShape dim({1280, 720});
    dim.setPosition({0, 0});
    dim.setFillColor(sf::Color(10, 8, 20, 170));
    window.draw(dim);

    drawText(window, "PAUSED", 640, 320, 56, sf::Color(250, 200, 110));
    drawText(window, "Press P to resume", 640, 385, 24, sf::Color::White);
}

bool PauseState::isResumeRequested()
{
    return resumeRequested;
}
