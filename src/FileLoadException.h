// Author: Mashhood Ali
#ifndef FILELOADEXCEPTION_H
#define FILELOADEXCEPTION_H

#include <string>

// Custom exception (Week 7-8). Thrown when a game file fails to load.
// It carries the file name so the catch block can tell the user
// exactly which file is missing.
class FileLoadException
{
private:
    std::string fileName;
    std::string message;

public:
    FileLoadException(std::string name);
    std::string getFileName();
    std::string getMessage();
};

#endif
