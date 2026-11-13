// Author: Mashhood Ali
#ifndef COIN_H
#define COIN_H

#include "Collectible.h"

// A coin: +10 points, +1 on the coin count (Week 9: it calls the
// overloaded Score add functions). The static counter below is
// Week 3: ONE counter shared by the whole class, counting every
// coin collected in the whole session, across all runs.
class Coin : public Collectible
{
private:
    static int totalCoinsCollected;

public:
    Coin(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void apply(Player& player, Score& score);

    static int getTotalCoins();
    static void showTotalCoins();
};

#endif
