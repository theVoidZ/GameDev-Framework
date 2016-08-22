#include "gameinfo.h"

#include "kernel/scene.h"

#include "kernel/component.h"

namespace gdf {
namespace kernel{

//Initializing static members
//////////////////////////////////////////////////////////////////////////////////////////////////////////
const sf::Time GameInfo::delta_time = sf::seconds( 1 / 30.0f );
std::unique_ptr<GameInfo> GameInfo::game_info(nullptr);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameInfo::GameInfo(const sf::Vector2i& size, std::string title)
    : sf::RenderWindow( sf::VideoMode( size.x, size.y) , title )
{

    // Defines a set of rules within classes ( Component requirements )
    new KernelRules();
    KernelRules::kernel->init();
    KernelRules::kernel->show_rules();

    //Create the GameInfo singleton,( remove eventual previous instance when a new one is created )
    if( game_info.get() == nullptr ){
        game_info.reset(this);
    }else{
        if( game_info.get() != this ){
            game_info.reset(this);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameInfo::~GameInfo(){
    // Destroy the Core Components

    // Destroy the scenes
    for( auto it = scenes_.begin(); it != scenes_.end(); ){
        delete (*it).second;
        it = scenes_.erase(it);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
int GameInfo::add_scene(Scene *scene, std::string name, bool is_daemon){
    static int scene_id = -1;
    if( scene != nullptr ){
        scene_id ++;
        scene->is_daemon_ = is_daemon;
        scene->name_ = name;
        scenes_[scene_id] = scene;
        return scene_id;
    }else{
        return -1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::init(){
    // GameInfo specific's init, used when overriding this class
    on_init();

    // Core Components init
    foreach (Component* ccomp, all_items) {
        ccomp->init();
    }

    // Scenes init
    std::map<unsigned int, Scene*>::iterator it;
    // All scenes are inited, whether they are daemons or not.
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr )
            (*it).second->init();
    }

    // All scenes are post_inited, whether they are daemons or not.
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr )
            (*it).second->post_init();
    }

    // reset clock ( clock )
    clock.restart();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::gameloop(){
    // Get elapsed time for the gameloop elementary cycle
    sf::Time elapsed_time = clock.restart();

    // While the amount of time is not consumed
    while( elapsed_time  > sf::Time::Zero ){

        // Whether performs an update with a protion time of delta_time or delta_time. But never superior.
        sf::Time next_update_time_portion = ( elapsed_time > delta_time )
                                            ? delta_time : elapsed_time;

        //Consumes a portion of time equal to delta_time
        elapsed_time -= delta_time;

        // Event handling
        handle_events();

        // Normal update + daemon
        update(next_update_time_portion);

        // Fixed update + daemon
        fixed_update(next_update_time_portion);

        // Late update + demon
        late_update(next_update_time_portion);
    }

    // Draw
    render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::handle_events(){
    sf::Event event;

    while( this->pollEvent(event) ){

        on_event(event);

        // Transfer captured events to the active scene only
        if( active_scene_ != nullptr ){
            active_scene_->handle_events(event);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::update(sf::Time dt){
    // Update self-components
    foreach (Component* ccomp, all_items) {
        ccomp->update(dt);
    }

    // Updates the active scene firstly
    if( active_scene_ != nullptr && active_scene_->is_loaded() ){
        active_scene_->update(dt);
    }

    // Update daemon scenes
    std::map< unsigned int, Scene*>::iterator it;
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr && (*it).second != active_scene_ && (*it).second->is_daemon() == true && (*it).second->is_loaded() ){
            (*it).second->update(dt);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::fixed_update(sf::Time dt){
    // Updates the physics of the active scene firstly
    if( active_scene_ != nullptr && active_scene_->is_loaded() ){
        active_scene_->fixed_update(dt);
    }

    // Update the physics of daemon scenes
    std::map<unsigned int, Scene*>::iterator it;
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr && (*it).second != active_scene_ && (*it).second->is_daemon() == true && (*it).second->is_loaded() ){
            (*it).second->fixed_update(dt);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::late_update(sf::Time dt){
    // Late update the active scene firstly
    if( active_scene_ != nullptr && active_scene_->is_loaded() ){
        active_scene_->late_update(dt);
    }

    // Late update the daemon scenes
    std::map<unsigned int, Scene*>::iterator it;
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr && (*it).second != active_scene_ && (*it).second->is_daemon() ){
            (*it).second->late_update(dt);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::render(){
    // Draw is applied only to the active scene
    if( active_scene_ == nullptr ){
        // In case there is no active scene, display back screen
        this->clear( sf::Color::Black );
        this->display();
        return;
    }

    // Clear the screen
    this->clear( active_scene_->clear_color() );

    // Draw the scene
    active_scene_->render();

    // Switching to the defaultView. ( Screen )
    this->setView( this->getDefaultView() );

    // Draw the GUI/HUD
    active_scene_->render_gui();

    // Display
    this->display();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::set_active_scene(unsigned int scene_id){
    std::map<unsigned int, Scene*>::iterator it;

    it = scenes_.find(scene_id);
    if( it != scenes_.end() ){
        active_scene_ = (*it).second;
    }else{
        std::cout << FORANGE << BOLD << "GameInfo::set_active_scene" << RESET_BOLD << " - Invalid scene id " << RESET << std::endl;
        active_scene_ = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::set_active_scene(std::string scene_name){
    std::map<unsigned int, Scene*>::iterator it;

    for(it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second->name() == scene_name ){
            active_scene_ = (*it).second;
            return;
        }
    }

    std::cout << FORANGE << BOLD << "GameInfo::set_active_scene" << RESET_BOLD << " - Invalid scene id " << RESET << std::endl;
    active_scene_ = nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map<unsigned int, Scene*>& GameInfo::scenes(){
    return scenes_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene* GameInfo::active_scene() const{
    if( active_scene_ == nullptr ){
        return nullptr;
    }

    return active_scene_;
}

}}
