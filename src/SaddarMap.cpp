// Author: Mashhood Ali
#include "SaddarMap.h"

// The Urdu tribute line of blueprint Section 6.3, kept as UTF-8
// bytes. It is drawn ONLY when assets/fonts/urdu.ttf exists (see
// Map::drawUrduText). Without that font the panel stays empty,
// because broken glyph boxes would be worse than no text.
const char* SADDAR_URDU_LINE = "علم دیا، راستہ دکھایا، شکریہ سر فیصل فیروز";

SaddarMap::SaddarMap()
    : Map("Saddar", 360, 620, 1.00f)
{
    dayTop = sf::Color(110, 150, 195);
    dayBottom = sf::Color(238, 205, 140);
    sunsetTop = sf::Color(48, 34, 84);
    sunsetBottom = sf::Color(226, 112, 54);
    nightTop = sf::Color(8, 10, 30);
    nightBottom = sf::Color(58, 48, 86);
    roadColor = sf::Color(52, 48, 50); // old city asphalt and stone

    addLandmark("KMC Market");
    addLandmark("KMC Building");
    addLandmark("Zainab Market");
    addLandmark("Rainbow Centre");
    addLandmark("Bohri Bazaar");

    addSign("SADDAR");
    addSign("KMC MARKET");
    addSign("ZAINAB MARKET");
}

void SaddarMap::drawBackground(sf::RenderWindow& window, float scrollX, int stage)
{
    drawSky(window, stage);

    // Far layer: old rooftops, the Empress Market clock tower
    // and the twin spires of St Patrick's Cathedral
    sf::Color farColor = shade(sf::Color(58, 50, 72), stage == 0 ? 1.5f : 1.0f);
    for (int i = 0; i < 4; i++)
    {
        float bx = parallaxX(430, i, scrollX, 0.3f, 1720);

        sf::RectangleShape roof({170, 90});
        roof.setPosition({bx, 495});
        roof.setFillColor(farColor);
        window.draw(roof);
        sf::RectangleShape tank({26, 20});
        tank.setPosition({bx + 110, 478});
        tank.setFillColor(farColor);
        window.draw(tank);

        if (i == 1)
        {
            // The clock tower of Empress Market, now KMC Market
            sf::RectangleShape tower({54, 300});
            tower.setPosition({bx + 200, 285});
            tower.setFillColor(shade(sf::Color(150, 124, 84), stage >= 2 ? 0.5f : 1.0f));
            window.draw(tower);
            sf::ConvexShape cap;
            cap.setPointCount(3);
            cap.setPoint(0, {0, 34});
            cap.setPoint(1, {27, 0});
            cap.setPoint(2, {54, 34});
            cap.setPosition({bx + 200, 252});
            cap.setFillColor(farColor);
            window.draw(cap);
            sf::CircleShape clockFace(19);
            clockFace.setPosition({bx + 208, 306});
            clockFace.setFillColor(sf::Color(238, 234, 220));
            window.draw(clockFace);
            sf::RectangleShape hand1({3, 14});
            hand1.setPosition({bx + 226, 312});
            hand1.setFillColor(sf::Color(40, 36, 30));
            window.draw(hand1);
            sf::RectangleShape hand2({11, 3});
            hand2.setPosition({bx + 227, 324});
            hand2.setFillColor(sf::Color(40, 36, 30));
            window.draw(hand2);
        }
        if (i == 3)
        {
            // The cathedral spires, kept quiet in the far layer
            for (int s = 0; s < 2; s++)
            {
                float sx = bx + 190 + s * 64;
                sf::RectangleShape spireTower({20, 130});
                spireTower.setPosition({sx, 400});
                spireTower.setFillColor(farColor);
                window.draw(spireTower);
                sf::ConvexShape spire;
                spire.setPointCount(3);
                spire.setPoint(0, {0, 44});
                spire.setPoint(1, {10, 0});
                spire.setPoint(2, {20, 44});
                spire.setPosition({sx, 358});
                spire.setFillColor(farColor);
                window.draw(spire);
                sf::RectangleShape crossV({3, 14});
                crossV.setPosition({sx + 8.5f, 342});
                crossV.setFillColor(farColor);
                window.draw(crossV);
                sf::RectangleShape crossH({9, 3});
                crossH.setPosition({sx + 5.5f, 347});
                crossH.setFillColor(farColor);
                window.draw(crossH);
            }
        }
    }

    // Mid layer: the dense shop fronts of Saddar. Building after
    // building, each front stacked with signboards. One building
    // in every five carries the decorated dedication panel in
    // its middle row (blueprint 6.3, appearance 2 of 4).
    const char* boardTexts[7] = {"Empress Market", "Zainab Market", "Rainbow Centre",
                                 "Bohri Bazaar", "KMC Market", "Mobile Market",
                                 "Regal Chowk"};
    sf::Color boardColors[5] = {sf::Color(178, 34, 44), sf::Color(24, 92, 52),
                                sf::Color(30, 80, 150), sf::Color(240, 170, 30),
                                sf::Color(120, 40, 110)};

    float scrolled = scrollX * 0.75f;
    int firstIndex = static_cast<int>(scrolled / 300.0f);
    float frac = scrolled - firstIndex * 300.0f;

    for (int i = 0; i < 5; i++)
    {
        float bx = i * 300.0f - frac;
        int worldIndex = firstIndex + i;

        sf::RectangleShape front({296, 205});
        front.setPosition({bx, 380});
        front.setFillColor(shade(sf::Color(122, 102, 84), stage >= 2 ? 0.5f : 1.0f));
        window.draw(front);

        for (int row = 0; row < 3; row++)
        {
            float by = 424.0f + row * 58.0f;
            if (row == 1 && worldIndex % 5 == 2)
            {
                // THE dedication wall panel: a truck art style
                // decorated border. The Urdu line is drawn only
                // when the Urdu font file exists; otherwise the
                // panel stays decorated and empty of text.
                sf::RectangleShape outer({252, 104});
                outer.setPosition({bx + 22, by - 52});
                outer.setFillColor(sf::Color(245, 200, 40));
                window.draw(outer);
                sf::RectangleShape mid({240, 92});
                mid.setPosition({bx + 28, by - 46});
                mid.setFillColor(sf::Color(200, 45, 45));
                window.draw(mid);
                sf::RectangleShape inner({228, 80});
                inner.setPosition({bx + 34, by - 40});
                inner.setFillColor(sf::Color(246, 238, 214));
                window.draw(inner);
                if (hasUrduFont())
                {
                    drawUrduText(window, SADDAR_URDU_LINE, bx + 148, by, 15,
                                 sf::Color(96, 40, 60));
                }
                continue;
            }
            int pick = (worldIndex * 3 + row) % 7;
            sf::Color panel = boardColors[(worldIndex + row) % 5];
            drawBoard(window, boardTexts[pick], bx + 148, by, 248, 46,
                      panel, sf::Color::White, 19);
        }
    }

    // Overhead wires between the buildings, thin dark lines
    sf::Color wireColor(30, 28, 34);
    sf::Vertex wire1[2];
    wire1[0].position = {0, 352};
    wire1[0].color = wireColor;
    wire1[1].position = {1280, 368};
    wire1[1].color = wireColor;
    window.draw(wire1, 2, sf::PrimitiveType::Lines);
    sf::Vertex wire2[2];
    wire2[0].position = {0, 372};
    wire2[0].color = wireColor;
    wire2[1].position = {1280, 358};
    wire2[1].color = wireColor;
    window.draw(wire2, 2, sf::PrimitiveType::Lines);

    // Pavement strip in front of the shops
    sf::RectangleShape pavement({1280, 35});
    pavement.setPosition({0, 585});
    pavement.setFillColor(shade(sf::Color(140, 128, 110), stage >= 2 ? 0.5f : 1.0f));
    window.draw(pavement);

    drawRoad(window, scrollX, stage, sf::Color(205, 195, 175));
}
