// Author: Mashhood Ali
#include "ChaiCup.h"

ChaiCup::ChaiCup(float startX, float startY)
    : GameObject(startX, startY), Collectible(startX, startY, 30, 32)
{
}

void ChaiCup::draw(sf::RenderWindow& window)
{
    // A small dhaba chai cup: white cup, brown chai, a saucer
    sf::RectangleShape cup({24, 18});
    cup.setPosition({x + 3, y + 8});
    cup.setFillColor(sf::Color(245, 245, 240));
    window.draw(cup);

    sf::RectangleShape chai({24, 6});
    chai.setPosition({x + 3, y + 8});
    chai.setFillColor(sf::Color(165, 100, 45));
    window.draw(chai);

    sf::RectangleShape saucer({30, 4});
    saucer.setPosition({x, y + 27});
    saucer.setFillColor(sf::Color(200, 200, 200));
    window.draw(saucer);
}

void ChaiCup::apply(Player& player, Score& score)
{
    (void)player;
    (void)score;
    // The effect lives in PlayState (it owns the world speed),
    // so this item only raises the request flag in the base class.
    requestSlowMotion();
}
