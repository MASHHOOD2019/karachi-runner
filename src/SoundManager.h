// Author: Mashhood Ali
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <string>

// All sound in one place (Week 2 encapsulation, resource
// ownership). Buffers are loaded once and live here; the sound
// objects play from them. Loading is forgiving on purpose: a
// missing sound file is skipped quietly, never a crash, so the
// game runs the same with or without its audio folder.
class SoundManager
{
private:
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer coinBuffer;
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer smashBuffer;
    sf::SoundBuffer gameOverBuffer;

    sf::Sound jumpSound;
    sf::Sound coinSound;
    sf::Sound hitSound;
    sf::Sound clickSound;
    sf::Sound smashSound;
    sf::Sound gameOverSound;

    bool jumpLoaded;
    bool coinLoaded;
    bool hitLoaded;
    bool clickLoaded;
    bool smashLoaded;
    bool gameOverLoaded;
    int loadedCount;

    bool loadOne(sf::SoundBuffer& buffer, sf::Sound& sound, std::string fileName);

public:
    SoundManager();

    void loadAll();
    void playJump();
    void playCoin();
    void playHit();
    void playClick();
    void playSmash();
    void playGameOver();

    int getLoadedCount();
};

#endif
