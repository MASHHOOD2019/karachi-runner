// Author: Mashhood Ali
#include "ShahrahMap.h"
#include <cmath>

ShahrahMap::ShahrahMap()
    : Map("Shahrah-e-Faisal", 320, 620, 1.10f)
{
    dayTop = sf::Color(100, 155, 205);
    dayBottom = sf::Color(245, 215, 145);
    sunsetTop = sf::Color(50, 36, 88);
    sunsetBottom = sf::Color(232, 120, 58);
    nightTop = sf::Color(8, 10, 30);
    nightBottom = sf::Color(48, 46, 84);
    roadColor = sf::Color(45, 43, 52); // dark multi lane asphalt

    addLandmark("FTC Building");
    addLandmark("Pedestrian Bridge");
    addLandmark("Nursery Furniture");
    addLandmark("Karsaz");
    addLandmark("Star Gate");

    addSign("SHAHRAH-E-FAISAL");
    addSign("AIRPORT");
    addSign("NURSERY");
    addSign("FTC");
}

void ShahrahMap::drawBackground(sf::RenderWindow& window, float scrollX, int stage)
{
    drawSky(window, stage);

    // Far layer: office slabs, and the FTC brick block at slot 1
    sf::Color farColor = shade(sf::Color(56, 48, 76), stage == 0 ? 1.5f : 1.0f);
    for (int i = 0; i < 4; i++)
    {
        float bx = parallaxX(430, i, scrollX, 0.3f, 1720);

        sf::RectangleShape slab({150, 150});
        slab.setPosition({bx, 435});
        slab.setFillColor(farColor);
        window.draw(slab);

        if (i == 1)
        {
            // FTC: one big reddish brown block with its letters
            sf::RectangleShape ftc({210, 180});
            ftc.setPosition({bx + 170, 405});
            ftc.setFillColor(sf::Color(146, 84, 62));
            window.draw(ftc);
            for (int r = 0; r < 4; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    sf::RectangleShape win({20, 14});
                    win.setPosition({bx + 186.0f + c * 38.0f, 452.0f + r * 32.0f});
                    win.setFillColor(sf::Color(214, 190, 150));
                    window.draw(win);
                }
            }
            drawTextCenter(window, "FTC", bx + 275, 428, 26, sf::Color::White);
        }
    }

    // Street level strip behind the road
    sf::RectangleShape verge({1280, 37});
    verge.setPosition({0, 585});
    verge.setFillColor(shade(sf::Color(70, 66, 74), stage >= 2 ? 0.55f : 1.0f));
    window.draw(verge);

    // Mid layer: the overhead gantry with the green board, then
    // a pedestrian bridge with ad panels
    float gantryX = parallaxX(2100, 0, scrollX, 0.6f, 2100);
    if (gantryX > -620 && gantryX < 1300)
    {
        sf::RectangleShape post1({10, 300});
        post1.setPosition({gantryX, 285});
        post1.setFillColor(sf::Color(90, 90, 96));
        window.draw(post1);
        sf::RectangleShape post2({10, 300});
        post2.setPosition({gantryX + 560, 285});
        post2.setFillColor(sf::Color(90, 90, 96));
        window.draw(post2);

        // Pakistan road sign style: deep green, white text
        sf::RectangleShape gantry({580, 84});
        gantry.setPosition({gantryX - 5, 268});
        gantry.setFillColor(sf::Color(14, 96, 50));
        window.draw(gantry);
        drawTextCenter(window, "Shahrah-e-Faisal", gantryX + 285, 292, 28, sf::Color::White);
        drawTextCenter(window, "Airport  ->", gantryX + 285, 330, 20, sf::Color::White);
    }

    float bridgeX = parallaxX(2100, 1, scrollX, 0.6f, 2100);
    if (bridgeX > -640 && bridgeX < 1300)
    {
        sf::RectangleShape leg1({12, 180});
        leg1.setPosition({bridgeX, 405});
        leg1.setFillColor(sf::Color(96, 96, 102));
        window.draw(leg1);
        sf::RectangleShape leg2({12, 180});
        leg2.setPosition({bridgeX + 600, 405});
        leg2.setFillColor(sf::Color(96, 96, 102));
        window.draw(leg2);

        // The bridge deck, its side covered with ad panels
        sf::RectangleShape deck({624, 46});
        deck.setPosition({bridgeX - 6, 380});
        deck.setFillColor(sf::Color(110, 108, 116));
        window.draw(deck);
        drawBoard(window, "SUPER TEA", bridgeX + 105, 403, 190, 38,
                  sf::Color(178, 34, 44), sf::Color::White, 18);
        drawBoard(window, "CITY HOMES", bridgeX + 305, 403, 190, 38,
                  sf::Color(30, 80, 150), sf::Color::White, 18);
        drawBoard(window, "4G MOBILE", bridgeX + 505, 403, 190, 38,
                  sf::Color(240, 170, 30), sf::Color(40, 32, 20), 18);
    }

    // Near layer: ONE billboard panel for sir (blueprint 6.2).
    // This is dedication appearance 1 of the maximum 4 in the
    // whole game world, and it exists only on this map.
    float boardX = parallaxX(2800, 0, scrollX, 0.85f, 2800);
    if (boardX > -420 && boardX < 1300)
    {
        sf::RectangleShape pole({12, 190});
        pole.setPosition({boardX + 165, 395});
        pole.setFillColor(sf::Color(80, 80, 86));
        window.draw(pole);

        sf::RectangleShape panel({350, 124});
        panel.setPosition({boardX, 282});
        panel.setFillColor(sf::Color(26, 44, 110));
        window.draw(panel);
        sf::RectangleShape frame({334, 108});
        frame.setPosition({boardX + 8, 290});
        frame.setFillColor(sf::Color(26, 44, 110));
        frame.setOutlineColor(sf::Color(245, 200, 40));
        frame.setOutlineThickness(3);
        window.draw(frame);

        drawTextCenter(window, "Thank You Sir", boardX + 175, 322, 30, sf::Color::White);
        drawTextCenter(window, "Faisal Feroze", boardX + 175, 362, 30, sf::Color(245, 200, 40));
    }

    drawRoad(window, scrollX, stage, sf::Color(225, 225, 225));

    // The second lane line of the multi lane road
    float dashScroll = std::fmod(scrollX, 90.0f);
    for (int i = 0; i < 15; i++)
    {
        sf::RectangleShape dash({46, 4});
        dash.setPosition({i * 90.0f - dashScroll, 700});
        dash.setFillColor(sf::Color(200, 200, 200));
        window.draw(dash);
    }
}
