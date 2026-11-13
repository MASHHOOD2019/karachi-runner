// Author: Mashhood Ali
#include "CliftonMap.h"

CliftonMap::CliftonMap()
    : Map("Clifton", 300, 620, 1.20f)
{
    dayTop = sf::Color(105, 165, 215);
    dayBottom = sf::Color(250, 222, 150);
    sunsetTop = sf::Color(56, 40, 92);
    sunsetBottom = sf::Color(238, 128, 62);
    nightTop = sf::Color(9, 11, 32);
    nightBottom = sf::Color(52, 50, 88);
    roadColor = sf::Color(100, 94, 88); // promenade paving grey

    addLandmark("Teen Talwar");
    addLandmark("Mohatta Palace");
    addLandmark("Dolmen Towers");
    addLandmark("Bahria Icon");
    addLandmark("Ghazi Shrine");
    addLandmark("Nishan-e-Pakistan");

    addSign("SEA VIEW");
    addSign("CLIFTON");
    addSign("DO DARYA");
}

void CliftonMap::drawBackground(sf::RenderWindow& window, float scrollX, int stage)
{
    drawSky(window, stage);

    // Far layer (slow parallax): tower blocks, the big flag pole
    // of Nishan-e-Pakistan and the three swords of Teen Talwar
    sf::Color farColor = shade(sf::Color(52, 46, 74), stage == 0 ? 1.5f : 1.0f);
    for (int i = 0; i < 4; i++)
    {
        float bx = parallaxX(430, i, scrollX, 0.3f, 1720);

        sf::RectangleShape tower({90, 190});
        tower.setPosition({bx, 395});
        tower.setFillColor(farColor);
        window.draw(tower);

        if (i == 1)
        {
            // The big flag pole with its flag
            sf::RectangleShape pole({5, 230});
            pole.setPosition({bx + 160, 355});
            pole.setFillColor(farColor);
            window.draw(pole);
            sf::RectangleShape flag({52, 30});
            flag.setPosition({bx + 165, 355});
            flag.setFillColor(sf::Color(20, 110, 60));
            window.draw(flag);
        }
        if (i == 2)
        {
            // Dolmen: twin towers behind a low mall block
            sf::RectangleShape mall({190, 60});
            mall.setPosition({bx + 130, 525});
            mall.setFillColor(farColor);
            window.draw(mall);
            sf::RectangleShape twin1({44, 200});
            twin1.setPosition({bx + 150, 385});
            twin1.setFillColor(farColor);
            window.draw(twin1);
            sf::RectangleShape twin2({44, 200});
            twin2.setPosition({bx + 215, 385});
            twin2.setFillColor(farColor);
            window.draw(twin2);
        }
        if (i == 3)
        {
            // Teen Talwar: three thin swords
            for (int s = 0; s < 3; s++)
            {
                sf::RectangleShape sword({7, 130});
                sword.setPosition({bx + 150 + s * 26, 455});
                sword.setFillColor(sf::Color(215, 215, 220));
                window.draw(sword);
            }
        }
    }

    // The Arabian Sea at Sea View, and the promenade edge
    sf::Color seaColor(60, 120, 155);
    if (stage == 0)
    {
        seaColor = sf::Color(75, 145, 175);
    }
    else if (stage >= 2)
    {
        seaColor = sf::Color(24, 48, 78);
    }
    sf::RectangleShape sea({1280, 29});
    sea.setPosition({0, 585});
    sea.setFillColor(seaColor);
    window.draw(sea);

    sf::RectangleShape glint({1280, 5});
    glint.setPosition({0, 583});
    glint.setFillColor(sf::Color(250, 200, 110));
    window.draw(glint);

    sf::RectangleShape promenade({1280, 8});
    promenade.setPosition({0, 612});
    promenade.setFillColor(sf::Color(170, 150, 120));
    window.draw(promenade);

    // Mid layer: date palms and one pink Mohatta style block
    for (int i = 0; i < 4; i++)
    {
        float px = parallaxX(430, i, scrollX, 0.6f, 1720);

        sf::RectangleShape trunk({7, 88});
        trunk.setPosition({px + 40, 524});
        trunk.setFillColor(sf::Color(90, 66, 44));
        window.draw(trunk);
        for (int f = 0; f < 5; f++)
        {
            sf::RectangleShape frond({46, 5});
            frond.setPosition({px + 43, 524});
            frond.setOrigin({0, 2});
            frond.setRotation(sf::degrees(-52.0f + f * 26.0f));
            frond.setFillColor(sf::Color(38, 110, 58));
            window.draw(frond);
        }

        if (i == 1)
        {
            // Mohatta Palace: pink stone block, three domes
            sf::RectangleShape palace({170, 74});
            palace.setPosition({px + 150, 538});
            palace.setFillColor(sf::Color(203, 130, 118));
            window.draw(palace);
            for (int d = 0; d < 3; d++)
            {
                sf::CircleShape dome(d == 1 ? 24.0f : 16.0f);
                dome.setPosition({px + 168 + d * 56 - (d == 1 ? 8.0f : 0.0f), d == 1 ? 492.0f : 500.0f});
                dome.setFillColor(sf::Color(225, 190, 140));
                window.draw(dome);
            }
        }
        if (i == 3)
        {
            // One area sign board near the promenade
            std::string sign = getSign(1); // CLIFTON
            drawBoard(window, sign, px + 230, 520, 170, 44,
                      sf::Color(18, 92, 52), sf::Color::White, 22);
        }
    }

    drawRoad(window, scrollX, stage, sf::Color(215, 205, 185));
}
