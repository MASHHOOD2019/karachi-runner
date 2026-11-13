// Author: Mashhood Ali
#include "GameOverState.h"
#include <sstream>

GameOverState::GameOverState(AssetManager& assetManager, ScoreManager& manager,
                             SoundManager& soundManager, Score score, std::string name)
{
    assets = &assetManager;
    scoreManager = &manager;
    sounds = &soundManager;
    finalScore = score;
    playerName = name;
    menuRequested = false;

    // The run just ended: play the game over sound once, here
    sounds->playGameOver();

    // Save once, here, if the run earned a place on the board
    newHighScore = scoreManager->qualifies(finalScore.getPoints());
    if (newHighScore)
    {
        scoreManager->addScore(playerName, finalScore);
    }
}

void GameOverState::handleInput(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        const sf::Event::KeyPressed* key = event.getIf<sf::Event::KeyPressed>();
        if (key != nullptr &&
            (key->code == sf::Keyboard::Key::Enter || key->code == sf::Keyboard::Key::Escape))
        {
            menuRequested = true;
        }
    }
}

void GameOverState::update(float dt)
{
    (void)dt; // a still screen; only input matters here
}

void GameOverState::drawBackground(sf::RenderWindow& window)
{
    // The same Karachi sunset, darker: the run ended at nightfall
    sf::RectangleShape skyTop({1280, 300});
    skyTop.setPosition({0, 0});
    skyTop.setFillColor(sf::Color(24, 20, 44));
    window.draw(skyTop);

    sf::RectangleShape skyMid({1280, 180});
    skyMid.setPosition({0, 300});
    skyMid.setFillColor(sf::Color(80, 28, 64));
    window.draw(skyMid);

    sf::RectangleShape skyLow({1280, 140});
    skyLow.setPosition({0, 480});
    skyLow.setFillColor(sf::Color(170, 84, 44));
    window.draw(skyLow);

    sf::RectangleShape road({1280, 100});
    road.setPosition({0, 620});
    road.setFillColor(sf::Color(32, 29, 40));
    window.draw(road);
}

void GameOverState::drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color)
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

void GameOverState::draw(sf::RenderWindow& window)
{
    drawBackground(window);

    drawText(window, "GAME OVER", 640, 95, 56, sf::Color(250, 200, 110));
    drawText(window, playerName + " ran out of hearts", 640, 150, 22, sf::Color::White);

    // The final score line, printed with the friend operator<<
    std::stringstream stream;
    stream << finalScore;
    drawText(window, stream.str(), 640, 205, 28, sf::Color::White);

    if (newHighScore)
    {
        drawText(window, "New high score!", 640, 255, 26, sf::Color(120, 230, 160));
    }

    // The Top 5 leaderboard, read back through ScoreManager
    drawText(window, "TOP 5 - KARACHI RUNNER", 640, 320, 24, sf::Color(250, 200, 110));
    for (int i = 0; i < scoreManager->getSavedCount(); i++)
    {
        std::stringstream row;
        row << (i + 1) << ".  " << scoreManager->getTopName(i)
            << "   " << scoreManager->getTopScore(i).getPoints() << " points   "
            << scoreManager->getTopScore(i).getDistance() << " m";
        drawText(window, row.str(), 640, 360 + i * 34, 20, sf::Color::White);
    }
    if (scoreManager->getSavedCount() == 0)
    {
        drawText(window, "No saved scores yet", 640, 360, 20, sf::Color(200, 200, 200));
    }

    drawText(window, "Press Enter to return to the menu", 640, 580, 22, sf::Color(220, 220, 220));
}

bool GameOverState::isMenuRequested()
{
    return menuRequested;
}

bool GameOverState::isNewHighScore()
{
    return newHighScore;
}
