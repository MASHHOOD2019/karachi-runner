// Author: Mashhood Ali
#include "Barrier.h"

Barrier::Barrier(float startX)
    : GameObject(startX, 620 - 64), Obstacle(startX, 620 - 64, 1, 96, 64)
{
}

void Barrier::draw(sf::RenderWindow& window)
{
    // Two legs
    sf::RectangleShape legLeft({8, 40});
    legLeft.setPosition({x + 6, y + 24});
    legLeft.setFillColor(sf::Color(90, 90, 95));
    window.draw(legLeft);

    sf::RectangleShape legRight({8, 40});
    legRight.setPosition({x + 82, y + 24});
    legRight.setFillColor(sf::Color(90, 90, 95));
    window.draw(legRight);

    // The striped top bar, orange and white, Karachi roadworks style
    sf::RectangleShape bar({96, 22});
    bar.setPosition({x, y + 2});
    bar.setFillColor(sf::Color(240, 120, 30));
    window.draw(bar);

    sf::RectangleShape stripeOne({16, 22});
    stripeOne.setPosition({x + 18, y + 2});
    stripeOne.setFillColor(sf::Color::White);
    window.draw(stripeOne);

    sf::RectangleShape stripeTwo({16, 22});
    stripeTwo.setPosition({x + 52, y + 2});
    stripeTwo.setFillColor(sf::Color::White);
    window.draw(stripeTwo);

    sf::RectangleShape stripeThree({16, 22});
    stripeThree.setPosition({x + 86, y + 2});
    stripeThree.setFillColor(sf::Color::White);
    window.draw(stripeThree);
}

std::string Barrier::getKind()
{
    return "Barrier";
}

bool Barrier::isLight()
{
    return true;
}

sf::FloatRect Barrier::getHitbox()
{
    // Only the top bar can hit the player. The open space under
    // the bar is exactly what a slide is for.
    return sf::FloatRect({x, y}, {width, height * 0.45f});
}
