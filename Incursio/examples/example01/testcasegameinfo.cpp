#include "testcasegameinfo.h"

// include of the Custom Scene
#include "example/testcasescene.h"


TestCaseGameInfo::TestCaseGameInfo(const sf::Vector2i& size, std::string title)
    :GameInfo(size, title)
{

}

TestCaseGameInfo::~TestCaseGameInfo(){

}

void TestCaseGameInfo::on_init(){

    add_scene( new TestCaseScene(), "CTSpawn", false);
//    add_scene( new TestCaseScene(), "TSpawn", false);
//    add_scene( new TestCaseScene(), "DoubleDoors", false);

//    set_active_scene( "CTSawn" );
    set_active_scene( 0 );


}

void TestCaseGameInfo::on_event(const sf::Event &event){
    if( event.type == sf::Event::Closed ){
        std::cout << FRED << BOLD << "You shall not pass ! " << RESET << std::endl;
        gdf::kernel::GameInfo::game_info.get()->close();
    }
}
