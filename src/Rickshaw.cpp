// Author: Mashhood Ali
#include "Rickshaw.h"

// The road surface is at y = 620, so the top is 620 - 84.
// GameObject is a virtual base, so this class calls it directly.
Rickshaw::Rickshaw(float startX)
    : GameObject(startX, 620 - 84), Obstacle(startX, 620 - 84, 1, 110, 84)
{
}

void Rickshaw::draw(sf::RenderWindow& window)
{
    // Placeholder shapes in rickshaw colours: green body, yellow
    // roof, black wheels. Pixel art replaces this in the art phase.
    sf::RectangleShape body({86, 44});
    body.setPosition({x + 12, y + 26});
    body.setFillColor(sf::Color(30, 140, 60));
    window.draw(body);

    sf::RectangleShape roof({70, 22});
    roof.setPosition({x + 20, y + 6});
    roof.setFillColor(sf::Color(245, 200, 40));
    window.draw(roof);

    sf::RectangleShape front({16, 34});
    front.setPosition({x + 94, y + 36});
    front.setFillColor(sf::Color(20, 100, 45));
    window.draw(front);

    sf::CircleShape wheelBack(11);
    wheelBack.setPosition({x + 16, y + 62});
    wheelBack.setFillColor(sf::Color(25, 25, 25));
    window.draw(wheelBack);

    sf::CircleShape wheelFront(9);
    wheelFront.setPosition({x + 92, y + 64});
    wheelFront.setFillColor(sf::Color(25, 25, 25));
    window.draw(wheelFront);
}

std::string Rickshaw::getKind()
{
    return "Rickshaw";
}
