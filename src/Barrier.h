// Author: Mashhood Ali
#ifndef BARRIER_H
#define BARRIER_H

#include "Obstacle.h"

// A road repair barrier: a striped top bar on two legs.
// Run into the bar and it costs a heart. Slide and you pass
// under the bar. Aryan smashes straight through it: it is one
// of the two light obstacles (dynamic_cast target, Week 12-13).
class Barrier : public Obstacle
{
public:
    Barrier(float startX);
    void draw(sf::RenderWindow& window);
    std::string getKind();
    bool isLight();
    sf::FloatRect getHitbox();
};

#endif
