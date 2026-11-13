// Author: Mashhood Ali
#include "BiryaniBox.h"

BiryaniBox::BiryaniBox(float startX, float startY)
    : GameObject(startX, startY), Collectible(startX, startY, 36, 30)
{
}

void BiryaniBox::draw(sf::RenderWindow& window)
{
    // A takeaway box: white body, red lid stripe, yellow rice top
    sf::RectangleShape box({36, 22});
    box.setPosition({x, y + 8});
    box.setFillColor(sf::Color(245, 245, 240));
    window.draw(box);

    sf::RectangleShape lid({36, 8});
    lid.setPosition({x, y + 2});
    lid.setFillColor(sf::Color(200, 45, 45));
    window.draw(lid);

    sf::RectangleShape rice({26, 6});
    rice.setPosition({x + 5, y + 12});
    rice.setFillColor(sf::Color(250, 190, 60));
    window.draw(rice);
}

void BiryaniBox::apply(Player& player, Score& score)
{
    (void)player;
    score.add(50, "Biryani bonus");
}
