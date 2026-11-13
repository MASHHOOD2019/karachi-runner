// Author: Mashhood Ali
#ifndef RICKSHAW_H
#define RICKSHAW_H

#include "Obstacle.h"

// The classic green CNG rickshaw. Cleared by a jump, deadly for
// everyone, Aryan included. Rickshaws cannot be smashed.
class Rickshaw : public Obstacle
{
public:
    Rickshaw(float startX);
    void draw(sf::RenderWindow& window);
    std::string getKind();
};

#endif
