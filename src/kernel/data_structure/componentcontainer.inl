namespace gdf {
namespace kernel{


//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::add_component(std::list<T*>* container){
    T* c = add_component <T>();
    if( c != nullptr ){
        if( container != nullptr ){
            container->push_back(c);
        }
    }

    return c;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::add_component(std::list< gdf::kernel::tracker_ptr<T> >* container){
    T* c = add_component <T>();
    if( c != nullptr ){
        if( container != nullptr ){
            gdf::kernel::tracker_ptr<T> tr_c =  this->get_component_tracker<T>(c);
            container->push_back(tr_c);
        }
    }

    return c;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::add_component(Component* existing_comp){
    // @ compile-time Type checking
    static_assert( std::is_base_of<Component, T>::value );

    T* c;
    if( existing_comp == nullptr ){
        c = new T();
    }else{
        c = dynamic_cast<T*>( existing_comp );
    }

    //! NOTE: Automatically Register any created type
    boost::typeindex::type_index t = boost::typeindex::type_id_with_cvr<T>();
    register_component(t.pretty_name(), &gdf::kernel::ComponentFactory::generic_ctor<T>);

    if( c->classname_ == "" )
        c->classname_ = t.pretty_name();

    std::list< tracker_ptr<Component> > comp_requirement;

    if( this->can_attach_component(this, c, &comp_requirement) ){
        //Make the gameobject linking
        c->set_host_object( this );

        if( !comp_requirement.empty() ){
            make_linking(c, &comp_requirement);
        }else{
            // If there is no component of the requirement, create it a top most level of the GO
            tracker_ptr<Component> tr(c);
            all_items.push_back( tr );
            top_most_items.push_back( tr );
        }


//        std::cout << BOLD << FBLUE << "+" << std::setw(23) << std::left << boost::typeindex::type_id_with_cvr<T>().pretty_name() << "→\t" << std::left << boost::typeindex::type_id_runtime(*this) << "::components" << RESET << std::endl;

        return c;
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::add_component(tracker_ptr<Component> vessel, Component* exisiting_comp, std::string comp_classname){
    // @ compile-time Type checking
    static_assert( std::is_base_of<Component, T>::value );

    T* c;
    if( exisiting_comp == nullptr ){
        c = new T();
    }else{
        c = dynamic_cast<T*>( exisiting_comp );
    }

    //! NOTE: Automatically Register any created type
    boost::typeindex::type_index t = boost::typeindex::type_id_with_cvr<T>();
    register_component(t.pretty_name(), &gdf::kernel::ComponentFactory::generic_ctor<T>);

    if( c->classname_ == "" )
        c->classname_ = comp_classname;

    std::list< tracker_ptr<Component> > comp_requirement;

    if( this->can_attach_component(this, c, &comp_requirement) ){
        //Make the gameobject linking
        c->set_host_object( this );

        tracker_ptr<Component> comp_holder(c);
        tracker_ptr<Component>::move(comp_holder, vessel);

        if( !comp_requirement.empty() ){
            make_linking(vessel, &comp_requirement);
        }else{
            // If there is no component of the requirement, create it a top most level of the GO
            all_items.push_back( vessel );
            top_most_items.push_back( vessel );
        }

//        std::cout << BOLD << FBLUE << "+" << std::setw(23) << std::left << boost::typeindex::type_id_with_cvr<T>().pretty_name() << "→\t" << std::left << boost::typeindex::type_id_runtime(*this) << "::components" << RESET << std::endl;

        return c;
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
gdf::kernel::tracker_ptr<T> ComponentContainer::get_component_tracker(gdf::kernel::Component* comp){
    if( comp != nullptr ){
        for( const gdf::kernel::tracker_ptr< gdf::kernel::Component >& pcomp : all_items ){
            if( !pcomp.expired() ){
                if( comp == pcomp.get() ){
                    return pcomp;
                }
            }
        }
    }

    return tracker_ptr<T>();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::get_component() const{
    for( const tracker_ptr<Component>& c : all_items ){
        if( !c.expired() ){
            if( boost::typeindex::type_id_runtime(*(c.get())) == boost::typeindex::type_id_with_cvr<T>() ){
                return static_cast<T*>(c.get());
            }
        }
    }
    return nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> ComponentContainer::get_components() const{
    std::list<T*> l;
    for( const tracker_ptr<Component>& c : all_items ){
        if( !c.expired() ){
            if( boost::typeindex::type_id_runtime(*(c.get())) == boost::typeindex::type_id_with_cvr<T>() ){
                l.push_back( static_cast<T*>(c.get()) );
            }
        }
    }
    return l;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* ComponentContainer::get_component_of_type() const{
    for( const tracker_ptr<Component>& c : all_items ){
        if( !c.expired() ){
            if( dynamic_cast<T*>(c.get()) != nullptr ){
                return static_cast<T*>(c.get());
            }
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> ComponentContainer::get_components_of_type() const{
    std::list<T*> l;
    for( const tracker_ptr<Component>& c : all_items ){
        if( !c.expired() ){
            if( dynamic_cast<T*>(c.get()) != nullptr ){
                l.push_back( static_cast<T*>(c.get()) );
            }
        }
    }
    return l;
}

}}
