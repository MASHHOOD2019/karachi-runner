// Author: Mashhood Ali
#include "SoundManager.h"
#include <fstream>

SoundManager::SoundManager()
    : jumpSound(jumpBuffer), coinSound(coinBuffer), hitSound(hitBuffer),
      clickSound(clickBuffer), smashSound(smashBuffer), gameOverSound(gameOverBuffer)
{
    // SFML 3 note: an sf::Sound is born with its buffer, so each
    // sound above starts tied to its (still empty) buffer member,
    // and loadOne() fills that buffer later. The buffers are
    // declared before the sounds in the class, so they exist
    // first (Week 2: member construction order follows the
    // declaration order, not the list order).
    jumpLoaded = false;
    coinLoaded = false;
    hitLoaded = false;
    clickLoaded = false;
    smashLoaded = false;
    gameOverLoaded = false;
    loadedCount = 0;
}

bool SoundManager::loadOne(sf::SoundBuffer& buffer, sf::Sound& sound, std::string fileName)
{
    // The file is checked first, so a missing sound is skipped
    // in complete silence: no crash and no error messages
    std::ifstream probe(fileName);
    if (!probe.good())
    {
        return false;
    }
    if (!buffer.loadFromFile(fileName))
    {
        return false; // a damaged file is skipped the same way
    }
    sound.setBuffer(buffer);
    return true;
}

void SoundManager::loadAll()
{
    loadedCount = 0;
    jumpLoaded = loadOne(jumpBuffer, jumpSound, "assets/audio/jump.wav");
    if (jumpLoaded) { loadedCount = loadedCount + 1; }
    coinLoaded = loadOne(coinBuffer, coinSound, "assets/audio/coin.wav");
    if (coinLoaded) { loadedCount = loadedCount + 1; }
    hitLoaded = loadOne(hitBuffer, hitSound, "assets/audio/hit.wav");
    if (hitLoaded) { loadedCount = loadedCount + 1; }
    clickLoaded = loadOne(clickBuffer, clickSound, "assets/audio/click.wav");
    if (clickLoaded) { loadedCount = loadedCount + 1; }
    smashLoaded = loadOne(smashBuffer, smashSound, "assets/audio/smash.wav");
    if (smashLoaded) { loadedCount = loadedCount + 1; }
    gameOverLoaded = loadOne(gameOverBuffer, gameOverSound, "assets/audio/gameover.wav");
    if (gameOverLoaded) { loadedCount = loadedCount + 1; }
}

void SoundManager::playJump()
{
    if (jumpLoaded)
    {
        jumpSound.play();
    }
}

void SoundManager::playCoin()
{
    if (coinLoaded)
    {
        coinSound.play();
    }
}

void SoundManager::playHit()
{
    if (hitLoaded)
    {
        hitSound.play();
    }
}

void SoundManager::playClick()
{
    if (clickLoaded)
    {
        clickSound.play();
    }
}

void SoundManager::playSmash()
{
    if (smashLoaded)
    {
        smashSound.play();
    }
}

void SoundManager::playGameOver()
{
    if (gameOverLoaded)
    {
        gameOverSound.play();
    }
}

int SoundManager::getLoadedCount()
{
    return loadedCount;
}
