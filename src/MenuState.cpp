// Author: Mashhood Ali
#include "MenuState.h"
#include "MashhoodPlayer.h"
#include "ShayanPlayer.h"
#include "AryanPlayer.h"

MenuState::MenuState(AssetManager& assetManager, SoundManager& soundManager)
{
    assets = &assetManager;
    sounds = &soundManager;
    startPressed = false;
    creditsPressed = false;
    selectedCharacter = 1;
    selectedMap = 1;
    mapNames[0] = "Clifton";
    mapNames[1] = "Shahrah-e-Faisal";
    mapNames[2] = "University Road";
    mapNames[3] = "Saddar";

    runners[0] = new MashhoodPlayer();
    runners[1] = new ShayanPlayer();
    runners[2] = new AryanPlayer();
    runners[0]->placeOnGround(300);
    runners[1]->placeOnGround(590);
    runners[2]->placeOnGround(880);
}

MenuState::~MenuState()
{
    for (int i = 0; i < 3; i++)
    {
        delete runners[i];
    }
}

void MenuState::handleInput(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        const sf::Event::KeyPressed* key = event.getIf<sf::Event::KeyPressed>();
        if (key == nullptr)
        {
            return;
        }
        if (key->code == sf::Keyboard::Key::Enter)
        {
            startPressed = true;
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::Num1)
        {
            selectedCharacter = 1;
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::Num2)
        {
            selectedCharacter = 2;
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::Num3)
        {
            selectedCharacter = 3;
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::Right)
        {
            // Cycle the maps forward: 1, 2, 3, 4, then back to 1
            selectedMap = selectedMap % 4 + 1;
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::Left)
        {
            selectedMap = selectedMap - 1;
            if (selectedMap < 1)
            {
                selectedMap = 4;
            }
            sounds->playClick();
        }
        else if (key->code == sf::Keyboard::Key::C)
        {
            creditsPressed = true;
            sounds->playClick();
        }
    }
}

void MenuState::update(float dt)
{
    for (int i = 0; i < 3; i++)
    {
        runners[i]->update(dt);
    }
}

void MenuState::drawBackground(sf::RenderWindow& window)
{
    // One Karachi sunset, drawn in horizontal bands of colour
    sf::RectangleShape skyTop({1280, 300});
    skyTop.setPosition({0, 0});
    skyTop.setFillColor(sf::Color(38, 32, 64));
    window.draw(skyTop);

    sf::RectangleShape skyMid({1280, 180});
    skyMid.setPosition({0, 300});
    skyMid.setFillColor(sf::Color(120, 40, 90));
    window.draw(skyMid);

    sf::RectangleShape skyLow({1280, 140});
    skyLow.setPosition({0, 480});
    skyLow.setFillColor(sf::Color(230, 120, 60));
    window.draw(skyLow);

    sf::RectangleShape sunStrip({1280, 12});
    sunStrip.setPosition({0, 608});
    sunStrip.setFillColor(sf::Color(250, 200, 110));
    window.draw(sunStrip);

    // The road
    sf::RectangleShape road({1280, 100});
    road.setPosition({0, 620});
    road.setFillColor(sf::Color(40, 36, 48));
    window.draw(road);
}

void MenuState::drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color)
{
    if (!assets->hasFont())
    {
        return;
    }
    sf::Text label(assets->getFont(), text, size);
    label.setFillColor(color);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2});
    label.setPosition({cx, y});
    window.draw(label);
}

void MenuState::draw(sf::RenderWindow& window)
{
    drawBackground(window);

    drawText(window, "KARACHI RUNNER", 640, 90, 64, sf::Color(250, 200, 110));
    drawText(window, "An endless run through Karachi", 640, 150, 24, sf::Color::White);

    // The 3 runners, running in place over their names
    for (int i = 0; i < 3; i++)
    {
        runners[i]->draw(window);
    }
    // The chosen runner's name is gold, the others stay white
    sf::Color gold(250, 200, 110);
    drawText(window, "Mashhood Ali", 321, 655, 20, selectedCharacter == 1 ? gold : sf::Color::White);
    drawText(window, "Shayan", 608, 655, 20, selectedCharacter == 2 ? gold : sf::Color::White);
    drawText(window, "Aryan", 908, 655, 20, selectedCharacter == 3 ? gold : sf::Color::White);

    drawText(window, "Press 1, 2 or 3 to choose your runner", 640, 205, 20, sf::Color(220, 220, 220));
    drawText(window, "Press Enter to play", 640, 240, 30, sf::Color::White);
    drawText(window, "Space = Jump    Down = Slide    P = Pause", 640, 285, 20, sf::Color(200, 200, 200));

    // Map choice: the name of the selected map in gold
    drawText(window, "Map: " + mapNames[selectedMap - 1], 640, 322, 24, sf::Color(250, 200, 110));
    drawText(window, "Left / Right arrows choose the map     C = Credits", 640, 352, 18, sf::Color(200, 200, 200));

    // Credits lines (Blueprint Section 6.1)
    drawText(window, "Karachi Runner - OOP Course Project CS 1420", 640, 420, 20, sf::Color(220, 220, 220));
    drawText(window, "Instructor: Sir Faisal Feroze", 640, 450, 20, sf::Color(220, 220, 220));
    drawText(window, "Made by: Mashhood Ali (SP26-BSSE-0021)", 640, 480, 20, sf::Color(220, 220, 220));
    drawText(window, "Muhammad Ali Jinnah University, Karachi", 640, 510, 20, sf::Color(220, 220, 220));
}

bool MenuState::isStartPressed()
{
    return startPressed;
}

void MenuState::clearStart()
{
    startPressed = false;
}

int MenuState::getSelectedCharacter()
{
    return selectedCharacter;
}

int MenuState::getSelectedMap()
{
    return selectedMap;
}

bool MenuState::isCreditsPressed()
{
    return creditsPressed;
}

void MenuState::clearCredits()
{
    creditsPressed = false;
}
