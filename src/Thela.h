// Author: Mashhood Ali
#ifndef THELA_H
#define THELA_H

#include "Obstacle.h"

// The wooden handcart of Saddar. Cleared by a jump, or smashed
// by Aryan: it is the second light obstacle
// (dynamic_cast target, Week 12-13).
class Thela : public Obstacle
{
public:
    Thela(float startX);
    void draw(sf::RenderWindow& window);
    std::string getKind();
    bool isLight();
};

#endif
