// Author: Mashhood Ali
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameState.h"
#include "Player.h"

// The owner of the whole game (Week 4-5 composition).
// Game HAS the window, the managers, the selected player and the
// current screen state, and its destructor deletes what it owns.
// It also moves between states: Menu to Play to Pause and back,
// Play to Game Over, Game Over to Menu.
class Game
{
private:
    sf::RenderWindow window;
    AssetManager assets;
    ScoreManager scoreManager;
    SoundManager sounds;
    Player* player;
    GameState* currentState;
    GameState* savedState; // the frozen PlayState under the pause screen

    void handleStateChanges();

public:
    Game();
    ~Game();

    void run();
    AssetManager& getAssets();
    ScoreManager& getScoreManager();
    SoundManager& getSounds();
    Player* getPlayer();
};

#endif
