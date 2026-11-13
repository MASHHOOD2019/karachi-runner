// Author: Mashhood Ali
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "CreditsState.h"
#include "MashhoodPlayer.h"
#include "FileLoadException.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({1280, 720}), "Karachi Runner"),
      player(nullptr),
      currentState(nullptr),
      savedState(nullptr)
{
    window.setFramerateLimit(60);

    // The font is loaded once here. If the file is not there yet,
    // the game still opens and the screens simply draw without text.
    try
    {
        assets.loadFont("assets/fonts/main.ttf");
    }
    catch (FileLoadException& e)
    {
        std::cout << "Font not loaded: " << e.getMessage() << std::endl;
        std::cout << "The game will run, but text needs assets/fonts/main.ttf" << std::endl;
    }

    // Read: the Top 5 leaderboard is loaded from highscore.txt
    // at the start (the file is created if it does not exist).
    scoreManager.loadScores();

    // Sounds load quietly: any missing file is skipped inside
    // SoundManager, so this line can never crash the game.
    sounds.loadAll();

    player = new MashhoodPlayer();
    currentState = new MenuState(assets, sounds);
}

Game::~Game()
{
    delete currentState;
    delete savedState;
    delete player;
}

void Game::handleStateChanges()
{
    // One GameState pointer, many behaviours: the casts below ask
    // what the current screen really is (Week 12-13 dynamic_cast)
    MenuState* menu = dynamic_cast<MenuState*>(currentState);
    if (menu != nullptr)
    {
        if (menu->isCreditsPressed())
        {
            delete currentState;
            currentState = new CreditsState(assets);
        }
        else if (menu->isStartPressed())
        {
            int choice = menu->getSelectedCharacter();
            int mapChoice = menu->getSelectedMap();
            delete currentState;
            currentState = new PlayState(assets, scoreManager, sounds, choice, mapChoice);
        }
        return;
    }

    CreditsState* credits = dynamic_cast<CreditsState*>(currentState);
    if (credits != nullptr)
    {
        if (credits->isBackRequested())
        {
            delete currentState;
            currentState = new MenuState(assets, sounds);
        }
        return;
    }

    PlayState* play = dynamic_cast<PlayState*>(currentState);
    if (play != nullptr)
    {
        if (play->isPauseRequested())
        {
            play->clearPauseRequest();
            savedState = currentState; // the run freezes under the pause
            currentState = new PauseState(assets);
        }
        else if (play->isFinished())
        {
            GameOverState* over = new GameOverState(assets, scoreManager, sounds,
                                                    play->getFinalScore(),
                                                    play->getPlayerName());
            delete play;
            currentState = over;
        }
        return;
    }

    PauseState* pause = dynamic_cast<PauseState*>(currentState);
    if (pause != nullptr)
    {
        if (pause->isResumeRequested())
        {
            delete pause;
            currentState = savedState;
            savedState = nullptr;
        }
        return;
    }

    GameOverState* over = dynamic_cast<GameOverState*>(currentState);
    if (over != nullptr && over->isMenuRequested())
    {
        delete over;
        currentState = new MenuState(assets, sounds);
    }
}

SoundManager& Game::getSounds()
{
    return sounds;
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f)
        {
            dt = 0.05f; // clamped, so one slow frame cannot break physics
        }

        // SFML 3 event loop: events arrive inside a std::optional
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else
            {
                currentState->handleInput(*event);
            }
        }

        currentState->update(dt);
        handleStateChanges();

        window.clear();
        // While paused, the frozen run is drawn first and the
        // pause screen is drawn over it
        if (savedState != nullptr && dynamic_cast<PauseState*>(currentState) != nullptr)
        {
            savedState->draw(window);
        }
        currentState->draw(window);
        window.display();
    }
}

AssetManager& Game::getAssets()
{
    return assets;
}

ScoreManager& Game::getScoreManager()
{
    return scoreManager;
}

Player* Game::getPlayer()
{
    return player;
}
