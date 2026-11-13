// Author: Mashhood Ali
#include "GameObject.h"

GameObject::GameObject(float startX, float startY)
{
    x = startX;
    y = startY;
    width = 0;
    height = 0;
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}

void GameObject::setSize(float newWidth, float newHeight)
{
    width = newWidth;
    height = newHeight;
}

sf::FloatRect GameObject::getBounds()
{
    return sf::FloatRect({x, y}, {width, height});
}
