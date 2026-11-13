// Author: Mashhood Ali
#ifndef SHAHRAHMAP_H
#define SHAHRAHMAP_H

#include "Map.h"

// Map 2, medium: Shahrah-e-Faisal, the big road to the airport.
// Green gantry signs, the FTC block, pedestrian bridges with ad
// panels, multi lane asphalt, and one special billboard (see
// blueprint Section 6.2, dedication appearance 1 of 4).
class ShahrahMap : public Map
{
public:
    ShahrahMap();
    void drawBackground(sf::RenderWindow& window, float scrollX, int stage);
};

#endif
