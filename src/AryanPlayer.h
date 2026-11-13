// Author: Mashhood Ali
#ifndef ARYANPLAYER_H
#define ARYANPLAYER_H

#include "Player.h"

// Aryan, the heavy one. Biggest body, slowest speed, lowest jump,
// but 4 hearts, and his weight lets him smash light wooden
// obstacles (road barriers and thelas) without losing a heart.
class AryanPlayer : public Player
{
public:
    AryanPlayer();
    std::string getTitle();
    bool canSmashLightObstacle();
};

#endif
