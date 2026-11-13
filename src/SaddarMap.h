// Author: Mashhood Ali
#ifndef SADDARMAP_H
#define SADDARMAP_H

#include "Map.h"

// Map 4, the hardest: Saddar, the old city. A wall of shop
// signboards, the Empress Market (KMC Market) clock tower and
// the cathedral spires. One decorated wall panel lives here
// (blueprint Section 6.3, dedication appearance 2 of 4).
class SaddarMap : public Map
{
public:
    SaddarMap();
    void drawBackground(sf::RenderWindow& window, float scrollX, int stage);
};

#endif
