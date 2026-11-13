// Author: Mashhood Ali
#ifndef BUS_H
#define BUS_H

#include "Obstacle.h"

// The tall one. A full, well timed jump is the only way over a
// bus, and it stays deadly for Aryan too: far too heavy to smash.
class Bus : public Obstacle
{
public:
    Bus(float startX);
    void draw(sf::RenderWindow& window);
    std::string getKind();
};

#endif
