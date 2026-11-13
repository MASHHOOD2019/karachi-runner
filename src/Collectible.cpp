// Author: Mashhood Ali
#include "Collectible.h"

Collectible::Collectible(float startX, float startY, float w, float h)
    : GameObject(startX, startY),
      MovingObject(startX, startY, 0),
      DrawableObject(startX, startY)
{
    slowMotionFlag = false;
    width = w;
    height = h;
}

Collectible::~Collectible()
{
}

void Collectible::update(float dt)
{
    moveLeft(dt);
}

void Collectible::requestSlowMotion()
{
    slowMotionFlag = true;
}

bool Collectible::isSlowMotionRequested()
{
    return slowMotionFlag;
}

void Collectible::clearSlowMotionRequest()
{
    slowMotionFlag = false;
}

sf::FloatRect Collectible::getHitbox()
{
    // A little forgiving, like the obstacle hitboxes
    return sf::FloatRect({x + width * 0.1f, y + height * 0.1f},
                         {width * 0.8f, height * 0.8f});
}
