#include "example/testcasegameinfo.h"

#define screen_width 640
#define screen_height 480

int main(int argc, char *argv[])
{

    TestCaseGameInfo* game_info = new TestCaseGameInfo(sf::Vector2i(screen_width, screen_height), "SFML" );

    game_info->init();
    while( game_info->isOpen() ){
        game_info->gameloop();
    }

    return EXIT_SUCCESS;

}
