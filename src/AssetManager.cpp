// Author: Mashhood Ali
#include "AssetManager.h"
#include "FileLoadException.h"

AssetManager::AssetManager()
{
    fontLoaded = false;
    playerTextureLoaded = false;
    obstacleTextureLoaded = false;
}

void AssetManager::loadFont(std::string fileName)
{
    if (!mainFont.openFromFile(fileName))
    {
        throw FileLoadException(fileName);
    }
    fontLoaded = true;
}

void AssetManager::loadTexture(std::string name, std::string fileName)
{
    // Plain if/else selection by name, no maps and no templates
    if (name == "player")
    {
        if (!playerTexture.loadFromFile(fileName))
        {
            throw FileLoadException(fileName);
        }
        playerTextureLoaded = true;
    }
    else if (name == "obstacle")
    {
        if (!obstacleTexture.loadFromFile(fileName))
        {
            throw FileLoadException(fileName);
        }
        obstacleTextureLoaded = true;
    }
}

sf::Font& AssetManager::getFont()
{
    return mainFont;
}

bool AssetManager::hasFont()
{
    return fontLoaded;
}

sf::Texture& AssetManager::getTexture(std::string name)
{
    if (name == "obstacle")
    {
        return obstacleTexture;
    }
    return playerTexture;
}
