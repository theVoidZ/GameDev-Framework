namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* Component::host_object(){
    static_assert( !std::is_base_of<ComponentContainer, T>() , "T must inherit from ComponentContainer" );
    return dynamic_cast<T*>(host_object_);
}

}}
