// Author: Mashhood Ali
#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "GameObject.h"

// Adds movement to a GameObject (Week 11 virtual inheritance).
// The "virtual" here means MovingObject and DrawableObject share
// ONE GameObject when a class inherits both of them. That is how
// the diamond problem is solved in this project.
class MovingObject : virtual public GameObject
{
private:
    float speedX;

public:
    MovingObject(float startX, float startY, float speed);
    virtual ~MovingObject();

    void setSpeedX(float speed);
    float getSpeedX();
    void moveLeft(float dt);
};

#endif
