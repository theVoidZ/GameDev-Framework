#include "gameobject.h"

#include "monobehavior.h"

#include "chrono.h"



namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject(std::string go_name)
    :ComponentContainer()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::~GameObject(){
//    std::cout << "~GameObject.begin " << name_ << std::endl;

    tracker_ptr< GameObject > this_tracker = scene()->get_game_object(this);
//    std::cout << this_tracker.get()->name() << " = " << name() << " is destroyed " << std::endl;

	// STEP 1 - Unlink parent and clear reference
	/// NOTE: Transfered to ~Hierarchy

    // STEP 2 - Destroy components (OR) if no hierarchy is found
    std::list< tracker_ptr<Component> >::iterator it2;
    for( it2 = top_most_items.begin(); it2 != top_most_items.end(); ){
        //! Specific component destruction event comes before component destruction event.
        (*it2).reset();

        it2 = top_most_items.erase(it2);

        //Erase entry from 'all_item' is included in Component::~Component
    }

    // STEP 3 - Remove entry from scene::game_objects
    std::list< tracker_ptr<GameObject> >::iterator it;
    for( it = scene_->game_objects().begin(); it != scene_->game_objects().end(); it++ ){
        if( !(*it).expired() ){
            if( (*it).get() == this ){
                scene_->game_objects().erase(it);
                break;
            }
        }
    }

    std::cout << BOLD << FGREEN << "GameObject: " << name_ << " has been destroyed " << RESET << std::endl;
//    std::cout << "~GameObject.end " << name_ << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::verbose() const{
    std::cout << FGREEN <<"--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD << "#GameObject: " << RESET_BOLD << name_ << "\t active:" << active_self_ << "\t" << instance_id_ << std::endl;

    std::list< tracker_ptr<Component> >::const_iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            std::cout << "\t" << boost::typeindex::type_id_runtime(*(*itc).get()).pretty_name()  << std::endl;
        }
    }
    std::cout << RESET;
}


void GameObject::on_gui(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::init(){
    // Initializes self-components
    //! NOTE: Hierarchical init of components ?
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->init();
        }
    }


    //Invoke init recursively on every child.
    if( !hierarchy().expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            if( !child.expired() )
                child.get()->game_object()->init();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::update(sf::Time dt){
    //Do not update when the game object is not active in hierarchy.
    if( !active_in_hierarchy() )
        return;

    // Altering time (dt)
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    //Invoke components.
    //! NOTE: Hierarchical update of components ?
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->update(dt);
        }
    }

    //Call update recursively
    if( !hierarchy().expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            child.get()->game_object()->update(dt);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::fixed_update(sf::Time dt){
    if( !active_in_hierarchy() )
        return;

    // Altering time (dt)
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    //Invoke components.
    //! NOTE: Hierarchical update of components ?
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->fixed_update(dt);
        }
    }


    //Call update recursively
    if( !hierarchy().expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            child.get()->game_object()->fixed_update(dt);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::late_update(sf::Time dt){
    //Do not update when the game object is not active in hierarchy.
    if( !active_in_hierarchy() )
        return;

    // Altering time (dt)
    dt = ( !chrono_.expired() ) ? dt*chrono_.get()->speed_factor_ : dt*1.0f;

    //Invoke components.
    //! NOTE: Hierarchical update of components ?
    std::list< tracker_ptr<Component> >::iterator itc = all_items.begin();
    for( ; itc != all_items.end(); itc++ ){
        if( !(*itc).expired() ){
            (*itc).get()->late_update(dt);
        }
    }


    //Call update recursively
    if( !hierarchy().expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            child.get()->game_object()->late_update(dt);
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::draw( sf::RenderTarget &target, sf::RenderStates states) const{
    if( !active_in_hierarchy() )
        return;

    sf::Transform t = sf::Transform::Identity;


    // If an object does not have a transform component, draw on it according to its most upper parent having transform
    // or absolute posionning.
    //! OBSOLETE: transofrm_ is introduced
//    if( (tr = get_component<Transform>()) == nullptr )
//    if( (tr = transform_.get() ) == nullptr ){
//        states.transform *= t;

//    }else{
//    }
    if( !hierarchy_.expired() ){
        if( !transform_.expired() ){
            states.transform = transform_.get()->local_to_world_matrix() * t;
        }
    }


    //! OBSOLETE: May limit the number of items to call.
    for( tracker_ptr<Component> ccomp : all_items) {
        if( !ccomp.expired() )
        {
            ccomp.get()->draw(target, states);
        }
    }

    //Invoke draw recursively on every child.
    //! FIXME: Using the variable and not the getters ( it is a const method )
    if( !hierarchy_.expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            child.get()->game_object()->draw(target, states);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::send_message(const char* method_name, std::vector<void*> args ) const{
    /*
    std::list< MonoBehavior* > mono_l = get_components_of_type< MonoBehavior >();
    for( MonoBehavior* m : mono_l ){
        switch( args.size() ){
        case 0:
            QMetaObject::invokeMethod(m, method_name );
            break;
        case 1:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ) );
            break;
        case 2:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ) );
            break;
        case 3:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ) );
            break;
        case 4:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ) );
            break;
        case 5:
            QMetaObject::invokeMethod(m, method_name ,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ) );
            break;
        case 6:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ),
                                      QGenericArgument(args[5].typeName(), args[5].data() ) );
            break;
        case 7:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ),
                                      QGenericArgument(args[5].typeName(), args[5].data() ),
                                      QGenericArgument(args[6].typeName(), args[6].data() ) );
            break;
        case 8:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ),
                                      QGenericArgument(args[5].typeName(), args[5].data() ),
                                      QGenericArgument(args[6].typeName(), args[6].data() ),
                                      QGenericArgument(args[7].typeName(), args[7].data() ));
            break;
        case 9:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ),
                                      QGenericArgument(args[5].typeName(), args[5].data() ),
                                      QGenericArgument(args[6].typeName(), args[6].data() ),
                                      QGenericArgument(args[7].typeName(), args[7].data() ),
                                      QGenericArgument(args[8].typeName(), args[8].data() ) );
            break;
        case 10:
            QMetaObject::invokeMethod(m, method_name,
                                      QGenericArgument(args[0].typeName(), args[0].data() ),
                                      QGenericArgument(args[1].typeName(), args[1].data() ),
                                      QGenericArgument(args[2].typeName(), args[2].data() ),
                                      QGenericArgument(args[3].typeName(), args[3].data() ),
                                      QGenericArgument(args[4].typeName(), args[4].data() ),
                                      QGenericArgument(args[5].typeName(), args[5].data() ),
                                      QGenericArgument(args[6].typeName(), args[6].data() ),
                                      QGenericArgument(args[7].typeName(), args[7].data() ),
                                      QGenericArgument(args[8].typeName(), args[8].data() ),
                                      QGenericArgument(args[9].typeName(), args[9].data() ) );
            break;
        }
    }
    */

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::send_message_upwards(const char* method_name, std::vector<void*> args ) const{
    //! FIXME: Not watched
    if( !hierarchy_.expired() ){
        Hierarchy* current = hierarchy_.get();
        while( current != nullptr ){
            current->game_object()->send_message(method_name, args );
            current = current->parent();
        }
    }else{
        // If hierarcy is null, just send it to the local gameobject
        send_message(method_name, args );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::broadcast_message(const char* method_name, std::vector<void*> args ) const{
    //! NOTE: may cause an error due to nullptr
    //Invoke on current node.
    this->send_message( method_name, args );

    //Invoke recursively on children
    //! FIXME: Not watched
    if( !hierarchy_.expired() ){
        for( tracker_ptr<Hierarchy> child : hierarchy_.get()->children() ){
            child.get()->game_object()->broadcast_message(method_name, args );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::find(std::string name, Scene* scene_target) {
    if( scene_target != nullptr ){
        GameObject* gameObject = find_in_scene(name, scene_target);
        if( gameObject != nullptr ){
            return gameObject;
        }
    }else{
        for( auto it : GameInfo::game_info.get()->scenes() ){
            if( it.second != nullptr ){
                Scene* sc = it.second;
                GameObject* gameObject;
                if( ( gameObject = find_in_scene(name, sc) ) != nullptr ){
                    return gameObject;
                }
            }
        }
    }

    std::cout << FORANGE << BOLD << "GameObject::find - gameobject name: " << name << " does not exist" << RESET << std::endl;
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::find_in_scene(std::string name, Scene* scene_target) {
    if( scene_target != nullptr ){
        for( const tracker_ptr<GameObject>& tr_go : scene_target->game_objects() ){
            if( !tr_go.expired() ){
                if( tr_go.get()->name() == name ){
                    return tr_go.get();
                }
            }
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::find_in_scene(unsigned long instance_id, Scene* scene_target) {
    if( scene_target != nullptr ){
        for( const tracker_ptr<GameObject>& tr_go : scene_target->game_objects() ){
            if( !tr_go.expired() ){
                if( tr_go.get()->instance_id_ == instance_id ){
                    return tr_go.get();
                }
            }
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::destroy(GameObject *go, unsigned long long ttd_ms){
    if( go != nullptr ){
        if( go->scene() != nullptr ){
            tracker_ptr<GameObject> tr = go->scene()->get_game_object(go);
            //! NOTE: Special treatment upon trying to destroy the root GameObject.
            if( !go->scene()->root().expired() ){
//                if( go->scene()->root().get() == obj ){
//                    std::cout << BOLD << FYELLOW << BRED << "WARNING: Cannot destroy root GameObject" << RESET << std::endl;
//                }
            }

            if( tr.get() == tr.get()->scene()->root().get() ){
                std::cout << BOLD << FYELLOW << BRED << "WARNING: Cannot destroy root GameObject" << RESET << std::endl;
            }else{
            }
            go->scene()->go_junkyard().emplace( tr, sf::milliseconds(ttd_ms) );

        }else{
            // add to GC4Orphans
            tracker_ptr<GameObject> lost_go(go);
            Scene::global_go_junkyard_.emplace( lost_go, sf::milliseconds(ttd_ms) );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::destroy( tracker_ptr<GameObject> go, unsigned long long ttd_ms){
    if( !go.expired() ){
        if( go.get()->scene() != nullptr ){
            //! NOTE: Special treatment upon trying to destroy the root GameObject.
            if( !go.get()->scene()->root().expired() ){
//                if( go->scene()->root().get() == obj ){
//                    std::cout << BOLD << FYELLOW << BRED << "WARNING: Cannot destroy root GameObject" << RESET << std::endl;
//                }
            }

            if( go.get() == go.get()->scene()->root().get() ){
                std::cout << BOLD << FYELLOW << BRED << "WARNING: Cannot destroy root GameObject" << RESET << std::endl;
            }else{
            }
            go.get()->scene()->go_junkyard().emplace(go, sf::milliseconds(ttd_ms) );

        }else{
            // add to GC4Orphans
            Scene::global_go_junkyard_.emplace( go, sf::milliseconds(ttd_ms) );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::destroy(Component *comp, unsigned long long ttd_ms){
    if( comp != nullptr ){
        ComponentContainer* cc = comp->host_object<ComponentContainer>();

        if( cc == nullptr ){
            // add to GC4Orphans
            tracker_ptr<Component> lost_comp(comp);
            Scene::global_c_junkyard_.emplace( lost_comp, sf::milliseconds(ttd_ms) );
        }else{
            // DO i belong to Scene ?

            if( dynamic_cast<GameObject*>(cc) != nullptr ){
                tracker_ptr<Component> comp_tracker;

                // Look for the tracker_ptr of the component based on the direct ptr
                for( auto it = comp->game_object()->all_items.begin(); it != comp->game_object()->all_items.end(); it ++ ){
                    if( !(*it).expired() ){
                        if( (*it).get() == comp ){
                            comp_tracker = *it;
                            break;
                        }
                    }
                }

                if( comp->game_object()->scene() != nullptr ){
                    comp->game_object()->scene()->c_junkyard().emplace( comp_tracker, sf::milliseconds(ttd_ms) );
                }else{
                    Scene::global_c_junkyard_.emplace( comp_tracker, sf::milliseconds(ttd_ms) );
                }
            }else{
                tracker_ptr<Component> lost_tr(comp);
                Scene::global_c_junkyard_.emplace( lost_tr, sf::milliseconds(ttd_ms) );

            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::active_self() const{
    return active_self_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::active_in_hierarchy() const{
    bool active_in_hierarchy = true;
    if( !hierarchy_.expired() ){
        Hierarchy* t = hierarchy_.get();
        while( t != nullptr ){
            active_in_hierarchy = active_in_hierarchy && t->game_object()->active_self();
            t = t->parent();
        }
        return active_in_hierarchy;
    }else{
        return false;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<Hierarchy>& GameObject::hierarchy(){
    if( hierarchy_.expired() ){
        hierarchy_ = get_component_tracker<gdf::kernel::Hierarchy>(get_component<gdf::kernel::Hierarchy>());
    }
    return hierarchy_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr<Transform>& GameObject::transform(){
    if( transform_.expired() ){
        transform_ = get_component_tracker<gdf::kernel::Transform>(get_component<gdf::kernel::Transform>());
    }
    return transform_;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
tracker_ptr< gdf::temporal::Chrono >& GameObject::chrono(){
    if( chrono_.expired() ){
        chrono_ = get_component_tracker<gdf::temporal::Chrono>(get_component<gdf::temporal::Chrono>());
    }
    return chrono_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::parent() const{
    if( !hierarchy_.expired() && hierarchy_.get()->parent() != nullptr ){
        return hierarchy_.get()->parent()->game_object();
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<GameObject*> GameObject::children() const{
    std::list<GameObject*> l;
    if( !hierarchy_.expired() ){
        for ( tracker_ptr<Hierarchy> t : hierarchy_.get()->children() ) {
            l.push_back( t.get()->game_object() );
        }
    }
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
gdf::kernel::Scene* GameObject::scene() const{
    return scene_;
}

}}
