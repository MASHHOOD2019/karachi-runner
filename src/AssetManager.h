// Author: Mashhood Ali
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

// Loads and owns every texture and the font, once, at the start
// (Week 2 encapsulation, Week 5 association, Week 7-8 exceptions).
// This class is the outline-safe replacement for a templated
// resource manager: named members and normal functions only.
// Other classes use its textures; the textures live and die here.
class AssetManager
{
private:
    sf::Font mainFont;
    bool fontLoaded;
    sf::Texture playerTexture;
    bool playerTextureLoaded;
    sf::Texture obstacleTexture;
    bool obstacleTextureLoaded;

public:
    AssetManager();

    void loadFont(std::string fileName);
    void loadTexture(std::string name, std::string fileName);
    sf::Font& getFont();
    bool hasFont();
    sf::Texture& getTexture(std::string name);
};

#endif
