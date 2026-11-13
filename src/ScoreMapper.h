// Author: Mashhood Ali
#ifndef SCOREMAPPER_H
#define SCOREMAPPER_H

#include <string>
#include "Score.h"

// The Mapper class (Week 16 serialization). It converts a Score
// object into one line of text for the file, and converts a line
// back into a Score object. Line format: name|points|coins|distance
// ScoreManager never builds file lines by hand; it always uses this.
class ScoreMapper
{
public:
    std::string toLine(std::string name, Score s);
    Score fromLine(std::string line, std::string& nameOut);
};

#endif
