// Author: Mashhood Ali
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

// The root of every object in the game world (Week 1 modeling,
// Week 10 abstract class). It has pure virtual functions, so no
// object of GameObject can be made directly.
class GameObject
{
protected:
    float x;
    float y;
    float width;
    float height;

public:
    GameObject(float startX, float startY);
    virtual ~GameObject();

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    inline float getX() { return x; }
    inline float getY() { return y; }
    void setPosition(float newX, float newY);
    void setSize(float newWidth, float newHeight);
    sf::FloatRect getBounds();
};

#endif
