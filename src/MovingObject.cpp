// Author: Mashhood Ali
#include "MovingObject.h"

MovingObject::MovingObject(float startX, float startY, float speed)
    : GameObject(startX, startY)
{
    speedX = speed;
}

MovingObject::~MovingObject()
{
}

void MovingObject::setSpeedX(float speed)
{
    speedX = speed;
}

float MovingObject::getSpeedX()
{
    return speedX;
}

void MovingObject::moveLeft(float dt)
{
    // The world scrolls, so moving objects travel toward the player
    x = x - speedX * dt;
}
