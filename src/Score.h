// Author: Mashhood Ali
#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>

// One run's score as a proper object (Week 2 encapsulation,
// Week 9 function overloading and operator overloading,
// Week 6 friend). No loose global score variables anywhere.
class Score
{
private:
    int points;
    int coins;
    int distance;
    std::string lastBonusReason;

public:
    Score();

    void add(int p);
    void add(int p, std::string reason);
    void addCoin();
    void setDistance(int d);

    inline int getPoints() { return points; }
    inline int getCoins() { return coins; }
    inline int getDistance() { return distance; }
    std::string getLastBonusReason();

    void setPoints(int p);
    void setCoins(int c);

    Score operator+(const Score& other);
    friend std::ostream& operator<<(std::ostream& out, const Score& s);
};

#endif
