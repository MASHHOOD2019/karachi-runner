// Author: Mashhood Ali
#include "Player.h"

// Simple physics values, same for every character
const float GRAVITY = 2200.0f;
const float BASE_JUMP_SPEED = 820.0f;
const float ROAD_Y = 620.0f;

Player::Player(std::string playerName, int startHearts, float jump, float slide,
               float speedF, float bodyWidth, float bodyHeight, sf::Color color)
    : GameObject(0, 0),
      MovingObject(0, 0, 0),
      DrawableObject(0, 0)
{
    // Because GameObject is a virtual base class, Player (the most
    // derived class) is the one that calls its constructor above.
    name = playerName;
    hearts = startHearts;
    maxHearts = startHearts;
    jumpPower = jump;
    slideTime = slide;
    speedFactor = speedF;
    velocityY = 0;
    onGround = true;
    sliding = false;
    slideTimer = 0;
    currentFrame = 0;
    frameTimer = 0;
    groundY = ROAD_Y;
    shirtColor = color;
    bagColor = sf::Color::Transparent;

    width = bodyWidth;
    height = bodyHeight;
    x = 0;
    y = groundY - height;
}

Player::~Player()
{
}

void Player::setBagColor(sf::Color color)
{
    bagColor = color;
}

void Player::placeOnGround(float xPos)
{
    x = xPos;
    y = groundY - height;
    velocityY = 0;
    onGround = true;
}

void Player::jump()
{
    if (onGround && !sliding)
    {
        velocityY = -BASE_JUMP_SPEED * jumpPower;
        onGround = false;
    }
}

void Player::startSlide()
{
    if (onGround && !sliding)
    {
        sliding = true;
        slideTimer = slideTime;
    }
}

void Player::update(float dt)
{
    // Run animation frames move at a steady rhythm
    frameTimer = frameTimer + dt;
    if (frameTimer >= 0.12f)
    {
        frameTimer = 0;
        currentFrame = currentFrame + 1;
        if (currentFrame > 7)
        {
            currentFrame = 0;
        }
    }

    // Slide timer
    if (sliding)
    {
        slideTimer = slideTimer - dt;
        if (slideTimer <= 0)
        {
            sliding = false;
        }
    }

    // Gravity pulls the player down until the feet touch the road
    velocityY = velocityY + GRAVITY * dt;
    y = y + velocityY * dt;
    if (y + height >= groundY)
    {
        y = groundY - height;
        velocityY = 0;
        onGround = true;
    }
    else
    {
        onGround = false;
    }
}

void Player::draw(sf::RenderWindow& window)
{
    // Placeholder drawing with SFML shapes. The hand drawn pixel art
    // sprites will replace these shapes in the art phase. If a texture
    // has been set, the sprite is drawn instead of the shapes.
    if (hasTexture())
    {
        drawSprite(window, currentFrame);
        return;
    }

    sf::Color skinColor(198, 134, 66);

    if (sliding)
    {
        // Low and long body shape while sliding
        sf::RectangleShape body({width * 1.4f, height * 0.35f});
        body.setPosition({x, groundY - height * 0.35f});
        body.setFillColor(shirtColor);
        window.draw(body);

        sf::CircleShape head(width * 0.20f);
        head.setPosition({x + width * 1.15f, groundY - height * 0.55f});
        head.setFillColor(skinColor);
        window.draw(head);
        return;
    }

    // Legs: two small rectangles that swap offset every frame,
    // which reads as running when the frames move fast
    float legSwing = 0;
    if (onGround)
    {
        if (currentFrame % 2 == 0)
        {
            legSwing = 4;
        }
        else
        {
            legSwing = -4;
        }
    }
    sf::RectangleShape legOne({width * 0.16f, height * 0.28f});
    legOne.setPosition({x + width * 0.22f + legSwing, y + height * 0.72f});
    legOne.setFillColor(sf::Color(30, 30, 60));
    window.draw(legOne);

    sf::RectangleShape legTwo({width * 0.16f, height * 0.28f});
    legTwo.setPosition({x + width * 0.58f - legSwing, y + height * 0.72f});
    legTwo.setFillColor(sf::Color(30, 30, 60));
    window.draw(legTwo);

    // Bag behind the body, if this character carries one
    if (bagColor != sf::Color::Transparent)
    {
        sf::RectangleShape bag({width * 0.30f, height * 0.42f});
        bag.setPosition({x - width * 0.12f, y + height * 0.30f});
        bag.setFillColor(bagColor);
        window.draw(bag);
    }

    // Torso
    sf::RectangleShape torso({width * 0.70f, height * 0.48f});
    torso.setPosition({x + width * 0.15f, y + height * 0.26f});
    torso.setFillColor(shirtColor);
    window.draw(torso);

    // Head
    sf::CircleShape head(width * 0.24f);
    head.setPosition({x + width * 0.26f, y});
    head.setFillColor(skinColor);
    window.draw(head);
}

void Player::loseHeart()
{
    if (hearts > 0)
    {
        hearts = hearts - 1;
    }
}

void Player::addHeart()
{
    if (hearts < maxHearts)
    {
        hearts = hearts + 1;
    }
}

bool Player::isDead()
{
    return hearts <= 0;
}

bool Player::isSliding()
{
    return sliding;
}

bool Player::canSmashLightObstacle()
{
    // Normal characters cannot smash anything. Aryan overrides this.
    return false;
}

void Player::setHearts(int h)
{
    // The setter checks the value first (Week 2)
    if (h < 0)
    {
        h = 0;
    }
    if (h > maxHearts)
    {
        h = maxHearts;
    }
    hearts = h;
}

float Player::getSpeedFactor()
{
    return speedFactor;
}

float Player::getSlideTime()
{
    return slideTime;
}
