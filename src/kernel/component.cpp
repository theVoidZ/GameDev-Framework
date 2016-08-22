#include "component.h"

#include "kernel/gameobject.h"

namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Component::Component()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Component::~Component(){
    // Reach the bottom-most component.
    for( auto it = children_components_.begin(); it != children_components_.end(); ){
        Component* c = *it;
        it++;
        delete c;
    }

    // Unlink the component ( reference loss ? )
    if( this->parents_components_.size() == 0 ){
        if( game_object() != nullptr ){
            host_object_->top_most_items.remove(this);
        }
    }else{
        for( auto it = this->parents_components_.begin(); it != this->parents_components_.end(); it++ ){
            (*it)->children_components_.remove( this );
        }
        this->parents_components_.clear();
    }

    // Here comes the virtual destructor ?

    if( game_object() != nullptr ){
        host_object_->all_items.remove(this);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::verbose(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::init(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::update(sf::Time dt){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::send_message(const char *method_name, std::vector<QVariant> args) const{
    game_object()->send_message( method_name, args );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::send_message_upwards(const char *method_name, std::vector<QVariant> args) const{
    game_object()->send_message_upwards( method_name, args );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::broadcast_message(const char *method_name, std::vector<QVariant> args) const{
    game_object()->broadcast_message( method_name, args );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Component::set_host_object(ComponentContainer* ho){
    host_object_ = ho;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
gdf::kernel::GameObject* Component::game_object() const{
    return static_cast<GameObject*>(host_object_);
}

}}
