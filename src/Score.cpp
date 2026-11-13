// Author: Mashhood Ali
#include "Score.h"

Score::Score()
{
    points = 0;
    coins = 0;
    distance = 0;
    lastBonusReason = "";
}

void Score::add(int p)
{
    points = points + p;
}

void Score::add(int p, std::string reason)
{
    // Overloaded version: same name, extra information (Week 9)
    points = points + p;
    lastBonusReason = reason;
}

void Score::addCoin()
{
    coins = coins + 1;
}

void Score::setDistance(int d)
{
    if (d < 0)
    {
        d = 0;
    }
    distance = d;
}

std::string Score::getLastBonusReason()
{
    return lastBonusReason;
}

void Score::setPoints(int p)
{
    if (p < 0)
    {
        p = 0;
    }
    points = p;
}

void Score::setCoins(int c)
{
    if (c < 0)
    {
        c = 0;
    }
    coins = c;
}

Score Score::operator+(const Score& other)
{
    Score total;
    total.points = points + other.points;
    total.coins = coins + other.coins;
    total.distance = distance + other.distance;
    return total;
}

std::ostream& operator<<(std::ostream& out, const Score& s)
{
    // A friend function, so it can read the private data (Week 6)
    out << "Points: " << s.points << "  Coins: " << s.coins
        << "  Distance: " << s.distance << " m";
    return out;
}
