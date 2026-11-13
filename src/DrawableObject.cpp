// Author: Mashhood Ali
#include "DrawableObject.h"

DrawableObject::DrawableObject(float startX, float startY)
    : GameObject(startX, startY)
{
    texture = nullptr;
    frameWidth = 0;
    frameHeight = 0;
}

DrawableObject::~DrawableObject()
{
    // The texture is NOT deleted here. It belongs to AssetManager.
}

void DrawableObject::setTexture(sf::Texture& tex, int fw, int fh)
{
    texture = &tex;
    frameWidth = fw;
    frameHeight = fh;
}

bool DrawableObject::hasTexture()
{
    return texture != nullptr;
}

void DrawableObject::drawSprite(sf::RenderWindow& window, int frame)
{
    if (texture == nullptr)
    {
        return;
    }
    sf::Sprite sprite(*texture);
    sprite.setTextureRect(sf::IntRect({frame * frameWidth, 0}, {frameWidth, frameHeight}));
    sprite.setPosition({x, y});
    window.draw(sprite);
}
