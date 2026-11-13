// Author: Mashhood Ali
#ifndef BIRYANIBOX_H
#define BIRYANIBOX_H

#include "Collectible.h"

// A biryani box: +50 points, added through the overloaded
// add(points, reason) function (Week 9 function overloading).
class BiryaniBox : public Collectible
{
public:
    BiryaniBox(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void apply(Player& player, Score& score);
};

#endif
