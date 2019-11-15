#include "finalgameinfo.h"

#include "garbagecollector.h"
#include "chrono.h"

#include "resourcemanager.h"

#include "finalkernel.h"
#include "finalsceneloader.h"

FinalGameInfo::FinalGameInfo(const sf::Vector2i& size, std::string title)
    :GameInfo(size, title)
{
    //! NOTE: USER KERNEL must be created here in order to be at the right time
    kernel_ = new FinalKernel();
}

FinalGameInfo::~FinalGameInfo(){

}

void FinalGameInfo::on_init(){
    // init the garbage collector
    scene_loader = add_component<FinalSceneLoader>();

    // init the resource manager
	add_component<gdf::temporal::Chrono>();
	add_component<ResourceManager>();

    GarbageCollector* global_gc = add_component<GarbageCollector>();
    global_gc->bind(&gdf::kernel::Scene::global_go_junkyard_, &gdf::kernel::Scene::global_c_junkyard_ );

    //!
    this->setKeyRepeatEnabled(false);

    // define viewports
    // Should be also in pixel

    GameInfo::game_info->add_viewport( sf::FloatRect(0.0, 0.0, 1, 1) );
    GameInfo::game_info->add_viewport( sf::FloatRect(0.70, 0.70, 0.25, 0.25) );

}

void FinalGameInfo::on_event(const sf::Event &event){
    if( event.type == sf::Event::Closed ){
        std::cout << FGREEN << BOLD << "FinalGameInfo: You shall pass ! " << RESET << std::endl;

        gdf::kernel::GameInfo::game_info.get()->close();
//        gdf::kernel::GameInfo::game_info.get()->scenes()[0]->root().reset();
    }
}
