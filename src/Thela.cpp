// Author: Mashhood Ali
#include "Thela.h"

Thela::Thela(float startX)
    : GameObject(startX, 620 - 70), Obstacle(startX, 620 - 70, 1, 100, 70)
{
}

void Thela::draw(sf::RenderWindow& window)
{
    // Wooden platform, a load of boxes, and two big cart wheels
    sf::RectangleShape load({54, 26});
    load.setPosition({x + 20, y + 2});
    load.setFillColor(sf::Color(170, 120, 60));
    window.draw(load);

    sf::RectangleShape loadTop({30, 16});
    loadTop.setPosition({x + 32, y - 12});
    loadTop.setFillColor(sf::Color(200, 150, 80));
    window.draw(loadTop);

    sf::RectangleShape platform({92, 10});
    platform.setPosition({x + 4, y + 30});
    platform.setFillColor(sf::Color(120, 82, 45));
    window.draw(platform);

    sf::RectangleShape handle({26, 6});
    handle.setPosition({x + 78, y + 40});
    handle.setFillColor(sf::Color(100, 68, 38));
    window.draw(handle);

    sf::CircleShape wheelBack(13);
    wheelBack.setPosition({x + 12, y + 42});
    wheelBack.setFillColor(sf::Color(60, 42, 26));
    window.draw(wheelBack);

    sf::CircleShape wheelFront(13);
    wheelFront.setPosition({x + 70, y + 42});
    wheelFront.setFillColor(sf::Color(60, 42, 26));
    window.draw(wheelFront);
}

std::string Thela::getKind()
{
    return "Thela";
}

bool Thela::isLight()
{
    return true;
}
