// Author: Mashhood Ali
#include <iostream>
#include "Game.h"
#include "FileLoadException.h"

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (FileLoadException& e)
    {
        std::cout << "A file could not be loaded: " << e.getMessage() << std::endl;
        std::cout << "Check that the assets folder is next to the game." << std::endl;
        return 1;
    }
    return 0;
}
