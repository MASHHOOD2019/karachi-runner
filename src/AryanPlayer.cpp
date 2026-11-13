// Author: Mashhood Ali
#include "AryanPlayer.h"

// GameObject is a virtual base class, so the most derived class
// (this one) calls its constructor directly in the list below.
AryanPlayer::AryanPlayer()
    : GameObject(0, 0), Player("Aryan", 4, 0.85f, 0.60f, 0.85f, 56, 68, sf::Color(215, 165, 25))
{
    // Mustard yellow kurta style shirt, drawn bigger on purpose:
    // 56 x 68 body against the 42 x 54 of Mashhood
    setBagColor(sf::Color(110, 75, 40));
}

std::string AryanPlayer::getTitle()
{
    return "Built solid. Barriers move out of HIS way.";
}

bool AryanPlayer::canSmashLightObstacle()
{
    return true;
}
