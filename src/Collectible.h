// Author: Mashhood Ali
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "MovingObject.h"
#include "DrawableObject.h"
#include "Player.h"
#include "Score.h"

// Anything the player picks up (Week 10 pure virtual function,
// Week 4-5 inheritance). Each child decides its own effect in
// apply(), and PlayState calls apply() through a Collectible
// pointer without knowing which item it is. That is polymorphism.
class Collectible : public MovingObject, public DrawableObject
{
private:
    bool slowMotionFlag;

protected:
    void requestSlowMotion();

public:
    Collectible(float startX, float startY, float w, float h);
    virtual ~Collectible();

    void update(float dt);
    // draw() stays pure virtual from GameObject.
    virtual void apply(Player& player, Score& score) = 0;

    sf::FloatRect getHitbox();
    bool isSlowMotionRequested();
    void clearSlowMotionRequest();
};

#endif
