// Author: Mashhood Ali
#ifndef PLAYER_H
#define PLAYER_H

#include "MovingObject.h"
#include "DrawableObject.h"
#include <string>

// The base class of the 3 playable characters (Week 2 encapsulation,
// Week 10 abstract class, Week 11 multiple inheritance).
// Player inherits MovingObject AND DrawableObject, and both of them
// inherit GameObject virtually, so a Player has only ONE position.
class Player : public MovingObject, public DrawableObject
{
private:
    std::string name;
    int hearts;
    int maxHearts;
    float jumpPower;    // jump factor: 1.00 is the standard jump
    float slideTime;    // how long a slide lasts, in seconds
    float speedFactor;  // speed factor: 1.00 is the standard speed
    float velocityY;
    bool onGround;
    bool sliding;
    float slideTimer;
    int currentFrame;
    float frameTimer;
    float groundY;      // the y level of the road surface
    sf::Color shirtColor;
    sf::Color bagColor;

public:
    Player(std::string playerName, int startHearts, float jump, float slide,
           float speedF, float bodyWidth, float bodyHeight, sf::Color color);
    virtual ~Player();

    void jump();
    void startSlide();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void placeOnGround(float xPos);

    void loseHeart();
    void addHeart();
    bool isDead();
    bool isSliding();
    virtual bool canSmashLightObstacle();
    virtual std::string getTitle() = 0;

    inline int getHearts() { return hearts; }
    void setHearts(int h);
    inline std::string getName() { return name; }
    float getSpeedFactor();
    float getSlideTime();

protected:
    void setBagColor(sf::Color color);
};

#endif
