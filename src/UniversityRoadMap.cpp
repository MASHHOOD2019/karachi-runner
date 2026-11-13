// Author: Mashhood Ali
#include "UniversityRoadMap.h"

UniversityRoadMap::UniversityRoadMap()
    : Map("University Road", 340, 620, 1.05f)
{
    dayTop = sf::Color(102, 158, 208);
    dayBottom = sf::Color(246, 218, 148);
    sunsetTop = sf::Color(52, 38, 90);
    sunsetBottom = sf::Color(234, 124, 60);
    nightTop = sf::Color(8, 10, 30);
    nightBottom = sf::Color(50, 48, 86);
    roadColor = sf::Color(48, 46, 54);

    addLandmark("Karachi University Gate");
    addLandmark("NED University");
    addLandmark("Urdu University");
    addLandmark("Sir Syed University");
    addLandmark("Expo Centre");
    addLandmark("PIA Planetarium");

    addSign("UNIVERSITY ROAD");
    addSign("EXPO CENTRE");
    addSign("NIPA");
}

void UniversityRoadMap::drawBackground(sf::RenderWindow& window, float scrollX, int stage)
{
    drawSky(window, stage);

    // Far layer: Expo Centre halls, the planetarium dome, a
    // flyover beam and stadium floodlight pylons
    sf::Color farColor = shade(sf::Color(54, 48, 74), stage == 0 ? 1.5f : 1.0f);
    for (int i = 0; i < 4; i++)
    {
        float bx = parallaxX(430, i, scrollX, 0.3f, 1720);

        if (i == 0)
        {
            // Expo Centre: one very long low hall, flat roof
            sf::RectangleShape hall({260, 78});
            hall.setPosition({bx, 507});
            hall.setFillColor(farColor);
            window.draw(hall);
            sf::RectangleShape banner({260, 14});
            banner.setPosition({bx, 507});
            banner.setFillColor(sf::Color(190, 60, 60));
            window.draw(banner);
        }
        if (i == 1)
        {
            // PIA Planetarium: a white dome on a round base
            sf::RectangleShape base({120, 40});
            base.setPosition({bx + 60, 545});
            base.setFillColor(farColor);
            window.draw(base);
            sf::CircleShape dome(52);
            dome.setPosition({bx + 68, 494});
            dome.setFillColor(shade(sf::Color(215, 218, 224), stage >= 2 ? 0.5f : 1.0f));
            window.draw(dome);
        }
        if (i == 2)
        {
            // The Hassan Square flyover crossing above the road
            sf::RectangleShape beam({300, 16});
            beam.setPosition({bx - 30, 348});
            beam.setRotation(sf::degrees(-4.0f));
            beam.setFillColor(farColor);
            window.draw(beam);
            sf::RectangleShape pillar({14, 130});
            pillar.setPosition({bx + 120, 360});
            pillar.setFillColor(farColor);
            window.draw(pillar);
        }
        if (i == 3)
        {
            // National Stadium floodlights in the distance
            for (int p = 0; p < 2; p++)
            {
                sf::RectangleShape pylon({6, 120});
                pylon.setPosition({bx + 90 + p * 90, 430});
                pylon.setFillColor(farColor);
                window.draw(pylon);
                sf::RectangleShape lights({34, 18});
                lights.setPosition({bx + 76 + p * 90, 414});
                lights.setFillColor(stage >= 2 ? sf::Color(250, 240, 190) : farColor);
                window.draw(lights);
            }
        }
    }

    // The long university boundary wall, with poster patches
    sf::RectangleShape wall({1280, 34});
    wall.setPosition({0, 585});
    wall.setFillColor(shade(sf::Color(168, 150, 122), stage >= 2 ? 0.5f : 1.0f));
    window.draw(wall);
    for (int i = 0; i < 6; i++)
    {
        float px = parallaxX(215, i, scrollX, 1.0f, 1290);
        sf::RectangleShape poster({34, 22});
        poster.setPosition({px, 591});
        poster.setFillColor(i % 2 == 0 ? sf::Color(200, 90, 70) : sf::Color(80, 130, 190));
        window.draw(poster);
    }

    // Mid layer: the university gates, one after another, each
    // with its own name board; slot 2 of the loop is the green
    // Safari Park tree line instead of a gate
    const char* gateNames[4] = {"University of Karachi", "NED University",
                                "Urdu University", "Sir Syed University"};
    int gateCount = 0;
    for (int i = 0; i < 4; i++)
    {
        float gx = parallaxX(560, i, scrollX, 0.6f, 2240);

        if (i == 2)
        {
            // Safari Park: a stretch of green in the corridor
            for (int t = 0; t < 5; t++)
            {
                sf::CircleShape tree(30);
                tree.setPosition({gx + 30 + t * 62, 520});
                tree.setFillColor(sf::Color(34, 96, 52));
                window.draw(tree);
                sf::RectangleShape trunk({7, 34});
                trunk.setPosition({gx + 57 + t * 62, 566});
                trunk.setFillColor(sf::Color(90, 66, 44));
                window.draw(trunk);
            }
            continue;
        }

        // A wide light gate: two pillars and a beam on top
        sf::Color stone = shade(sf::Color(206, 196, 172), stage >= 2 ? 0.5f : 1.0f);
        sf::RectangleShape pillar1({22, 118});
        pillar1.setPosition({gx, 470});
        pillar1.setFillColor(stone);
        window.draw(pillar1);
        sf::RectangleShape pillar2({22, 118});
        pillar2.setPosition({gx + 268, 470});
        pillar2.setFillColor(stone);
        window.draw(pillar2);
        sf::RectangleShape beamTop({312, 26});
        beamTop.setPosition({gx - 11, 448});
        beamTop.setFillColor(stone);
        window.draw(beamTop);

        drawBoard(window, gateNames[gateCount % 4], gx + 145, 461, 300, 34,
                  sf::Color(24, 70, 130), sf::Color::White, 19);
        gateCount = gateCount + 1;
    }

    drawRoad(window, scrollX, stage, sf::Color(222, 222, 222));
}
