#include "scene.h"
#include "kernel/gameinfo.h"

#include "kernel/gameobject.h"
#include "Core/System/camera.h"
#include "Core/System/monobehavior.h"

#include "kernel/component.h"

namespace gdf {
namespace kernel{

std::map<Object*, sf::Time> Scene::global_junkyard_;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::~Scene(){
    // Destroy Core Components

    // Destroy the hierarchy
    delete root_;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::init(){
    //Creating the root item to build the hierarchy.
    root_ = new GameObject();

    // Binds the scene and the root object
    root_->scene_ = this; // to be changed

    // Init the specific properties of the scene - used on overridden scenes
    on_init();

    // Init the Component declared in 'on_init'
    foreach (Component* ccomp, all_items) {
        ccomp->init();
    }

    // Loading resources
    load_resources();

}

void Scene::post_init(){

    build();

    // Init the Root, gameobjects and all their components ( must be called after build
    root_->init();

    // Mark the scene as Loaded
    is_loaded_ = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::handle_events(const sf::Event &event){
    // handle scene events
    on_event(event);

    // Passes events handling to the GameObjects Component ( MonoBehavior )
    // Windows events
    if( event.type == sf::Event::Closed ){ // data = (none)
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onClosed
            mb->on_closed(event);
        }
    }else if( event.type == sf::Event::Resized ){ // data = event.size
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onResized
            mb->on_resized(event);
        }
    }else if( event.type == sf::Event::GainedFocus ){ // data = (none)
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onGainedFocus
            mb->on_gained_focus(event);
        }
    }else if( event.type == sf::Event::LostFocus ){ // data = (none)
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onLostFocus
            mb->on_lost_focus(event);
        }

    }else if( event.type == sf::Event::MouseEntered ){ // data = (none)
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onMouseEntered
            mb->on_mouse_entered(event);
        }

    }else if( event.type == sf::Event::MouseLeft ){ // data = (none)
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onMouseLeft
            mb->on_mouse_left(event);
        }

    // Mouse events
    }else if( event.type == sf::Event::MouseButtonPressed ){ // data = event.mouseButton
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {

            //! CLBK: onMousePressed
            mb->on_mouse_button_pressed(event);
        }

    }else if( event.type == sf::Event::MouseButtonReleased ){ // data = event.mouseButton
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onMouseReleased
            mb->on_mouse_button_released(event);
        }

    }else if( event.type == sf::Event::MouseMoved ){ // data = event.mouseMove
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onMouseMove
            mb->on_mouse_moved(event);
        }

    }else if( event.type == sf::Event::MouseWheelMoved ){ // data = event.mouseWheel
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onMouseWheelMoved
            mb->on_mouse_wheel_moved(event);
        }

    // Keyboard events
    }else if( event.type == sf::Event::KeyPressed ){ // data = event.key
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onKeyPressed
            mb->on_key_pressed(event);
        }

    }else if( event.type == sf::Event::KeyReleased ){ // data = event.key
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onKeyReleased
            mb->on_key_released(event);
        }

    }else if( event.type == sf::Event::TextEntered ){ // data = event.text
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onTextEntered
            mb->on_text_entered(event);
        }

    // Joystick events
    }else if( event.type == sf::Event::JoystickButtonPressed ){ // data = event.joystickButton
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onJoystickButtonPressed
            mb->on_joystick_button_pressed(event);
        }

    }else if( event.type == sf::Event::JoystickButtonReleased ){ // data = event.joystickButton
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onJoystickButtonReleased
            mb->on_joystick_button_released(event);
        }

    }else if( event.type == sf::Event::JoystickMoved ){ // data = event.joystickMove
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onJoystickMoved
            mb->on_joystick_moved(event);
        }

    }else if( event.type == sf::Event::JoystickConnected ){ // data = event.joystickConnect
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onJoystickConnected
            mb->on_joystick_connected(event);
        }

    }else if( event.type == sf::Event::JoystickDisconnected ){ // data = event.joystickConnect
        std::list<MonoBehavior*> l = root_->getComponentsInChildrenOfType<MonoBehavior>();
        foreach (MonoBehavior* mb, l) {
            //! CLBK: onJoystickDisconnected
            mb->on_joystick_disconnected(event);
        }

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::update(sf::Time dt){
    // update self component
    foreach (Component* ccomp, all_items) {
        ccomp->update(dt);
    }

    // Update the root GameObject
    root_->update(dt);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::fixed_update(sf::Time dt){
    // Update the physics of the root GameObject
    root_->fixed_update(dt);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::late_update(sf::Time dt){
    // Late Update the root GameObject
    root_->late_update(dt);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::render(){
    // For each Camera/View, render its spot target.
    for( Camera* camera : cameras_ ){
        if( camera != nullptr && camera->is_enabled() ){

            // Activate/Switch render target to this view target
            gdf::kernel::GameInfo::game_info->setView( camera->getView() );

            // Fires only on local GameObject
            foreach (MonoBehavior* m, camera->game_object()->getComponentsOfType<MonoBehavior>() ) {
                if( m->is_enabled() ){
                    //! CLBK: onPreRender
                    m->on_pre_render( camera );
                }
            }

            // Apply the drawing.
            gdf::kernel::GameInfo::game_info->sf::RenderWindow::draw( *root_ );

            // Fires only on local GameObject
            foreach (MonoBehavior* m, camera->game_object()->getComponentsOfType<MonoBehavior>() ) {
                if( m->is_enabled() ){
                    //! CLBK: onPostRender
                    m->on_post_render( camera );
                }
            }

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::render_gui(){
    // Trigger a callback - invoking MonoBehavior::onGui if reimplemented
    foreach (MonoBehavior* m, root_->getComponentsInChildrenOfType<MonoBehavior>() ) {
        if( m->is_enabled() ){
            //! CLBK: onGui
            m->on_gui();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::set_as_daemon(bool daemon){
    is_daemon_ = daemon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<Camera*>& Scene::cameras(){
    return cameras_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* Scene::root() const{
    return this->root_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<GameObject*>& Scene::game_objects(){
    return game_objects_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map<Object*, sf::Time>& Scene::junkyard(){
    return junkyard_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::is_daemon() const{
    return is_daemon_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::is_loaded() const{
    return is_loaded_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
sf::Color Scene::clear_color() const{
    return clear_color_;
}

std::string Scene::name() const{
    return name_;
}


}}
