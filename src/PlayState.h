// Author: Mashhood Ali
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "AssetManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "Map.h"
#include "Player.h"
#include "Obstacle.h"
#include "Collectible.h"
#include "Score.h"
#include <string>

// The real game (Phases 3, 4 and 5, maps added in Phase 6).
// PlayState OWNS its player, its map, its obstacles and its
// collectibles (Week 4-5 composition) and deletes them all in
// its destructor. The arrays are fixed size arrays of base class
// pointers (Week 3): one update() call runs a different function
// for every kind of obstacle and item.
class PlayState : public GameState
{
private:
    AssetManager* assets;       // association: owned by Game
    ScoreManager* scoreManager; // association: owned by Game
    SoundManager* sounds;       // association: owned by Game

    Player* player;
    Map* map;
    Obstacle* obstacles[20];
    int obstacleCount;
    Collectible* items[20];
    int itemCount;
    int lightStage; // 0 day, 1 sunset, 2 night, picked from score

    Score score;
    Score finalScore;
    bool bonusAdded;

    float worldSpeed;        // base speed, before the character factor
    float distanceTravelled; // in pixels
    float lastPointDistance; // distance at which the last point was given
    float nextSpawnDistance;
    float nextItemDistance;
    int spawnCounter;
    int itemCounter;

    bool slowMotion;
    float slowTimer;
    float invulnTimer;
    float shakeTime;
    bool pauseRequested;
    bool finished;

    float currentSpeed();
    void spawnObstacle();
    void spawnCollectible();
    void removeObstacle(int index);
    void removeItem(int index);
    void checkCollisions();
    sf::FloatRect playerHitbox();
    void finishRun();

    void drawHud(sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window, std::string text, float x, float y, int size, sf::Color color);

public:
    PlayState(AssetManager& assetManager, ScoreManager& manager,
              SoundManager& soundManager, int characterChoice, int mapChoice);
    ~PlayState();

    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    void startSlowMotion();
    bool isPauseRequested();
    void clearPauseRequest();
    bool isFinished();
    Score getFinalScore();
    std::string getPlayerName();
    std::string getMapName();
    int getLightStage();
};

#endif
