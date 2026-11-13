// Author: Mashhood Ali
#include "ShayanPlayer.h"

// GameObject is a virtual base class, so the most derived class
// (this one) calls its constructor directly in the list below.
ShayanPlayer::ShayanPlayer()
    : GameObject(0, 0), Player("Shayan", 3, 1.15f, 0.35f, 1.15f, 36, 52, sf::Color(230, 90, 30))
{
    // Slimmer body than Mashhood, bright red orange T-shirt
    setBagColor(sf::Color(60, 60, 60));
}

std::string ShayanPlayer::getTitle()
{
    return "Fastest legs in Karachi. Brakes sold separately.";
}
