// Author: Mashhood Ali
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include "AssetManager.h"

// One Karachi area as one object (Week 2 encapsulation, Week 3
// arrays of strings, Week 5 aggregation, Week 10 abstract class).
// A map HOLDS the names of its landmarks and its sign boards as
// data (aggregation: the names are grouped and used by the map,
// they are not owned things with their own lifetime problem), and
// it knows its own start speed, speed cap and gap factor, so
// switching maps is switching one object, not rewriting the game.
// drawBackground() is pure virtual: every area draws itself.
class Map
{
private:
    std::string mapName;
    float startSpeed;
    float speedCap;
    float gapFactor;
    std::string landmarks[10];
    int landmarkCount;
    std::string signs[10];
    int signCount;
    AssetManager* assets; // association: the assets belong to Game
    sf::Font urduFont;
    bool urduFontLoaded;

protected:
    // Sky colours for the 3 light stages, filled by each child:
    // stage 0 day, stage 1 sunset, stage 2 night
    sf::Color dayTop;
    sf::Color dayBottom;
    sf::Color sunsetTop;
    sf::Color sunsetBottom;
    sf::Color nightTop;
    sf::Color nightBottom;
    sf::Color roadColor;

    void addLandmark(std::string name);
    void addSign(std::string text);

    sf::Color skyTopFor(int stage);
    sf::Color skyBottomFor(int stage);
    sf::Color shade(sf::Color color, float factor);

    void drawSky(sf::RenderWindow& window, int stage);
    void drawRoad(sf::RenderWindow& window, float scrollX, int stage, sf::Color dashColor);
    float parallaxX(float spacing, int index, float scrollX, float factor, float loopLength);

    void drawTextAt(sf::RenderWindow& window, std::string text, float x, float y, int size, sf::Color color);
    void drawTextCenter(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color);
    void drawBoard(sf::RenderWindow& window, std::string text, float cx, float y,
                   float w, float h, sf::Color panel, sf::Color ink, int textSize);

    bool hasUrduFont();
    void drawUrduText(sf::RenderWindow& window, std::string utf8Text, float cx, float cy, int size, sf::Color color);

public:
    Map(std::string name, float speed, float cap, float gap);
    virtual ~Map();

    void useAssets(AssetManager& assetManager);

    virtual void drawBackground(sf::RenderWindow& window, float scrollX, int stage) = 0;

    inline std::string getMapName() { return mapName; }
    inline float getStartSpeed() { return startSpeed; }
    inline float getSpeedCap() { return speedCap; }
    inline float getGapFactor() { return gapFactor; }
    int getLandmarkCount();
    std::string getLandmark(int i);
    int getSignCount();
    std::string getSign(int i);
};

#endif
