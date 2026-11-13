// Author: Mashhood Ali
#ifndef MASHHOODPLAYER_H
#define MASHHOODPLAYER_H

#include "Player.h"

// Mashhood Ali, the balanced main character (Week 4-5 single
// inheritance). All his values are standard: nothing special,
// nothing weak.
class MashhoodPlayer : public Player
{
public:
    MashhoodPlayer();
    std::string getTitle();
};

#endif
