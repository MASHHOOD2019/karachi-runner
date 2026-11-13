// Author: Mashhood Ali
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "AssetManager.h"
#include "SoundManager.h"
#include "Player.h"
#include <string>

// The title screen (Phase 1 shell, finished in Phase 5).
// It shows the game title, the 3 runners running in place,
// "Press Enter to play", and the credits lines of Section 6.
// Keys 1, 2, 3 choose the runner, Left and Right arrows cycle
// the map (the same simple single-key style), and C opens the
// credits screen.
class MenuState : public GameState
{
private:
    AssetManager* assets;   // association: the assets belong to Game
    SoundManager* sounds;   // association: the sounds belong to Game
    Player* runners[3];     // the 3 characters, owned by this state
    bool startPressed;
    bool creditsPressed;
    int selectedCharacter;  // 1 Mashhood, 2 Shayan, 3 Aryan
    int selectedMap;        // 1 Clifton, 2 Shahrah, 3 University, 4 Saddar
    std::string mapNames[4];

    void drawBackground(sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color);

public:
    MenuState(AssetManager& assetManager, SoundManager& soundManager);
    ~MenuState();

    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isStartPressed();
    void clearStart();
    int getSelectedCharacter();
    int getSelectedMap();
    bool isCreditsPressed();
    void clearCredits();
};

#endif
