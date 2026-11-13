// Author: Mashhood Ali
#include "Bus.h"

// Tall and long: 240 x 120, top at 620 - 120.
Bus::Bus(float startX)
    : GameObject(startX, 620 - 120), Obstacle(startX, 620 - 120, 1, 240, 120)
{
}

void Bus::draw(sf::RenderWindow& window)
{
    // Truck art colours: teal body, red and yellow bands, a row
    // of windows. Placeholder shapes until the art phase.
    sf::RectangleShape body({240, 96});
    body.setPosition({x, y + 10});
    body.setFillColor(sf::Color(20, 130, 140));
    window.draw(body);

    sf::RectangleShape band({240, 14});
    band.setPosition({x, y + 78});
    band.setFillColor(sf::Color(200, 45, 45));
    window.draw(band);

    sf::RectangleShape bandTop({240, 8});
    bandTop.setPosition({x, y + 10});
    bandTop.setFillColor(sf::Color(245, 200, 40));
    window.draw(bandTop);

    for (int i = 0; i < 4; i++)
    {
        sf::RectangleShape win({30, 26});
        win.setPosition({x + 14 + i * 44, y + 26});
        win.setFillColor(sf::Color(190, 225, 235));
        window.draw(win);
    }

    // The back panel at the rear of the bus, in truck art style:
    // a decorated border of nested colours, the way real Karachi
    // buses carry a painted panel on their backs. This is the
    // bus-back dedication design placement of blueprint 6.3.
    sf::RectangleShape panelOuter({40, 62});
    panelOuter.setPosition({x + 192, y + 18});
    panelOuter.setFillColor(sf::Color(245, 200, 40));
    window.draw(panelOuter);

    sf::RectangleShape panelMid({32, 54});
    panelMid.setPosition({x + 196, y + 22});
    panelMid.setFillColor(sf::Color(200, 45, 45));
    window.draw(panelMid);

    sf::RectangleShape panelInner({24, 46});
    panelInner.setPosition({x + 200, y + 26});
    panelInner.setFillColor(sf::Color(246, 238, 214));
    window.draw(panelInner);

    sf::RectangleShape panelDot({10, 10});
    panelDot.setPosition({x + 207, y + 44});
    panelDot.setFillColor(sf::Color(30, 130, 80));
    window.draw(panelDot);

    sf::CircleShape wheelBack(15);
    wheelBack.setPosition({x + 28, y + 92});
    wheelBack.setFillColor(sf::Color(25, 25, 25));
    window.draw(wheelBack);

    sf::CircleShape wheelFront(15);
    wheelFront.setPosition({x + 192, y + 92});
    wheelFront.setFillColor(sf::Color(25, 25, 25));
    window.draw(wheelFront);
}

std::string Bus::getKind()
{
    return "Bus";
}
