#include "gameinfo.h"

#include "scene.h"

#include "component.h"
#include "camera.h"

#include "sceneloaderbase.h"

#include "componentfactory.h"
#include "gameobject.h"


namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Viewport::Viewport(sf::FloatRect r) : rect(r), enabled(false)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Viewport::is_assigned() const{
    return ( !camera.expired() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene* Viewport::get_camera_scene(){
    if( !camera.expired() ){
	    GameObject* cam_go = nullptr;
	    if( (cam_go = dynamic_cast<gdf::kernel::GameObject*>( camera.get()->host_object<gdf::kernel::GameObject>() )) != nullptr ){
		    if( cam_go->scene() != nullptr ){
			    return cam_go->scene();
		    }
	    }
    }

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//Initializing static members
//////////////////////////////////////////////////////////////////////////////////////////////////////////
const sf::Time GameInfo::delta_time = sf::seconds( 1 / 33.0f );
std::unique_ptr<GameInfo> GameInfo::game_info(nullptr);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameInfo::GameInfo(const sf::Vector2i& size, std::string title)
    : sf::RenderWindow( sf::VideoMode( size.x, size.y) , title )
{
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
int GameInfo::add_scene(std::string name, bool is_active){
    static int scene_id = -1;
    Scene* scene = new Scene();
    scene_id ++;
    scene->ref_count_ = 0;
    scene->name_ = name;
    scene->is_active_ = is_active;

    //! LINK: Pushing a Scene to Scene's vector
    scenes_[scene_id] = scene;
    return scene_id;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::add_viewport(sf::FloatRect r){
    //! LINK: Pushing a Viewport to Viewport vector
    viewports_.push_back( new Viewport(r) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::bind(int viewport_index, tracker_ptr<Camera> camera){
    //! FIXME: camera is Component but cannot retrieve scene for sf::View, this is why scene is also passed as parameter to be removed if it would be possible.
    if( viewport_index < viewports_.size() && viewport_index >= 0 ){

        if( !camera.expired() ){
            Scene* sc = nullptr;

            GameObject* cam_go = camera.get()->game_object();
            if( cam_go->scene() != nullptr ){
                sc= cam_go->scene();
            }

            if( sc != nullptr ){
                //Valid camera is going to be added.

                // Unbind already bound viewport.
                if( viewports_[viewport_index]->is_assigned() ){
                    unbind( viewport_index );
                }

                viewports_[viewport_index]->camera = camera;
                viewports_[viewport_index]->enabled = true;
                sc->ref_count_ ++ ;
//            viewports_[viewport_index]->view->setViewport( viewports_[viewport_index]->rect );
            }
        }

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::unbind(int viewport_index){
    if( viewport_index < viewports_.size() && viewport_index >= 0 ){
        if( viewports_[viewport_index]->is_assigned() ){
            Scene* sc = viewports_ [viewport_index]->get_camera_scene();

            if( sc != nullptr ){
                viewports_[viewport_index]->camera.release();
                viewports_[viewport_index]->enabled = false;
                sc->ref_count_--;
            }
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::init(){
    this->setVerticalSyncEnabled(true);

    this->setTitle("ImGui test");
    this->resetGLStates();

    // Init kernel
    if( kernel_ == nullptr ){
        // force init kernel with default one if not.
        kernel_ = new KernelRules();
    }
    kernel_->init();
    kernel_->show_rules();


    // Init ComponentFactory
    component_factory_ = new ComponentFactory();

    // GameInfo specific's init, used by overriding this class ( force init on SceneLoader default when no class is specified )
    // Add Components, scenes , set data here.
    on_init();

    // Add/init the scene loader.
    if( scene_loader == nullptr )
        scene_loader = add_component<SceneLoaderBase>();

    // GameInfo Components init
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->init();
        }
    }

    // Scenes init
    std::map<unsigned int, Scene*>::iterator it;
    // All scenes are inited - Component are inited here
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr )
            (*it).second->init();
    }

    // All scenes are post_inited
    // Some components requires/ must be inited after others, so have to be inited during the second phase
    for( it=scenes_.begin(); it!=scenes_.end(); it++ ){
        if( (*it).second != nullptr )
            (*it).second->post_init();
    }

    // reset clock ( Start the TIMER )
    clock.restart();
}

void GameInfo::on_init(){
    // For overriden object
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

//        next_update_time_portion = next_update_time_portion * 0.2f;
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

        // Handle events of active scenes only
        for( auto it : scenes_ ){
            if( it.second != nullptr && it.second->is_loaded() ){
                if( it.second->is_active() ){ // daemon not involved
                    it.second->handle_events(event);
                }
            }
        }

    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::on_event(const sf::Event &event){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::update(sf::Time dt){
    // Update self-components
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->update(dt);
        }
    }

    // Update scenes
    // Handle events of active scenes only
    for( auto it : scenes_ ){
        if( it.second != nullptr && it.second->is_loaded() && it.second->is_active() ){
            it.second->update(dt);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::fixed_update(sf::Time dt){
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->fixed_update(dt);
        }
    }

    // Update the physics of scenes
    for( auto it : scenes_ ){
        if( it.second != nullptr && it.second->is_loaded() && it.second->is_active() ){
            it.second->fixed_update(dt);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::late_update(sf::Time dt){
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->late_update(dt);
        }
    }


    // Late update the scenes
    for( auto it : scenes_ ){
        if( it.second != nullptr && it.second->is_loaded() && it.second->is_active() ){
            it.second->late_update(dt);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInfo::render(){
    // Clear the screen
    this->clear( clear_color );


    for( Viewport* v : viewports_ ){
        if( v->enabled ){
            if( v->is_assigned() && v->get_camera_scene()->is_active() ){
                //! FIX: Temporarly disabled
                this->setView( *( dynamic_cast<sf::View*>(v->camera.get()) ) );
                v->camera.get()->set_viewport( v->rect );
                v->get_camera_scene()->draw();
            }
        }
    }

    // Render GUI
    //! FIXME:
    this->setView( this->getDefaultView() );

    for( Viewport* v : viewports_ ){
        if( v->enabled ){
            if( v->is_assigned() ){
                v->get_camera_scene()->draw_gui();
            }
        }
    }


    // Display
    this->display();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GETTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector< Viewport* >& GameInfo::viewports(){
    return viewports_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
KernelRules* GameInfo::kernel(){
    return kernel_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentFactory* GameInfo::component_factory(){
    return component_factory_;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map<unsigned int, Scene*>& GameInfo::scenes(){
    return scenes_;
}

}}
