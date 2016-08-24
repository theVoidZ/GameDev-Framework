
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< int scene_index>
GameObject* GameObject::instantiate(){
    return GameObject::instantiate<scene_index>(nullptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< int scene_index>
GameObject* GameObject::instantiate(std::string go_name, sf::Vector2f pos, float rotation){
    return GameObject::instantiate<scene_index>(nullptr, go_name, pos, rotation);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< int scene_index>
GameObject* GameObject::instantiate(Hierarchy* parent, std::string go_name, sf::Vector2f pos, float rotation){
    GameObject* go = new GameObject();
    if( parent != nullptr ){
        parent->attach_child(go->hierarchy());
    }else{
        // if parent is nullptr, attach it to the Root
        auto sc = GameInfo::game_info->scenes().find(scene_index);
        if( sc != GameInfo::game_info->scenes().end() ){
            go->scene_ = gdf::kernel::GameInfo::game_info->scenes()[scene_index];
            go->scene_->root()->hierarchy_->attach_child(go->hierarchy());
        }else{
            std::cout << FRED << BOLD << "Scene #" << scene_index << " do not exist, GameObject::instantiante aborted" << RESET << std::endl;
            return nullptr;
        }
    }

    go->name_ = go_name;
//    go->transform_->set_position(pos);
//    go->transform_->set_rotation(rotation);

    return go;
}


}}
