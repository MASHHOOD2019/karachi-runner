// Author: Mashhood Ali
#ifndef SHAYANPLAYER_H
#define SHAYANPLAYER_H

#include "Player.h"

// Shayan, the fast one. Highest speed and jump, but the shortest
// slide. That short slide is his weakness, by design.
class ShayanPlayer : public Player
{
public:
    ShayanPlayer();
    std::string getTitle();
};

#endif
