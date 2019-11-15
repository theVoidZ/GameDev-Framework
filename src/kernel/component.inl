namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* Component::host_object(){
//    static_assert( !std::is_base_of<gdf::kernel::ComponentContainer, T>() , "T must inherit from ComponentContainer" );
    return dynamic_cast<T*>(host_object_);
}

}}
