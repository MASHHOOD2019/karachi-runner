// Author: Mashhood Ali
#include "PlayState.h"
#include "MashhoodPlayer.h"
#include "ShayanPlayer.h"
#include "AryanPlayer.h"
#include "CliftonMap.h"
#include "ShahrahMap.h"
#include "UniversityRoadMap.h"
#include "SaddarMap.h"
#include "Rickshaw.h"
#include "Pothole.h"
#include "Barrier.h"
#include "Bus.h"
#include "Thela.h"
#include "Coin.h"
#include "BiryaniBox.h"
#include "ChaiCup.h"
#include <cmath>

const float GROUND_Y = 620.0f;

PlayState::PlayState(AssetManager& assetManager, ScoreManager& manager,
                     SoundManager& soundManager, int characterChoice, int mapChoice)
{
    assets = &assetManager;
    scoreManager = &manager;
    sounds = &soundManager;

    // The character chosen on the menu (keys 1, 2, 3)
    if (characterChoice == 2)
    {
        player = new ShayanPlayer();
    }
    else if (characterChoice == 3)
    {
        player = new AryanPlayer();
    }
    else
    {
        player = new MashhoodPlayer();
    }
    player->placeOnGround(160);

    // The map chosen on the menu (arrows, 1 to 4). PlayState
    // owns it and deletes it in the destructor (composition).
    if (mapChoice == 2)
    {
        map = new ShahrahMap();
    }
    else if (mapChoice == 3)
    {
        map = new UniversityRoadMap();
    }
    else if (mapChoice == 4)
    {
        map = new SaddarMap();
    }
    else
    {
        map = new CliftonMap();
    }
    map->useAssets(assetManager);
    lightStage = 0;

    obstacleCount = 0;
    itemCount = 0;
    for (int i = 0; i < 20; i++)
    {
        obstacles[i] = nullptr;
        items[i] = nullptr;
    }

    bonusAdded = false;
    worldSpeed = map->getStartSpeed();
    distanceTravelled = 0;
    lastPointDistance = 0;
    nextSpawnDistance = 750; // the first obstacle comes after a calm start
    nextItemDistance = 420;
    spawnCounter = 0;
    itemCounter = 0;

    slowMotion = false;
    slowTimer = 0;
    invulnTimer = 0;
    shakeTime = 0;
    pauseRequested = false;
    finished = false;
}

PlayState::~PlayState()
{
    // Composition: what PlayState created, PlayState deletes
    delete player;
    delete map;
    for (int i = 0; i < obstacleCount; i++)
    {
        delete obstacles[i];
    }
    for (int i = 0; i < itemCount; i++)
    {
        delete items[i];
    }
}

float PlayState::currentSpeed()
{
    // The cap applies to the base speed, then the character
    // factor is multiplied in (Blueprint Section 3)
    float speed = worldSpeed * player->getSpeedFactor();
    if (slowMotion)
    {
        speed = speed * 0.5f;
    }
    return speed;
}

void PlayState::handleInput(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        const sf::Event::KeyPressed* key = event.getIf<sf::Event::KeyPressed>();
        if (key == nullptr)
        {
            return;
        }
        if (key->code == sf::Keyboard::Key::Space || key->code == sf::Keyboard::Key::W ||
            key->code == sf::Keyboard::Key::Up)
        {
            player->jump();
            sounds->playJump();
        }
        else if (key->code == sf::Keyboard::Key::S || key->code == sf::Keyboard::Key::Down)
        {
            player->startSlide();
        }
        else if (key->code == sf::Keyboard::Key::P || key->code == sf::Keyboard::Key::Escape)
        {
            pauseRequested = true;
        }
    }
}

void PlayState::update(float dt)
{
    if (finished)
    {
        return;
    }

    float speed = currentSpeed();

    // Slow motion counts down in real seconds, then speed is back
    if (slowMotion)
    {
        slowTimer = slowTimer - dt;
        if (slowTimer <= 0)
        {
            slowMotion = false;
            slowTimer = 0;
        }
    }

    // Speed ramp: rises slowly, stops at this map's cap
    worldSpeed = worldSpeed + 2.5f * dt;
    if (worldSpeed > map->getSpeedCap())
    {
        worldSpeed = map->getSpeedCap();
    }

    // The light stage of the run, picked from the score:
    // day under 200 points, sunset 200 to 499, night from 500
    if (score.getPoints() >= 500)
    {
        lightStage = 2;
    }
    else if (score.getPoints() >= 200)
    {
        lightStage = 1;
    }
    else
    {
        lightStage = 0;
    }

    if (invulnTimer > 0)
    {
        invulnTimer = invulnTimer - dt;
    }
    if (shakeTime > 0)
    {
        shakeTime = shakeTime - dt;
    }

    player->update(dt);

    // Distance, and 1 point for every 25 pixels of running
    distanceTravelled = distanceTravelled + speed * dt;
    while (distanceTravelled - lastPointDistance >= 25.0f)
    {
        score.add(1);
        lastPointDistance = lastPointDistance + 25.0f;
    }
    score.setDistance(static_cast<int>(distanceTravelled / 10.0f));

    if (distanceTravelled >= nextSpawnDistance)
    {
        spawnObstacle();
    }
    if (distanceTravelled >= nextItemDistance)
    {
        spawnCollectible();
    }

    for (int i = 0; i < obstacleCount; i++)
    {
        obstacles[i]->setSpeedX(speed);
        obstacles[i]->update(dt);
        if (!obstacles[i]->isPassed() &&
            obstacles[i]->getX() + obstacles[i]->getBounds().size.x < player->getX())
        {
            obstacles[i]->setPassed(true);
        }
    }
    for (int i = 0; i < itemCount; i++)
    {
        items[i]->setSpeedX(speed);
        items[i]->update(dt);
    }

    // Remove what has scrolled off the left edge
    for (int i = obstacleCount - 1; i >= 0; i--)
    {
        if (obstacles[i]->getX() + obstacles[i]->getBounds().size.x < -60)
        {
            removeObstacle(i);
        }
    }
    for (int i = itemCount - 1; i >= 0; i--)
    {
        if (items[i]->getX() + items[i]->getBounds().size.x < -60)
        {
            removeItem(i);
        }
    }

    checkCollisions();

    if (player->isDead())
    {
        finishRun();
    }
}

void PlayState::spawnObstacle()
{
    if (obstacleCount >= 20)
    {
        return;
    }

    // The 5 kinds cycle in a fixed order, so patterns stay fair
    // and readable instead of random and sometimes impossible
    Obstacle* ob = nullptr;
    int kind = spawnCounter % 5;
    if (kind == 0)
    {
        ob = new Rickshaw(1330);
    }
    else if (kind == 1)
    {
        ob = new Pothole(1330);
    }
    else if (kind == 2)
    {
        ob = new Barrier(1330);
    }
    else if (kind == 3)
    {
        ob = new Bus(1330);
    }
    else
    {
        ob = new Thela(1330);
    }
    obstacles[obstacleCount] = ob;
    obstacleCount = obstacleCount + 1;
    spawnCounter = spawnCounter + 1;

    // THE FAIRNESS RULE (Blueprint Section 3): the gap to the
    // next obstacle is never less than the distance the player
    // travels while jumping at the current speed, plus this
    // obstacle's width, plus a reaction margin, all scaled by
    // the map's gap factor. At any speed, with any character,
    // the next obstacle is always clearable.
    float airTime = 2.0f * 820.0f * 0.85f / 2200.0f; // lowest jump, Aryan
    float jumpDistance = currentSpeed() * airTime;
    float gap = (jumpDistance + ob->getBounds().size.x + 220.0f) * map->getGapFactor();
    nextSpawnDistance = distanceTravelled + gap;
}

void PlayState::spawnCollectible()
{
    if (itemCount >= 20)
    {
        return;
    }

    Collectible* item = nullptr;
    int kind = itemCounter % 7;
    if (kind == 5)
    {
        item = new BiryaniBox(1300, 552);
    }
    else if (kind == 6)
    {
        item = new ChaiCup(1300, 556);
    }
    else if (itemCounter % 2 == 0)
    {
        item = new Coin(1300, 566); // low coin: collected by running
    }
    else
    {
        item = new Coin(1300, 468); // high coin: collected mid jump
    }
    items[itemCount] = item;
    itemCount = itemCount + 1;
    itemCounter = itemCounter + 1;

    nextItemDistance = distanceTravelled + 430.0f + (itemCounter % 3) * 140.0f;
}

void PlayState::removeObstacle(int index)
{
    delete obstacles[index];
    obstacleCount = obstacleCount - 1;
    obstacles[index] = obstacles[obstacleCount];
    obstacles[obstacleCount] = nullptr;
}

void PlayState::removeItem(int index)
{
    delete items[index];
    itemCount = itemCount - 1;
    items[index] = items[itemCount];
    items[itemCount] = nullptr;
}

sf::FloatRect PlayState::playerHitbox()
{
    sf::FloatRect bounds = player->getBounds();
    if (player->isSliding())
    {
        // Sliding is low: only the bottom 35 percent can be hit
        return sf::FloatRect({bounds.position.x + bounds.size.x * 0.05f,
                              GROUND_Y - bounds.size.y * 0.35f},
                             {bounds.size.x * 0.9f, bounds.size.y * 0.35f});
    }
    // About 75 percent of the full box, centred
    return sf::FloatRect({bounds.position.x + bounds.size.x * 0.125f,
                          bounds.position.y + bounds.size.y * 0.125f},
                         {bounds.size.x * 0.75f, bounds.size.y * 0.75f});
}

void PlayState::checkCollisions()
{
    sf::FloatRect pBox = playerHitbox();

    // Collectibles first: touching one is always good
    for (int i = itemCount - 1; i >= 0; i--)
    {
        if (items[i]->getHitbox().findIntersection(pBox))
        {
            if (dynamic_cast<Coin*>(items[i]) != nullptr)
            {
                sounds->playCoin();
            }
            items[i]->apply(*player, score);
            if (items[i]->isSlowMotionRequested())
            {
                startSlowMotion();
                items[i]->clearSlowMotionRequest();
            }
            removeItem(i);
        }
    }

    if (invulnTimer > 0)
    {
        return; // flashing after a hit: one mistake costs one heart only
    }

    for (int i = obstacleCount - 1; i >= 0; i--)
    {
        Obstacle* ob = obstacles[i];
        if (!ob->getHitbox().findIntersection(pBox))
        {
            continue;
        }

        // Week 12-13 casting in real use: dynamic_cast tells us
        // the REAL type behind the Obstacle pointer.
        Barrier* barrier = dynamic_cast<Barrier*>(ob);
        Thela* thela = dynamic_cast<Thela*>(ob);

        if (player->canSmashLightObstacle() && (barrier != nullptr || thela != nullptr))
        {
            // Aryan's weight does the work: +20, a shake, no heart lost
            score.add(20, "Aryan smash");
            sounds->playSmash();
            shakeTime = 0.15f;
            removeObstacle(i);
            return;
        }

        if (barrier != nullptr && player->isSliding())
        {
            continue; // slid clean under the barrier's top bar
        }

        player->loseHeart();
        sounds->playHit();
        invulnTimer = 1.0f;
        removeObstacle(i);
        return; // one hit per frame, never two hearts at once
    }
}

void PlayState::finishRun()
{
    if (!bonusAdded)
    {
        // End of run bonus, added with the overloaded operator+
        // (Week 9): 1 bonus point for every 50 metres... in game
        // distance units, distance / 50.
        Score bonus;
        bonus.setPoints(score.getDistance() / 50);
        finalScore = score + bonus;
        bonusAdded = true;
    }
    finished = true;
}

void PlayState::startSlowMotion()
{
    slowMotion = true;
    slowTimer = 5.0f;
}

bool PlayState::isPauseRequested()
{
    return pauseRequested;
}

void PlayState::clearPauseRequest()
{
    pauseRequested = false;
}

bool PlayState::isFinished()
{
    return finished;
}

Score PlayState::getFinalScore()
{
    return finalScore;
}

std::string PlayState::getPlayerName()
{
    return player->getName();
}

std::string PlayState::getMapName()
{
    return map->getMapName();
}

int PlayState::getLightStage()
{
    return lightStage;
}

void PlayState::drawText(sf::RenderWindow& window, std::string text, float x, float y, int size, sf::Color color)
{
    if (!assets->hasFont())
    {
        return;
    }
    sf::Text label(assets->getFont(), text, size);
    label.setFillColor(color);
    label.setPosition({x, y});
    window.draw(label);
}

void PlayState::drawHud(sf::RenderWindow& window)
{
    drawText(window, "Score: " + std::to_string(score.getPoints()), 24, 16, 24, sf::Color::White);
    drawText(window, "Coins: " + std::to_string(score.getCoins()), 24, 48, 24, sf::Color(250, 200, 40));
    drawText(window, "Distance: " + std::to_string(score.getDistance()) + " m", 24, 80, 24, sf::Color::White);

    drawText(window, player->getName(), 560, 16, 24, sf::Color(250, 200, 110));
    drawText(window, map->getMapName(), 590, 48, 20, sf::Color(210, 210, 210));

    // Hearts as small red boxes, one per heart
    for (int i = 0; i < player->getHearts(); i++)
    {
        sf::RectangleShape heart({22, 22});
        heart.setPosition({1150.0f - i * 30.0f, 20});
        heart.setFillColor(sf::Color(215, 45, 55));
        window.draw(heart);
    }
    drawText(window, "Hearts", 1152, 48, 16, sf::Color(210, 210, 210));

    if (slowMotion)
    {
        drawText(window, "CHAI TIME - slow motion", 500, 90, 22, sf::Color(120, 230, 160));
    }
}

void PlayState::draw(sf::RenderWindow& window)
{
    // Small screen shake when Aryan smashes something
    bool shaking = shakeTime > 0;
    if (shaking)
    {
        sf::View view = window.getDefaultView();
        if (static_cast<int>(shakeTime * 20.0f) % 2 == 0)
        {
            view.move({4, 0});
        }
        else
        {
            view.move({-4, 0});
        }
        window.setView(view);
    }

    // The map draws the whole background: one call, and the
    // right city appears (polymorphism through the Map pointer)
    map->drawBackground(window, distanceTravelled, lightStage);

    for (int i = 0; i < itemCount; i++)
    {
        items[i]->draw(window);
    }
    for (int i = 0; i < obstacleCount; i++)
    {
        obstacles[i]->draw(window);
    }

    // After a hit the player flashes: skip the draw on alternate
    // tenths of a second while invulnerable
    bool flashOff = invulnTimer > 0 && static_cast<int>(invulnTimer * 10.0f) % 2 == 0;
    if (!flashOff)
    {
        player->draw(window);
    }

    drawHud(window);

    if (shaking)
    {
        window.setView(window.getDefaultView());
    }
}
