#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

// c++-includes
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <memory>
#include <map>
#include <assert.h>

// sfml-includes

// qt-includes

// user-includes
#include "resource_management/resource.h"
#include "kernel/object.h"
#include "kernel/component.h"

//! Very basic ResourceManager
/// \brief The resource manager holds a set of active instances that can be used on demand without
/// loading again the resource.
///
/// The resource manager is commong to all the scenes
///
class ResourceManager final : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default constructor
        ResourceManager();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default destructor
        ~ResourceManager();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void verbose();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< typename T >
        T* load_resource(unsigned long id, bool is_shared, std::string name = "" );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Deallocate the original resource ( memory ).
        ///
        /// \attention WARNING: What if it is used ?, how to know that
        ///
        void unload_resource(unsigned long id);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unloads all unused resources
        ///
        /// Every resource of the resource manager that is not actually used is removed.
        ///
        /// Only shared resource are effected by this method, because non-shared resource are not tracked after
        /// they clone themselves.
        ///
        /// A resource is unused when the \a std::shared_ptr<T>::use_count is equal to at most one. Means, there
        /// is one unqiue reference pointing to the object, which is the one helo by the resource manager.
        ///
        void unload_unused_resources();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a resource with id 'id'.
        /// \param id   Id of the resource to retreive
        /// \return     Return the resource with id 'id', otherwise, nullptr if the id does not match
        ///
        template< typename T >
        std::shared_ptr<T> get( unsigned long id);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Holds the loaded resources.
        /// \sa Use load_resource, unload_resource to alter the content of this variable.
        ///
        std::map<unsigned long, std::shared_ptr<Resource> > resources;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

// resourceholder.tpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T>
T* ResourceManager::load_resource(unsigned long id, bool is_shared, std::string name ){
    auto it = resources.find(id);
    if( it == resources.end() ){
        T* res = new T();
        // Let the resource initialize by its own.
        //res->on_init( 1, "./Cockatrice.png" ); // better from resource_book
        ((Resource*)res)->name_ = name;
        ((Resource*)res)->id_ = id;
        ((Resource*)res)->is_shared = is_shared;

        // active_instance & copies are set to 0.
        resources.insert( std::pair<unsigned long, std::shared_ptr<T> >( id, std::shared_ptr<T>(res) ) ) ;

        return (T*)res;
    }else{
        std::cout << "ResourceManager::load_resouce - Resource already exist id=" << id << std::endl;
        return nullptr;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template < typename T >
std::shared_ptr<T> ResourceManager::get(unsigned long id ){
    auto it = resources.find(id);

    if(it != resources.end() ){

        if( (*it).second->is_shared ){
            std::shared_ptr<T> sh = std::dynamic_pointer_cast<T>( (*it).second );
            return sh;
        }else{
            // return a clone of the resource
            T* t = new T( *(T*)( (*it).second.get() ) );
            std::shared_ptr<T> sh(t);
            return sh;
        }
    }else{
        std::cout << "ResourceManager::get - Resource does not exist id=" << id << std::endl;
        return std::shared_ptr<T>();
    }
}

#endif // RESOURCEMANAGER_H
