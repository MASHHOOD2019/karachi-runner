// Author: Mashhood Ali
#include "Map.h"
#include <cmath>
#include <fstream>

Map::Map(std::string name, float speed, float cap, float gap)
{
    mapName = name;
    startSpeed = speed;
    speedCap = cap;
    gapFactor = gap;
    landmarkCount = 0;
    signCount = 0;
    assets = nullptr;
    urduFontLoaded = false;

    // Safe defaults; every child map sets its own colours
    dayTop = sf::Color(105, 165, 215);
    dayBottom = sf::Color(250, 222, 150);
    sunsetTop = sf::Color(56, 40, 92);
    sunsetBottom = sf::Color(238, 128, 62);
    nightTop = sf::Color(9, 11, 32);
    nightBottom = sf::Color(52, 50, 88);
    roadColor = sf::Color(45, 43, 52);
}

Map::~Map()
{
}

void Map::useAssets(AssetManager& assetManager)
{
    assets = &assetManager;

    // The Urdu font is optional. The file is checked first and
    // only loaded when it really exists; if it is not there the
    // Urdu lines are simply skipped and nothing breaks.
    std::ifstream probe("assets/fonts/urdu.ttf");
    if (probe.good() && urduFont.openFromFile("assets/fonts/urdu.ttf"))
    {
        urduFontLoaded = true;
    }
}

void Map::addLandmark(std::string name)
{
    if (landmarkCount < 10)
    {
        landmarks[landmarkCount] = name;
        landmarkCount = landmarkCount + 1;
    }
}

void Map::addSign(std::string text)
{
    if (signCount < 10)
    {
        signs[signCount] = text;
        signCount = signCount + 1;
    }
}

int Map::getLandmarkCount()
{
    return landmarkCount;
}

std::string Map::getLandmark(int i)
{
    if (i < 0 || i >= landmarkCount)
    {
        return "";
    }
    return landmarks[i];
}

int Map::getSignCount()
{
    return signCount;
}

std::string Map::getSign(int i)
{
    if (i < 0 || i >= signCount)
    {
        return "";
    }
    return signs[i];
}

sf::Color Map::skyTopFor(int stage)
{
    if (stage == 1)
    {
        return sunsetTop;
    }
    if (stage >= 2)
    {
        return nightTop;
    }
    return dayTop;
}

sf::Color Map::skyBottomFor(int stage)
{
    if (stage == 1)
    {
        return sunsetBottom;
    }
    if (stage >= 2)
    {
        return nightBottom;
    }
    return dayBottom;
}

sf::Color Map::shade(sf::Color color, float factor)
{
    // static_cast: float maths back into a colour channel (W12)
    int r = static_cast<int>(color.r * factor);
    int g = static_cast<int>(color.g * factor);
    int b = static_cast<int>(color.b * factor);
    if (r > 255) { r = 255; }
    if (g > 255) { g = 255; }
    if (b > 255) { b = 255; }
    return sf::Color(static_cast<std::uint8_t>(r),
                     static_cast<std::uint8_t>(g),
                     static_cast<std::uint8_t>(b));
}

void Map::drawSky(sf::RenderWindow& window, int stage)
{
    sf::RectangleShape top({1280, 470});
    top.setPosition({0, 0});
    top.setFillColor(skyTopFor(stage));
    window.draw(top);

    sf::RectangleShape bottom({1280, 152});
    bottom.setPosition({0, 470});
    bottom.setFillColor(skyBottomFor(stage));
    window.draw(bottom);

    // One disc in the sky: the sun by day, low and orange at
    // sunset, and a pale moon at night
    sf::CircleShape disc(34);
    if (stage == 0)
    {
        disc.setPosition({1010, 90});
        disc.setFillColor(sf::Color(252, 232, 160));
    }
    else if (stage == 1)
    {
        disc.setRadius(46);
        disc.setPosition({990, 330});
        disc.setFillColor(sf::Color(250, 150, 60));
    }
    else
    {
        disc.setPosition({1030, 80});
        disc.setFillColor(sf::Color(225, 228, 235));
    }
    window.draw(disc);

    if (stage >= 2)
    {
        // Simple stars: fixed dots from plain arithmetic
        for (int i = 0; i < 26; i++)
        {
            float sx = static_cast<float>((i * 197) % 1240) + 20.0f;
            float sy = static_cast<float>((i * 89) % 260) + 20.0f;
            sf::RectangleShape star({3, 3});
            star.setPosition({sx, sy});
            star.setFillColor(sf::Color(230, 230, 240));
            window.draw(star);
        }
    }
}

void Map::drawRoad(sf::RenderWindow& window, float scrollX, int stage, sf::Color dashColor)
{
    sf::Color road = roadColor;
    if (stage >= 2)
    {
        road = shade(roadColor, 0.55f);
    }

    sf::RectangleShape roadRect({1280, 100});
    roadRect.setPosition({0, 620});
    roadRect.setFillColor(road);
    window.draw(roadRect);

    sf::RectangleShape edge({1280, 5});
    edge.setPosition({0, 620});
    edge.setFillColor(shade(road, 1.5f));
    window.draw(edge);

    // Moving dashes on the road sell the speed
    float dashScroll = std::fmod(scrollX, 90.0f);
    for (int i = 0; i < 15; i++)
    {
        sf::RectangleShape dash({46, 5});
        dash.setPosition({i * 90.0f - dashScroll, 668});
        dash.setFillColor(dashColor);
        window.draw(dash);
    }
}

float Map::parallaxX(float spacing, int index, float scrollX, float factor, float loopLength)
{
    // Where one scrolling prop belongs this frame. Props are
    // spaced evenly over one loop length; when a prop leaves the
    // left edge it wraps to the right end of the loop.
    float moved = std::fmod(scrollX * factor, loopLength);
    float x = index * spacing - moved;
    if (x < -320)
    {
        x = x + loopLength;
    }
    return x;
}

void Map::drawTextAt(sf::RenderWindow& window, std::string text, float x, float y, int size, sf::Color color)
{
    if (assets == nullptr || !assets->hasFont())
    {
        return;
    }
    sf::Text label(assets->getFont(), text, size);
    label.setFillColor(color);
    label.setPosition({x, y});
    window.draw(label);
}

void Map::drawTextCenter(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color)
{
    if (assets == nullptr || !assets->hasFont())
    {
        return;
    }
    sf::Text label(assets->getFont(), text, size);
    label.setFillColor(color);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2});
    label.setPosition({cx, y});
    window.draw(label);
}

void Map::drawBoard(sf::RenderWindow& window, std::string text, float cx, float y,
                    float w, float h, sf::Color panel, sf::Color ink, int textSize)
{
    sf::RectangleShape board({w, h});
    board.setPosition({cx - w / 2, y - h / 2});
    board.setFillColor(panel);
    window.draw(board);

    sf::RectangleShape frame({w - 8, h - 8});
    frame.setPosition({cx - w / 2 + 4, y - h / 2 + 4});
    frame.setFillColor(panel);
    frame.setOutlineColor(ink);
    frame.setOutlineThickness(2);
    window.draw(frame);

    drawTextCenter(window, text, cx, y, textSize, ink);
}

bool Map::hasUrduFont()
{
    return urduFontLoaded;
}

void Map::drawUrduText(sf::RenderWindow& window, std::string utf8Text, float cx, float cy, int size, sf::Color color)
{
    if (!urduFontLoaded)
    {
        return;
    }
    // The line is stored as UTF-8 bytes, so it is converted the
    // proper way before SFML draws it
    sf::String text = sf::String::fromUtf8(utf8Text.begin(), utf8Text.end());
    sf::Text label(urduFont, text, size);
    label.setFillColor(color);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2});
    label.setPosition({cx, cy});
    window.draw(label);
}
