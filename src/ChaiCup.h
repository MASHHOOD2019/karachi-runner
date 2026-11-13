// Author: Mashhood Ali
#ifndef CHAICUP_H
#define CHAICUP_H

#include "Collectible.h"

// A cup of chai: time slows down. Picking it up asks PlayState
// (through the flag in the base class) to halve the world speed
// for 5 seconds. Karachi runs on chai; this game slows on it.
class ChaiCup : public Collectible
{
public:
    ChaiCup(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void apply(Player& player, Score& score);
};

#endif
