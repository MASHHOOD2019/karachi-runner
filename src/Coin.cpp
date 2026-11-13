// Author: Mashhood Ali
#include "Coin.h"
#include <iostream>

// The static member MUST be defined once, outside the class,
// in this file (Week 3). Without this line the linker complains.
int Coin::totalCoinsCollected = 0;

Coin::Coin(float startX, float startY)
    : GameObject(startX, startY), Collectible(startX, startY, 26, 26)
{
}

void Coin::draw(sf::RenderWindow& window)
{
    sf::CircleShape coin(13);
    coin.setPosition({x, y});
    coin.setFillColor(sf::Color(250, 200, 40));
    window.draw(coin);

    sf::CircleShape inner(8);
    inner.setPosition({x + 5, y + 5});
    inner.setFillColor(sf::Color(255, 225, 110));
    window.draw(inner);
}

void Coin::apply(Player& player, Score& score)
{
    (void)player; // a coin does not change the player, only the score
    score.addCoin();
    score.add(10);
    totalCoinsCollected = totalCoinsCollected + 1;
}

int Coin::getTotalCoins()
{
    return totalCoinsCollected;
}

void Coin::showTotalCoins()
{
    std::cout << "Total coins collected this session: "
              << totalCoinsCollected << std::endl;
}
