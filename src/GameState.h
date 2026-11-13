// Author: Mashhood Ali
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

// The common design of every screen in the game (Week 10 abstract
// class). Menu, playing, pause and game over screens all inherit
// this. The game holds ONE GameState pointer and calls these three
// functions without knowing which screen it really is. That is
// runtime polymorphism.
class GameState
{
public:
    GameState() {}
    virtual ~GameState() {}

    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif
