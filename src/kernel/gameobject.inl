
namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::get_component_in_parent() const{
    if( parent() != nullptr )
        return parent()->get_component<T>();
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::get_components_in_parent() const{
    std::list<T*> l;
    if( parent() != nullptr )
        return parent()->get_components<T>();
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::get_component_in_parent_of_type() const{
    if( parent() != nullptr )
        return parent()->get_component_of_type<T>();
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::get_components_in_parent_of_type() const{
    std::list<T*> l;
    if( parent() != nullptr )
        return parent()->get_components_of_type<T>();
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::get_component_in_children() const{
    T* result = nullptr;
    get_component_in_children__recursive<T>(&result, this, false);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::get_components_in_children() const{
    std::list<T*> result;
    get_components_in_children__recursive<T>(&result, this, false);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::get_component_in_children_of_type() const{
    T* result = nullptr;
    get_component_in_children__recursive<T>(&result, this, true);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::get_components_in_children_of_type() const{
    std::list<T*> result;

    //! NOTE: Conflict in list type
    this->get_components_in_children__recursive<T>(&result, this, true);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void GameObject::get_component_in_children__recursive(T** result, const GameObject* current_node, bool look_for_subtypes) const{
    if( *result == nullptr ){
        if( !look_for_subtypes ){
            *result = current_node->get_component<T>();
        }else{
            *result = current_node->get_component_of_type<T>();
        }

        for( GameObject* go : current_node->children() ){
            get_component_in_children__recursive <T>(result, go, look_for_subtypes);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void GameObject::get_components_in_children__recursive(std::list<T*>* result, const GameObject* current_node, bool look_for_subtypes) const{
    std::list<T*> tmp_result;

    // Get Components of the current node
    if( !look_for_subtypes ){
        tmp_result = current_node->get_components<T>();

    }else{
        tmp_result = current_node->get_components_of_type<T>();
    }

    // merge results
    for( T* a : tmp_result ){
        result->push_back(a);
    }

    // Children call
    for (GameObject* go : current_node->children()) {
        get_components_in_children__recursive <T>(result, go, look_for_subtypes);
    }
}


}}
