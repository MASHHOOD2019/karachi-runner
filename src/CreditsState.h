// Author: Mashhood Ali
#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "GameState.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <string>

// The credits screen (blueprint Section 6.1, dedication item 1).
// Reached from the menu with the C key; Esc or Enter goes back.
// It carries the course lines, sir's name, and the professional
// line of blueprint Section 6.4 in English - and in Urdu too,
// when the Urdu font file is present.
class CreditsState : public GameState
{
private:
    AssetManager* assets; // association: owned by Game
    sf::Font urduFont;
    bool urduFontLoaded;
    bool backRequested;

    void drawBackground(sf::RenderWindow& window);
    void drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color);
    void drawUrduLine(sf::RenderWindow& window, float cx, float y, int size, sf::Color color);

public:
    CreditsState(AssetManager& assetManager);

    void handleInput(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isBackRequested();
};

#endif
