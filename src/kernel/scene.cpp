#include "scene.h"
#include "gameinfo.h"

#include "gameobject.h"
#include "component.h"
#include "monobehavior.h"

#include "chrono.h"

#include "camera.h"

#include "bounds.h"

#include  "collider.h"

namespace gdf {
namespace kernel{

std::map< tracker_ptr<GameObject>, sf::Time> Scene::global_go_junkyard_;
std::map< tracker_ptr<Component>, sf::Time> Scene::global_c_junkyard_;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
{
    add_component<gdf::temporal::Chrono>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Scene::~Scene(){
    // destroy root is handled by the std::shared_ptr

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* Scene::instantiate(tracker_ptr<GameObject> vessel){

    //! NOTE: Vessel MUST HAVE ManagerObject CREATED
    GameObject* go = new GameObject();
    go->scene_ = this;
    go->name_ = "";
//    std::cout << BOLD << "GO: instance_id:" << go->instance_id() << ", name:" << go->name() << RESET << std::endl;
    tracker_ptr<GameObject> tr(go);

    //! NOTE: Must use the semantic move to keep the same manager_object within the vessel.
    gdf::kernel::tracker_ptr<gdf::kernel::GameObject>::move(tr, vessel);

    //! Add the vessel instead of 'tr'
    this->game_objects_.push_back(vessel);
    return go;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* Scene::instantiate(std::string go_name){
    GameObject* go = new GameObject();
    go->scene_ = this;
    go->name_ = go_name;
//    std::cout << BOLD << "GO: instance_id:" << go->instance_id() << ", name:" << go->name() << RESET << std::endl;
    tracker_ptr<GameObject> tr(go);
    this->game_objects_.push_back( tr );

    return go;
}

GameObject* Scene::instantiate(Hierarchy *parent, std::string go_name){
    GameObject* go = instantiate(go_name);
    if( go != nullptr ){
        go->add_component<Hierarchy>();
        if( parent != nullptr ){
            parent->attach_child( go->hierarchy() );

//            parent->children().push_back( go->hierarchy() );
//            go->hierarchy().get()->parent_ = parent;
        }else{
            //! WARNING: Do not force root attachment
            std::cout << BOLD << FRED << "Warning: Isolated GameObject created - " << go->name() << RESET << std::endl;
        }
    }

    return go;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* Scene::instantiate(Hierarchy *parent, sf::Vector2f pos, float rotation, std::string go_name){
    GameObject* go = instantiate(parent, go_name);
    if( go != nullptr ){
        //! NOTE: Force a creation of Transform
        go->add_component<Transform>(); // GameObject::transform_ (auto filled)
        go->transform().get()->set_position(pos);
        go->transform().get()->set_rotation(rotation);
    }

    return go;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::init(){
    //Creating the root item to build the hierarchy. and returns a tracker of the given object.
    root_ = this->get_game_object( instantiate(nullptr, sf::Vector2f(0,0), 0.f, "root") );

    // Init the scene's Component
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->init();
        }
    }

}

void Scene::post_init(){
    // Post Init scene's Components.
    // Scene is built here ( post_init phase )
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->post_init();
        }
    }


    // Init the Root, gameobjects and all their components ( must be called after building the scene )
    if( !root_.expired() ){
        root_.get()->init();
    }


    // Mark the scene as Loaded
    is_loaded_ = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::handle_events(const sf::Event &event){
    // handle scene events
    on_event(event);

    if( root_.expired() ){
        return;
    }

    // Passes events handling to the GameObjects Component ( MonoBehavior )
    // Windows events
    if( event.type == sf::Event::Closed ){ // data = (none)
        std::cout << "REF: " << (int)ref_count_ << std::endl;
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onClosed
//            mb->on_closed(event);
        }
    }else if( event.type == sf::Event::Resized ){ // data = event.size
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onResized
            mb->on_resized(event);
        }
    }else if( event.type == sf::Event::GainedFocus ){ // data = (none)
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onGainedFocus
            mb->on_gained_focus(event);
        }
    }else if( event.type == sf::Event::LostFocus ){ // data = (none)
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onLostFocus
            mb->on_lost_focus(event);
        }

    }else if( event.type == sf::Event::MouseEntered ){ // data = (none)
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onMouseEntered
            mb->on_mouse_entered(event);
        }

    }else if( event.type == sf::Event::MouseLeft ){ // data = (none)
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onMouseLeft
            mb->on_mouse_left(event);
        }

    // Mouse events
    }else if( event.type == sf::Event::MouseButtonPressed ){ // data = event.mouseButton
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {

            //! CLBK: onMousePressed
            mb->on_mouse_button_pressed(event);
        }

    }else if( event.type == sf::Event::MouseButtonReleased ){ // data = event.mouseButton
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onMouseReleased
            mb->on_mouse_button_released(event);
        }

    }else if( event.type == sf::Event::MouseMoved ){ // data = event.mouseMove
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onMouseMove
            mb->on_mouse_moved(event);
        }

    }else if( event.type == sf::Event::MouseWheelMoved ){ // data = event.mouseWheel
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onMouseWheelMoved
            mb->on_mouse_wheel_moved(event);
        }

    // Keyboard events
    }else if( event.type == sf::Event::KeyPressed ){ // data = event.key
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onKeyPressed
            mb->on_key_pressed(event);
        }

    }else if( event.type == sf::Event::KeyReleased ){ // data = event.key
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onKeyReleased
            mb->on_key_released(event);
        }

    }else if( event.type == sf::Event::TextEntered ){ // data = event.text
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onTextEntered
            mb->on_text_entered(event);
        }

    // Joystick events
    }else if( event.type == sf::Event::JoystickButtonPressed ){ // data = event.joystickButton
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onJoystickButtonPressed
            mb->on_joystick_button_pressed(event);
        }

    }else if( event.type == sf::Event::JoystickButtonReleased ){ // data = event.joystickButton
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onJoystickButtonReleased
            mb->on_joystick_button_released(event);
        }

    }else if( event.type == sf::Event::JoystickMoved ){ // data = event.joystickMove
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onJoystickMoved
            mb->on_joystick_moved(event);
        }

    }else if( event.type == sf::Event::JoystickConnected ){ // data = event.joystickConnect
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onJoystickConnected
            mb->on_joystick_connected(event);
        }

    }else if( event.type == sf::Event::JoystickDisconnected ){ // data = event.joystickConnect
        std::list<MonoBehavior*> l = root_.get()->get_components_in_children_of_type<MonoBehavior>();
        for (MonoBehavior* mb : l) {
            //! CLBK: onJoystickDisconnected
            mb->on_joystick_disconnected(event);
        }

    }
}

void Scene::on_event(const sf::Event &event){

    if( event.type == sf::Event::Closed ){ // data = (none)
//        if( !root_.expired() ){
//            root_.reset();
//        }

//        std::cout << ITALIC << BYELLOW << FBLACK << "Initiating root reset " << RESET << std::endl;
//        root_ = new GameObject();
//        root_->scene_ = this;
//        root_->init();

//        GameObject* g1 = instantiate();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::update(sf::Time dt){
    //! SUGG: Enability of SCENE ?

    // Altering time (dt) according to factor
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    // update self component
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->update(dt);
        }
    }

    if( !root_.expired() ){
        // Update the root GameObject
        root_.get()->update(dt);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::fixed_update(sf::Time dt){

    // Altering time (dt) according to factor
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    // update self component
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->fixed_update(dt);
        }
    }

    if( !root_.expired() ){
        // Update the root GameObject
        root_.get()->fixed_update(dt);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::late_update(sf::Time dt){

    // Altering time (dt) according to factor
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    // update self component
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->late_update(dt);
        }
    }


    if( !root_.expired() ){
        // Late Update the root GameObject
        root_.get()->late_update(dt);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::draw(){
    //! NOTE: Consider Scene's Graphical component ?

    // no render selfcomponent
    if( root_.expired() ){
        return;
    }

    gdf::kernel::GameInfo::game_info->sf::RenderWindow::draw( *root_.get() );

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::draw_gui(){
    if( root_.expired() ){
        return;
    }

    // Trigger a callback - invoking MonoBehavior::onGui if reimplemented
    for (MonoBehavior* m : root_.get()->get_components_in_children_of_type<MonoBehavior>() ) {
        if( m->enabled() ){
            //! CLBK: onGui
            m->on_gui();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Scene::set_active(bool active){
    is_active_ = active;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list< tracker_ptr<Camera> >& Scene::cameras(){
    return cameras_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<tracker_ptr<GameObject> > &Scene::game_objects(){
    return game_objects_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<GameObject> Scene::root() const{
    return root_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<GameObject> Scene::get_game_object(GameObject *go){
    for(auto it = game_objects_.begin(); it != game_objects_.end(); it++ ){
        if( !(*it).expired() ){
            if( (*it).get() == go ){
                return *it;
            }
        }
    }
    return tracker_ptr<GameObject>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<GameObject> Scene::get_game_object(unsigned long instance_id){
    std::list< tracker_ptr<GameObject> >::iterator it;
    for( it = game_objects_.begin(); it != game_objects_.end(); it++ ){
        if( !(*it).expired() ){
            if( (*it).get()->instance_id() == instance_id ){
                return *it;
            }
        }
    }
    return tracker_ptr<GameObject>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<GameObject> Scene::get_game_object(std::string instance_name){
    std::list< tracker_ptr<GameObject> >::iterator it;
    for( it = game_objects_.begin(); it != game_objects_.end(); it++ ){
        if( !(*it).expired() ){
            if( (*it).get()->name() == instance_name ){
                return *it;
            }
        }
    }
    return tracker_ptr<GameObject>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map< tracker_ptr<GameObject>, sf::Time> &Scene::go_junkyard(){
    return go_junkyard_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map< tracker_ptr<Component>, sf::Time> &Scene::c_junkyard(){
    return c_junkyard_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<temporal::Chrono> Scene::chrono(){
    if( chrono_.expired() ){
        chrono_ = get_component_tracker<gdf::temporal::Chrono>(get_component<gdf::temporal::Chrono>());
    }
    return chrono_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::is_active() const{
    return is_active_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Scene::is_loaded() const{
    return is_loaded_;
}

std::string Scene::name() const{
    return name_;
}


}}
