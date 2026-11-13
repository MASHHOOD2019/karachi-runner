// Author: Mashhood Ali
#include "Pothole.h"

// Flat on the road surface (y = 620), only 16 px tall.
Pothole::Pothole(float startX)
    : GameObject(startX, 620 - 16), Obstacle(startX, 620 - 16, 1, 90, 16)
{
}

void Pothole::draw(sf::RenderWindow& window)
{
    // A dark flat ellipse pressed into the road
    sf::CircleShape hole(26);
    hole.setScale({1.7f, 0.32f});
    hole.setPosition({x + 2, y + 2});
    hole.setFillColor(sf::Color(12, 10, 16));
    window.draw(hole);

    sf::CircleShape inner(16);
    inner.setScale({1.7f, 0.30f});
    inner.setPosition({x + 18, y + 5});
    inner.setFillColor(sf::Color(35, 30, 40));
    window.draw(inner);
}

std::string Pothole::getKind()
{
    return "Pothole";
}
