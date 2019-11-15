#include "hierarchy.h"

#include "gameobject.h"

namespace gdf {
namespace kernel {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Hierarchy::Hierarchy()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Hierarchy::~Hierarchy(){
    // WARNING: hierarchy's Callbacks are preprocessed in ~GameObject
//	std::cout << BYELLOW << BOLD << "~Hierarchy" << RESET << std::endl;

	// Recursive call to all GameObject's of children hierarchy
	for( auto it = children_.begin(); it != children_.end(); ){
		auto sh = this->game_object()->scene()->get_game_object( (*it).get()->game_object() );
		it++;
		sh.reset();

		// Erase entry from children is included in "Hierarchy::detach_child"
	}

    // STEP 1 - Unlink parent and clear reference
    if( this->parent_ != nullptr ){
        //Detach from parent ( GO is not destroyed yet )
        this->parent_->detach_child( this->host_object_->get_component_tracker<Hierarchy>(this) );
    }else{
        // iam the root (top most item ) - skip
        // deletion is triggered through scene->root_

    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hierarchy::init(){
    // When the GameObject is holding a Specific pointer to Component ( Singleton )
    // An auto assign of that pointer can be performed in 'init'
    // Init is invoked after creation
    if( game_object() != nullptr ){
        game_object()->hierarchy();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hierarchy::attach_child( tracker_ptr<Hierarchy> child ){
    if( child.expired() ){
        std::cout << "> Attempting to attach an invalid child" << std::endl;
        return;
    }

    if( this == child.get() || this->is_child_of(child) ){
        std::cout << "> Attempting to make the ancestor of this hierarchy as a child. attachChild operation aborted" << std::endl;
        return;
    }

    bool exist = false;

    // Check existence
    std::list< tracker_ptr<Hierarchy> >::iterator it;
    for( it = children_.begin(); it != children_.end(); it++ ){
        if( (*it).get() == child.get() ){
            exist = true;
            break; // to end
        }
    }

    if( !exist ){
        //If child is attached, detach it.
        if( child.get()->parent_ != nullptr ){
            child.get()->parent_->detach_child(child);
        }

        //Establish links
        children_.push_back(child);
        child.get()->parent_ = this;

        child.get()->link_checker++;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hierarchy::detach_child( tracker_ptr<Hierarchy> child ){
    if( !child.expired() ){

        // Is it really its children
        std::list< tracker_ptr<Hierarchy> >::iterator it;
        for( it = children_.begin(); it != children_.end(); it++ ){
            if( !(*it).expired() ){
                if( (*it).get() == child.get() ){
                    (*it).get()->parent_ = nullptr;
                    children_.erase(it);

                    child.get()->link_checker--;
                    break;
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hierarchy::detach_children(){
    std::list< tracker_ptr< Hierarchy > >::iterator it;
    for( it = children_.begin(); it != children_.end(); ){
        auto it_item = *it;
        this->detach_child( it_item );
        it++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Hierarchy::is_child_of( tracker_ptr<Hierarchy> parent ) const{
    if( !parent.expired() ) {

        Hierarchy* current = this->parent();

        while( current != nullptr ) {
            if( current == parent.get() )
                return true;
            current = current->parent_;
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Hierarchy *Hierarchy::parent() const{
    return parent_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<tracker_ptr<Hierarchy> >& Hierarchy::children(){
    return children_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int Hierarchy::child_count() const{
    return children_.size();
}


}}
