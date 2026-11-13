// Author: Mashhood Ali
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "AssetManager.h"
#include <string>

// The pause screen (Week 10 overriding). Game draws the frozen
// PlayState first, then this state draws a dim layer and the
// PAUSED text over it. PlayState is simply not updated while
// this state is active, so the run freezes exactly where it was.
class PauseState : public GameState
{
private:
    AssetManager* assets; // association: owned by Game
    bool resumeRequested;

    void drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color);

public:
    PauseState(AssetManager& assetManager);

    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isResumeRequested();
};

#endif
