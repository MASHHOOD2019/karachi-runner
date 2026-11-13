// Author: Mashhood Ali
#include "FileLoadException.h"

FileLoadException::FileLoadException(std::string name)
{
    fileName = name;
    message = "Could not load file: " + name;
}

std::string FileLoadException::getFileName()
{
    return fileName;
}

std::string FileLoadException::getMessage()
{
    return message;
}
