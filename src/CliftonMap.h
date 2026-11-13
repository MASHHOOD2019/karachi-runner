// Author: Mashhood Ali
#ifndef CLIFTONMAP_H
#define CLIFTONMAP_H

#include "Map.h"

// Map 1, the easiest: Clifton and Sea View. The sea, the
// promenade, Teen Talwar, the big flag and the towers, drawn as
// simple silhouettes in the shared light of the day.
class CliftonMap : public Map
{
public:
    CliftonMap();
    void drawBackground(sf::RenderWindow& window, float scrollX, int stage);
};

#endif
