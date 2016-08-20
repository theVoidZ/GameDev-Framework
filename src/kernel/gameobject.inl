
namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::getComponentInParent() const{
    if( parent() != nullptr )
        return parent()->getComponent<T>();
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::getComponentsInParent() const{
    std::list<T*> l;
    if( parent() != nullptr )
        return parent()->getComponents<T>();
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::getComponentInParentOfType() const{
    if( parent() != nullptr )
        return parent()->getComponentOfType<T>();
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::getComponentsInParentOfType() const{
    std::list<T*> l;
    if( parent() != nullptr )
        return parent()->getComponentsOfType<T>();
    return l;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::getComponentInChildren() const{
    T* result = nullptr;
    getComponentInChildren_recursive<T>(&result, this, false);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::getComponentsInChildren() const{
    std::list<T*> result;
    getComponentsInChildren_recursive<T>( &result, this, false);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* GameObject::getComponentInChildrenOfType() const{
    T* result = nullptr;
    getComponentInChildren_recursive<T>(&result, this, true);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::list<T*> GameObject::getComponentsInChildrenOfType() const{
    std::list<T*> result;

    //! NOTE: Conflict in list type
    this->getComponentsInChildren_recursive<T>( &result, this, true);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void GameObject::getComponentInChildren_recursive(T** result, const GameObject* current_node, bool look_for_subtypes) const{
    if( *result == nullptr ){
        if( !look_for_subtypes ){
            *result = current_node->getComponent<T>();
        }else{
            *result = current_node->getComponentOfType<T>();
        }

        for( GameObject* go : current_node->children() ){
            getComponentInChildren_recursive<T>(result, go, look_for_subtypes);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void GameObject::getComponentsInChildren_recursive(std::list<T*>* result, const GameObject* current_node, bool look_for_subtypes) const{
    std::list<T*> tmp_result;

    // Get Components of the current node
    if( !look_for_subtypes ){
        tmp_result = current_node->getComponents<T>();

    }else{
        tmp_result = current_node->getComponentsOfType<T>();
    }

    // merge results
    for( T* a : tmp_result ){
        result->push_back(a);
    }

    // Children call
    foreach (GameObject* go, current_node->children()) {
        getComponentsInChildren_recursive<T>(result, go, look_for_subtypes);
    }
}

}}
