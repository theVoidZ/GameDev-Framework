namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::addComponent(std::list<T*>* container){
    // static_assert( std::is_base_of<Component, T>()
    T* c = new T();

    if( container != nullptr ){
        container->push_back(c);
    }

    std::list<gdf::kernel::Component*> comp_requirement;

    if( this->can_attach_component(c, &comp_requirement) ){
        //Make the gameobject linking
        c->set_host_object( this );

        all_items.push_back( c );

        //! Creates a way to retreive all the components of a game_object
        if( !comp_requirement.empty() ){
            make_linking(c, &comp_requirement);
        }else{
            // If there is no component of the requirement, create it a top most level of the GO
            top_most_items.push_back(c);
        }

        std::cout << BOLD << FBLUE << "+" << std::setw(23) << std::left << boost::typeindex::type_id_with_cvr<T>().pretty_name() << "→\t" << std::left << boost::typeindex::type_id_runtime(*this) << "::components" << RESET << std::endl;

        return c;
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::getComponent() const{
    for( gdf::kernel::Component* c : all_items ){
        if( strcmp(T::staticMetaObject.className(), static_cast<QObject*>(c)->metaObject()->className()) == 0 ){
            return static_cast<T*>(c);
        }
    }
    return nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> ComponentContainer::getComponents() const{
    std::list<T*> l;
    for( gdf::kernel::Component* c : all_items ){
        if( strcmp(T::staticMetaObject.className(), static_cast<QObject*>(c)->metaObject()->className()) == 0 ){
            l.push_back( static_cast<T*>(c) );
        }
    }
    return l;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::getComponentOfType() const{
    for( gdf::kernel::Component* c : all_items ){
        /// QT: static_cast<QObject*>(c)->inherits( T::staticMetaObject.className() )
        if( static_cast<QObject*>(c)->inherits( T::staticMetaObject.className() ) ){
            return static_cast<T*>(c);
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> ComponentContainer::getComponentsOfType() const{
    std::list<T*> l;
    for( gdf::kernel::Component* c : all_items ){
        /// QT: static_cast<QObject*>(c)->inherits( T::staticMetaObject.className() )
        if( static_cast<QObject*>(c)->inherits( T::staticMetaObject.className() ) ){
            l.push_back( static_cast<T*>(c) );
        }
    }
    return l;
}

}}
