// Author: Mashhood Ali
#include "Obstacle.h"

Obstacle::Obstacle(float startX, float startY, int dmg, float w, float h)
    : GameObject(startX, startY),
      MovingObject(startX, startY, 0),
      DrawableObject(startX, startY)
{
    damage = dmg;
    passed = false;
    width = w;
    height = h;
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float dt)
{
    // The world scrolls past the player, so obstacles move left.
    // PlayState sets the speed every frame through setSpeedX().
    moveLeft(dt);
}

int Obstacle::hitDamage()
{
    return damage;
}

bool Obstacle::isLight()
{
    // Heavy by default. Barrier and Thela override this: they are
    // the two light wooden obstacles Aryan can smash.
    return false;
}

sf::FloatRect Obstacle::getHitbox()
{
    // About 75 percent of the full box, centred. Roof signs,
    // mirrors and decorations do not kill the player.
    return sf::FloatRect({x + width * 0.125f, y + height * 0.125f},
                         {width * 0.75f, height * 0.75f});
}

bool Obstacle::isPassed()
{
    return passed;
}

void Obstacle::setPassed(bool p)
{
    passed = p;
}
