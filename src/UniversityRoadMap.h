// Author: Mashhood Ali
#ifndef UNIVERSITYROADMAP_H
#define UNIVERSITYROADMAP_H

#include "Map.h"

// Map 3, medium hard: University Road, the education corridor.
// Gate after gate (Karachi University, NED, Urdu University,
// Sir Syed), the Expo Centre halls and the planetarium dome.
class UniversityRoadMap : public Map
{
public:
    UniversityRoadMap();
    void drawBackground(sf::RenderWindow& window, float scrollX, int stage);
};

#endif
