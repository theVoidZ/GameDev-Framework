#include "hierarchy.h"

namespace gdf {
namespace kernel {


Hierarchy::Hierarchy()
{

}

Hierarchy::~Hierarchy(){

}

void Hierarchy::attach_child( Hierarchy* child ){
    std::list< Hierarchy* >::iterator it;

    if( this->is_child_of(child) ){
        std::cout << "> Attempting to make the ancestor of this hierarchy as a child. attachChild operation aborted" << std::endl;
        return;
    }

    bool exist = false;

    //!
    for( it = children_.begin(); it != children_.end(); it++ ){
        if( *it == child ){
            exist = true;
            return;
        }
    }

    if( !exist ){
        //If child is attached, detach it.
        if( child != nullptr && child->parent_ != nullptr ){
            child->parent_->detach_child(child);
        }

        //Establish links
        children_.push_back(child);
        child->parent_ = this;
    }

}

void Hierarchy::detach_child( Hierarchy* child ){
    if( child != nullptr ){
        child->parent_ = nullptr;
        children_.remove(child);
    }
}

void Hierarchy::attach_to(Hierarchy *parent){
    // Only attach uses detach
    if( this->parent_ != nullptr ){
        this->parent_->detach_child(this);
    }

    if( parent != nullptr ){
        parent->attach_child(this);
    }else{
        std::cout << "Attempting to attach a Hierarchy to a null parent" << std::endl;
    }
}

Hierarchy* Hierarchy::detach(){
    if( this->parent_ != nullptr ){
        Hierarchy* p = this->parent_;
        this->parent_->detach_child(this);
        return p;
    }else{
        return nullptr;
    }
}

void Hierarchy::detach_children(){
    for( Hierarchy* child : children_ ){
        detach_child( child );
    }
}

Hierarchy* Hierarchy::get_child( int index ) const{
    if( index >= 0 && index < children_.size() ){
        std::list< Hierarchy* >::const_iterator it;
        for( it=children_.begin();index>0; it++,index--);
        return *it;
    }else{
        return nullptr;
    }
}

bool Hierarchy::is_child_of( Hierarchy* parent ) const{
    const Hierarchy* current = this->parent();

    while( current != nullptr ){
        if( current == parent )
            return true;
        current = current->parent_;
    }

    return false;
}

Hierarchy* Hierarchy::parent() const{
    return parent_;
}

const std::list<Hierarchy *>& Hierarchy::children() const{
    return children_;
}

Hierarchy* Hierarchy::root() const{
    //! FIXME:
//    return gdf::kernel::GameInfo::game_info->active_scene()->root()->Hierarchy();
}

Hierarchy* Hierarchy::topmost_root(){
    Hierarchy* current = this;

    while( current->parent_ != nullptr )
        current = current->parent_;

    return current;
}

unsigned int Hierarchy::child_count() const{
    return children_.size();
}


}}
