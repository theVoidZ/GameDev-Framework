#include <SFML/Graphics.hpp>

#include <list>
#include "finalgameinfo.h"

#include <memory>
#include <fstream>
#include <iostream>
#include <Box2D/Box2D.h>

#define screen_width 1920
#define screen_height 1080

#include "terminal_colors.h"

#define classname(x) #x

int main(int argc, char *argv[])
{

    std::cout << RESET << std::endl;

    GameInfo* window = new FinalGameInfo(sf::Vector2i(screen_width, screen_height), "SFML" );


    window->init();

    while( window->isOpen() ){
        window->gameloop();
    }


    return EXIT_SUCCESS;

}

