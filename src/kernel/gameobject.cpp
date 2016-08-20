#include "gameobject.h"

#include "Core/System/transform.h"
#include "Core/Graphic/renderer.h"
#include "Core/System/monobehavior.h"
#include "kernel/garbagecollector.h"

#include "Core/Utilities/algorithm.h"


namespace gdf {
namespace kernel{

unsigned long GameObject::game_object_counter = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject(std::string go_name)
{
    go_name = "";

    //Naming procedure
    //Auto-naming
/*  // Undefined FIND ( bug )
    if( go_name.empty() ){
        go_name = "game_object";

        naming:
        GameObject::game_object_counter++;

        //! NOTE: review ( it is Qt code ), change QString
        if( GameObject::find( ( QString( QString::fromStdString(go_name) + "_%1").arg(game_object_counter) ).toStdString() ) == nullptr ){
            go_name = ( QString( QString::fromStdString(go_name) + "_%1").arg(game_object_counter) ).toStdString();
        }else{
            goto naming;
        }
    }else{
        if( GameObject::find( go_name ) == nullptr ){
            name_ = go_name;
        }else{
            goto naming;
        }
    }
*/

    // Creates and Initialize the transform.
    transform_ = addComponent<Transform>();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::~GameObject(){

    // DFS-call: A Child may be dependant on Parent. The opposite is false.
    // Thus, destroy the child first ( break links from bottom to top )
    if( transform_ != nullptr ){
        //! NOTE: Use const ? somewhere
        for( auto child = transform_->children.begin(); child != transform_->children.end(); ){

            GameObject* ch = (*child)->game_object();
            child++; // Keep a reference to the next entry of children
            delete ch; // Then destroy the GO.
        }
    }

    //! NOTE: Detaching from the parentis done in ~Transform() ?


    // Destroy components of each game object starting by the top-most layer
    //! NOTE: Destroying components of a gameobject is triggered by destroying h_components content which recursively destroy the others.
    for( std::list< Component* >::iterator it = top_most_items.begin(); it != top_most_items.end(); ){
        Component* comp = *it;
        it++;
        delete (comp);
        // remove from h_components ( and components ?):
        // Must be performed from the component, because if destroy is called for a component top-most level
        // it must have the same effect
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::verbose(){
    std::cout << FGREEN <<"--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD << "#GameObject: " << RESET_BOLD << name_ << std::endl;
    for( Component* c : all_items ){
        std::cout << "\t" << c->metaObject()->className() << std::endl;
    }
    std::cout << RESET;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::draw( sf::RenderTarget &target, sf::RenderStates states) const{
    if( !active_in_hierarchy() )
        return;

    sf::Transform t = sf::Transform::Identity;

    states.transform *= transform_->get_matrix() * t;

    // Retrieves all renderers to draw their graphic component.
    std::list< Renderer* > rend_l = this->getComponentsOfType<Renderer>();

    //There is no control on Renderers.
    //but Further: they will have an 'enabled' member.
    for( Renderer* r : rend_l ){
        r->draw( target, states );
    }

    //Invoke draw recursively on every child.
    for( Transform* child : transform_->Transform::getChildren() ){
        child->game_object()->draw(target, states);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::init(){
    //! NOTE: How to update components ? (
    //! They are structured in a graph, having several source-Nodes
    for( Component* c : all_items ){
        c->init();
    }

    //Invoke init recursively on every child.
    for( Transform* child : transform_->Transform::getChildren() ){
        child->game_object()->init();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::update(sf::Time dt){
    //Do not update when the game object is not active in hierarchy.
    if( !active_in_hierarchy() )
        return;

    //Invoke components.
    for( Component* c : all_items ){
        //depending on the component type ? renderers, behaviours, others
        //! NOTE: HERE update, regular component
        c->update(dt);

    }

    //Call update recursively
    for( Transform* child : transform_->Transform::getChildren() ){
        child->game_object()->update(dt);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::fixed_update(sf::Time dt){
    if( !active_in_hierarchy() )
        return;

    //Invoke components.
    for( Component* c : all_items ){
        //! NOTE: HERE fixed update, includes PHYSIC components
        if( c->inherits( MonoBehavior::staticMetaObject.className() ) ){
            MonoBehavior* mbeh = static_cast<MonoBehavior*>(c);
            if( mbeh->is_enabled() )
                mbeh->fixed_update(dt);
        }else{
            // Update accordingly to the type of the component
            // Physics: Rigidbodies
        }
    }

    //Call update recursively
    for( Transform* child : transform_->Transform::getChildren() ){
        child->game_object()->fixed_update(dt);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::late_update(sf::Time dt){
    //Do not update when the game object is not active in hierarchy.
    if( !active_in_hierarchy() )
        return;


    //Invoke components.
    for( Component* c : all_items ){
        //! NOTE: HERE late update, usually monobehaviour ( user-reserved function )
        if( c->inherits( MonoBehavior::staticMetaObject.className() ) ){
            MonoBehavior* mbeh = static_cast<MonoBehavior*>(c);
            if( mbeh->is_enabled() )
                mbeh->late_update(dt);
        }else{
            // Update accordingly to the type of the component
            // none
        }
    }

    //Call update recursively
    for( Transform* child : transform_->Transform::getChildren() ){
        child->game_object()->late_update(dt);
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::send_message( const char* method_name, std::vector< QVariant > args ) const{
    std::list< MonoBehavior* > mono_l = getComponentsOfType< MonoBehavior >();
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

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::send_message_upwards(const char* method_name, std::vector<QVariant> args ) const{
    Transform* current = transform_;
    while( current != nullptr ){
        current->send_message(method_name, args );
        current = current->getParent();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::broadcast_message( const char* method_name, std::vector< QVariant > args ) const{
    //! NOTE: may cause an error due to nullptr
    //Invoke on current node.
    this->send_message( method_name, args );

    //Invoke recursively on children
    for( Transform* child : transform_->Transform::getChildren() ){
        child->broadcast_message(method_name, args );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::instantiate(){
    return GameObject::instantiate(nullptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::instantiate(std::string go_name, sf::Vector2f pos, float rotation){
    return GameObject::instantiate(nullptr, go_name, pos, rotation);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::instantiate(Transform* parent, std::string go_name, sf::Vector2f pos, float rotation){
    GameObject* go = new GameObject();
    if( parent != nullptr ){
        parent->attach_child(go->transform());
    }else{
        // if parent is nullptr, attach it to the Root
        gdf::kernel::GameInfo::game_info->active_scene()->root()->transform_->attach_child(go->transform());
    }

    go->name_ = go_name;
    go->transform_->set_position(pos);
    go->transform_->set_rotation(rotation);

    //! WARNING: This is moved and handled by the Chrono component.
    //! Spawn time now depends on the Chrono instance.
//    go->spawn_time_ = go->transform->getRoot()->game_object()->getScene()->life_time();
    return go;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::destroy(GameObject *go, unsigned long long ttd_ms){
    // Change:
    // In order to reduce class-dependability
    // GameObject & GarbageCollector
    // Entities willing to implement a GarbageCollector would have a special container called 'Junk'
    // When adding the GC component, the GC will bing his watched_list to this Junk list.
    // HOW to define the Junk list ? simple container or component ?

    // locate the root, because only the root is binded to the scene.
    Transform* t = go->transform_;
    while( t->getParent() != nullptr ){
        t = t->getParent();
    }

    // if the top most transform is for a Root. ( isRoot: game_object.scene != nullptr )
    if( t->game_object()->scene() != nullptr ){
        // it is root
        // add to GC of the root's scene
        t->game_object()->scene()->getComponent<gdf::kernel::GarbageCollector>()->collect(go, sf::milliseconds(ttd_ms) );
    }else{
        // it is not attached to a root ( orphan )
        // add to GC4Orphans
        gdf::kernel::GameInfo::game_info->getComponent<gdf::kernel::GarbageCollector>()->collect(go, sf::milliseconds(ttd_ms) );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::destroy(Component *comp, unsigned long long ttd_ms){
    //! BUG: You cant destroy anything, object must have a hirerachical structure in order to get the scene
    //! NOTE: Create a commong 'static' variable for a group of object ????
    //! USING a static const inside a TEMPLATE-function ........ like in template meta-programming

    //! GC: Use timer according to the GC owner.
    if( comp->game_object() == nullptr ){
        // add to GC4Orphans
        gdf::kernel::GameInfo::game_info->getComponent<gdf::kernel::GarbageCollector>()->collect(comp, sf::milliseconds(ttd_ms) );
    }else{
        // locate the root
        Transform* t = comp->game_object()->transform();
        while( t->getParent() != nullptr ){
            t = t->getParent();
        }

        // if the top most transform is for a Root. ( isRoot: game_object.scene != nullptr )
        if( t->game_object()->scene() != nullptr ){
            // it is root
            // add to GC of the root's scene
            t->game_object()->scene()->getComponent<gdf::kernel::GarbageCollector>()->collect(comp, sf::milliseconds(ttd_ms) );
        }else{
            // it is not attached to a root ( orphan )
            // add to GC4Orphans
            // Instead of calling the Gc, add the object to the junkcontainer
            gdf::kernel::GameInfo::game_info->getComponent<gdf::kernel::GarbageCollector>()->collect(comp, sf::milliseconds(ttd_ms) );
        }
    }
}

 //////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::set_active_self(bool etat){
    active_self_ = etat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::active_self() const{
    return active_self_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::active_in_hierarchy() const{
    bool active_in_hierarchy = true;
    Transform* t = transform_;
    while( t != nullptr ){
        active_in_hierarchy = active_in_hierarchy && t->game_object()->active_self();
        t = t->getParent();
    }
    return active_in_hierarchy;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Transform* GameObject::transform() const{
    return transform_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject* GameObject::parent() const{
    if( transform_ != nullptr && transform_->getParent() != nullptr ){
        return transform_->getParent()->game_object();
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
std::list<GameObject*> GameObject::children() const{
    std::list<GameObject*> l;
    foreach (const Transform* t, transform_->getChildren() ) {
        l.push_back( t->game_object() );
    }
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
gdf::kernel::Scene* GameObject::scene(){
    //! FIXME:to be reimplemented correctly
    return scene_;
}

}}
