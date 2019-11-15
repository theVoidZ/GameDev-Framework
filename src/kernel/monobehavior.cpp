#include "monobehavior.h"

namespace gdf {
namespace kernel {

MonoBehavior::MonoBehavior()
{

}

MonoBehavior::~MonoBehavior(){

}

void MonoBehavior::verbose(){

}

void MonoBehavior::on_pre_render( Camera* camera ){

}

void MonoBehavior::on_post_render( Camera* camera ){

}

void MonoBehavior::on_gui(){

}

void MonoBehavior::on_became_visible(){

}

void MonoBehavior::on_became_invisible(){

}

void MonoBehavior::on_destroy(){

}

void MonoBehavior::on_closed(const sf::Event &event){

}

void MonoBehavior::on_resized(const sf::Event &event){

}

void MonoBehavior::on_gained_focus(const sf::Event &event){

}

void MonoBehavior::on_lost_focus(const sf::Event &event){

}

void MonoBehavior::on_mouse_entered(const sf::Event& event){

}

void MonoBehavior::on_mouse_left(const sf::Event& event){

}

void MonoBehavior::on_mouse_button_pressed(const sf::Event& event){

}

void MonoBehavior::on_mouse_button_released(const sf::Event& event){

}

void MonoBehavior::on_mouse_moved(const sf::Event& event){

}

void MonoBehavior::on_mouse_wheel_moved(const sf::Event& event){

}

void MonoBehavior::onMouseDoubleClick(const sf::Event& event){

}

void MonoBehavior::on_key_pressed(const sf::Event& event){

}

void MonoBehavior::on_key_released(const sf::Event& event){

}

void MonoBehavior::on_text_entered(const sf::Event& event){
    // Might be used (in the future) to implement high-level filtered/patterend input ( regex ) ?
}

void MonoBehavior::on_joystick_button_pressed(const sf::Event &event){

}

void MonoBehavior::on_joystick_button_released(const sf::Event &event){

}

void MonoBehavior::on_joystick_moved(const sf::Event &event){

}

void MonoBehavior::on_joystick_connected(const sf::Event &event){

}

void MonoBehavior::on_joystick_disconnected(const sf::Event &event){

}

void MonoBehavior::on_enter_state(animation::AnimatorTransitionBase *transition){

}

void MonoBehavior::on_exit_state(animation::AnimatorTransitionBase *transition){

}

void MonoBehavior::on_enter_collision(Collider *obj1, Collider *obj2){

}

void MonoBehavior::on_stay_collision(Collider *obj1, Collider *obj2){

}

void MonoBehavior::on_exit_collision(Collider *obj1, Collider *obj2){

}

}}
