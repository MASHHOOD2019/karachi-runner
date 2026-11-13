// Author: Mashhood Ali
#include "ScoreManager.h"
#include "ScoreMapper.h"
#include "FileLoadException.h"
#include <fstream>

ScoreManager::ScoreManager()
{
    savedCount = 0;
    fileName = "highscore.txt";
}

void ScoreManager::setFileName(std::string name)
{
    fileName = name;
}

void ScoreManager::insertSorted(std::string name, Score s)
{
    // Find where this score belongs, highest points first
    int pos = savedCount;
    while (pos > 0 && topScores[pos - 1].getPoints() < s.getPoints())
    {
        pos = pos - 1;
    }
    if (pos >= 5)
    {
        return; // below the whole board, nothing to insert
    }

    int last = savedCount;
    if (last > 4)
    {
        last = 4;
    }
    for (int i = last; i > pos; i--)
    {
        topScores[i] = topScores[i - 1];
        topNames[i] = topNames[i - 1];
    }
    topScores[pos] = s;
    topNames[pos] = name;
    if (savedCount < 5)
    {
        savedCount = savedCount + 1;
    }
}

void ScoreManager::loadScores()
{
    savedCount = 0;

    std::ifstream inFile(fileName);
    if (!inFile)
    {
        // Create: no file yet, so make an empty one and start fresh
        std::ofstream createFile(fileName);
        return;
    }

    ScoreMapper mapper;
    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.length() == 0)
        {
            continue;
        }
        std::string name;
        Score s = mapper.fromLine(line, name);
        if (name.length() > 0)
        {
            insertSorted(name, s);
        }
    }
}

void ScoreManager::saveScores()
{
    std::ofstream outFile(fileName);
    if (!outFile)
    {
        throw FileLoadException(fileName);
    }

    ScoreMapper mapper;
    for (int i = 0; i < savedCount; i++)
    {
        outFile << mapper.toLine(topNames[i], topScores[i]) << "\n";
    }
}

bool ScoreManager::qualifies(int points)
{
    if (points <= 0)
    {
        return false;
    }
    if (savedCount < 5)
    {
        return true;
    }
    return points > topScores[4].getPoints();
}

void ScoreManager::addScore(std::string name, Score s)
{
    if (!qualifies(s.getPoints()))
    {
        return;
    }
    insertSorted(name, s);
    saveScores();
}

void ScoreManager::resetScores()
{
    // Delete: the board is cleared and the file is emptied
    savedCount = 0;
    std::ofstream outFile(fileName);
    if (!outFile)
    {
        throw FileLoadException(fileName);
    }
}

Score ScoreManager::getTopScore(int i)
{
    if (i < 0 || i >= savedCount)
    {
        return Score();
    }
    return topScores[i];
}

std::string ScoreManager::getTopName(int i)
{
    if (i < 0 || i >= savedCount)
    {
        return "";
    }
    return topNames[i];
}

int ScoreManager::getSavedCount()
{
    return savedCount;
}
