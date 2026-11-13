// Author: Mashhood Ali
#ifndef POTHOLE_H
#define POTHOLE_H

#include "Obstacle.h"

// A Karachi pothole: flat on the road, small, easy to miss at
// speed. Cleared by even a small jump.
class Pothole : public Obstacle
{
public:
    Pothole(float startX);
    void draw(sf::RenderWindow& window);
    std::string getKind();
};

#endif
