namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* HierarchicalContainer::addComponent(std::list<T*>* container){
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
T* HierarchicalContainer::getComponent() const{
    // Can use meta object system of qt.
    for( gdf::kernel::Component* c : all_items ){
        boost::typeindex::type_index t1 = boost::typeindex::type_id_runtime(*c);
        boost::typeindex::type_index t2 = boost::typeindex::type_id_with_cvr<T>();

        if( t1.pretty_name() == t2.pretty_name() ){
            return static_cast<T*>(c);
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> HierarchicalContainer::getComponents() const{
    std::list<T*> l;
    for( gdf::kernel::Component* c : all_items ){
        boost::typeindex::type_index t1 = boost::typeindex::type_id_runtime(*c);
        boost::typeindex::type_index t2 = boost::typeindex::type_id_with_cvr<T>();

        if( t1.pretty_name() == t2.pretty_name() ){
            l.push_back( static_cast<T*>(c) );
        }
    }
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* HierarchicalContainer::getComponentOfType() const{
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
std::list<T*> HierarchicalContainer::getComponentsOfType() const{
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