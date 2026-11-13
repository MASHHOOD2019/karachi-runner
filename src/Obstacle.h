// Author: Mashhood Ali
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "MovingObject.h"
#include "DrawableObject.h"
#include <string>

// The general traffic obstacle (Week 10 abstract class,
// Week 4-5 multilevel inheritance: GameObject to Obstacle to child).
// Obstacle inherits MovingObject AND DrawableObject, and both of
// them inherit GameObject virtually, so there is only one position.
class Obstacle : public MovingObject, public DrawableObject
{
private:
    int damage;
    bool passed;

public:
    Obstacle(float startX, float startY, int dmg, float w, float h);
    virtual ~Obstacle();

    void update(float dt);
    // draw() stays pure virtual from GameObject: every child
    // obstacle draws its own shape.
    virtual int hitDamage();
    virtual bool isLight();
    virtual std::string getKind() = 0;

    virtual sf::FloatRect getHitbox();
    inline int getDamage() { return damage; }
    bool isPassed();
    void setPassed(bool p);
};

#endif
