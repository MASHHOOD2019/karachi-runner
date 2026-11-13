// Author: Mashhood Ali
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>
#include "Score.h"

// Owns the Top 5 leaderboard and the highscore.txt file
// (Week 15 file handling with full CRUD, Week 3 arrays of objects,
// Week 16: every line goes through ScoreMapper).
// Create: the file is made if it does not exist.
// Read: the Top 5 is loaded at game start.
// Update: a new qualifying score is inserted and the file rewritten.
// Delete: resetScores() clears the board and the file.
class ScoreManager
{
private:
    Score topScores[5];
    std::string topNames[5];
    int savedCount;
    std::string fileName;

    void insertSorted(std::string name, Score s);

public:
    ScoreManager();

    void setFileName(std::string name);
    void loadScores();
    void saveScores();
    bool qualifies(int points);
    void addScore(std::string name, Score s);
    void resetScores();

    Score getTopScore(int i);
    std::string getTopName(int i);
    int getSavedCount();
};

#endif
