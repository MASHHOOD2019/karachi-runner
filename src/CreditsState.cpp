// Author: Mashhood Ali
#include "CreditsState.h"
#include <fstream>

// The second dedication line of blueprint Section 6.4, kept as
// UTF-8 bytes: "A teacher's guidance is the real asset."
const char* CREDITS_URDU_LINE = "استاد کی رہنمائی ہی اصل سرمایہ ہے";

CreditsState::CreditsState(AssetManager& assetManager)
{
    assets = &assetManager;
    backRequested = false;

    // Optional, like everywhere in this game: the file is
    // checked first, and if the Urdu font is not there, the
    // Urdu line is simply skipped and nothing breaks
    urduFontLoaded = false;
    std::ifstream probe("assets/fonts/urdu.ttf");
    if (probe.good())
    {
        urduFontLoaded = urduFont.openFromFile("assets/fonts/urdu.ttf");
    }
}

void CreditsState::handleInput(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        const sf::Event::KeyPressed* key = event.getIf<sf::Event::KeyPressed>();
        if (key != nullptr &&
            (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Enter))
        {
            backRequested = true;
        }
    }
}

void CreditsState::update(float dt)
{
    (void)dt; // a still screen; only input matters here
}

void CreditsState::drawBackground(sf::RenderWindow& window)
{
    // The shared Karachi sunset, same as the menu
    sf::RectangleShape skyTop({1280, 300});
    skyTop.setPosition({0, 0});
    skyTop.setFillColor(sf::Color(38, 32, 64));
    window.draw(skyTop);

    sf::RectangleShape skyMid({1280, 180});
    skyMid.setPosition({0, 300});
    skyMid.setFillColor(sf::Color(120, 40, 90));
    window.draw(skyMid);

    sf::RectangleShape skyLow({1280, 140});
    skyLow.setPosition({0, 480});
    skyLow.setFillColor(sf::Color(230, 120, 60));
    window.draw(skyLow);

    sf::RectangleShape road({1280, 100});
    road.setPosition({0, 620});
    road.setFillColor(sf::Color(40, 36, 48));
    window.draw(road);
}

void CreditsState::drawText(sf::RenderWindow& window, std::string text, float cx, float y, int size, sf::Color color)
{
    if (!assets->hasFont())
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

void CreditsState::drawUrduLine(sf::RenderWindow& window, float cx, float y, int size, sf::Color color)
{
    if (!urduFontLoaded)
    {
        return;
    }
    std::string line = CREDITS_URDU_LINE;
    sf::String text = sf::String::fromUtf8(line.begin(), line.end());
    sf::Text label(urduFont, text, size);
    label.setFillColor(color);
    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y / 2});
    label.setPosition({cx, y});
    window.draw(label);
}

void CreditsState::draw(sf::RenderWindow& window)
{
    drawBackground(window);

    drawText(window, "CREDITS", 640, 90, 48, sf::Color(250, 200, 110));

    drawText(window, "Karachi Runner", 640, 190, 30, sf::Color::White);
    drawText(window, "OOP Course Project CS 1420", 640, 240, 24, sf::Color(220, 220, 220));
    drawText(window, "Instructor: Sir Faisal Feroze", 640, 300, 26, sf::Color(250, 200, 110));
    drawText(window, "Made by Mashhood Ali", 640, 350, 24, sf::Color::White);
    drawText(window, "Muhammad Ali Jinnah University, Karachi", 640, 395, 22, sf::Color(220, 220, 220));

    // The professional line of blueprint 6.4, English first...
    drawText(window, "A teacher's guidance is the real asset.", 640, 480, 22, sf::Color(120, 230, 160));
    // ...and in Urdu too, when the Urdu font file is present
    drawUrduLine(window, 640, 522, 20, sf::Color(120, 230, 160));

    drawText(window, "Press Esc to go back", 640, 600, 20, sf::Color(200, 200, 200));
}

bool CreditsState::isBackRequested()
{
    return backRequested;
}
