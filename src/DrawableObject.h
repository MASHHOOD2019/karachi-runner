// Author: Mashhood Ali
#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

// Adds sprite drawing to a GameObject (Week 11 virtual inheritance,
// Week 5 association). The texture itself belongs to AssetManager,
// this class only keeps a pointer to it.
class DrawableObject : virtual public GameObject
{
private:
    sf::Texture* texture;
    int frameWidth;
    int frameHeight;

public:
    DrawableObject(float startX, float startY);
    virtual ~DrawableObject();

    void setTexture(sf::Texture& tex, int fw, int fh);
    bool hasTexture();
    void drawSprite(sf::RenderWindow& window, int frame);
};

#endif
