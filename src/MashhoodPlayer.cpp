// Author: Mashhood Ali
#include "MashhoodPlayer.h"

// GameObject is a virtual base class, so the most derived class
// (this one) calls its constructor directly in the list below.
MashhoodPlayer::MashhoodPlayer()
    : GameObject(0, 0), Player("Mashhood Ali", 3, 1.00f, 0.60f, 1.00f, 42, 54, sf::Color(20, 110, 60))
{
    // Dark green T-shirt and a navy backpack, his identity marker
    setBagColor(sf::Color(25, 35, 90));
}

std::string MashhoodPlayer::getTitle()
{
    return "The all-rounder. Late for class, never late on a jump.";
}
