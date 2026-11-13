// Author: Mashhood Ali
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "GameState.h"
#include "AssetManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "Score.h"
#include <string>

// The game over screen (Phase 5). Shows the final score, printed
// with the friend operator<< of Score (Week 6 in real use), saves
// the score through ScoreManager if it qualifies (Week 15), and
// shows the Top 5 leaderboard read back from highscore.txt.
class GameOverState : public GameState
{
private:
    AssetManager* assets;       // association: owned by Game
    ScoreManager* scoreManager; // association: owned by Game
    SoundManager* sounds;       // association: owned by Game
    Score finalScore;
    std::string playerName;
    bool newHighScore;
    bool menuRequested;

    void drawBackground(sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color);

public:
    GameOverState(AssetManager& assetManager, ScoreManager& manager,
                  SoundManager& soundManager, Score score, std::string name);

    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isMenuRequested();
    bool isNewHighScore();
};

#endif
