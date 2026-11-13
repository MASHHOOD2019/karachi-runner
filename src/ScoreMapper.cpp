// Author: Mashhood Ali
#include "ScoreMapper.h"
#include <sstream>

std::string ScoreMapper::toLine(std::string name, Score s)
{
    std::stringstream stream;
    stream << name << "|" << s.getPoints() << "|" << s.getCoins()
           << "|" << s.getDistance();
    return stream.str();
}

Score ScoreMapper::fromLine(std::string line, std::string& nameOut)
{
    Score s;
    nameOut = "";

    // Split the line on the | characters, by hand
    std::string parts[4];
    int partCount = 0;
    std::string current = "";
    for (std::size_t i = 0; i < line.length() && partCount < 4; i++)
    {
        if (line[i] == '|')
        {
            parts[partCount] = current;
            partCount = partCount + 1;
            current = "";
        }
        else
        {
            current = current + line[i];
        }
    }
    if (partCount < 4)
    {
        parts[partCount] = current;
        partCount = partCount + 1;
    }

    if (partCount != 4)
    {
        return s; // a damaged line gives an empty score and no name
    }

    nameOut = parts[0];
    try
    {
        s.setPoints(std::stoi(parts[1]));
        s.setCoins(std::stoi(parts[2]));
        s.setDistance(std::stoi(parts[3]));
    }
    catch (...)
    {
        nameOut = "";
        return Score();
    }
    return s;
}
