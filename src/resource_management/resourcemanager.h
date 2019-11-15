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
#include "resource.h"
#include "object.h"
#include "component.h"
#include "tracker_ptr.h"


//! Very basic ResourceManager
/// \brief The resource manager holds a set of active instances that can be used on demand without
/// loading again the resource.
///
/// The resource manager is commong to all the scenes

class ResourceManager final : public gdf::kernel::Component
{
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
        T* load_resource(std::string uname, bool shared = true);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Deallocate the original resource ( memory ).
        ///
        void unload_resource(unsigned long id, bool force_unload=false);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unloads all unused resources (recursively)
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
        /// Used: when Pointer to resource in available instead of name, eg. get( r.id )
        template< typename T >
        gdf::kernel::tracker_ptr<T> get( unsigned long id);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< typename T >
        gdf::kernel::tracker_ptr<T> get(std::string name);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Holds the loaded resources.
        /// \sa Use load_resource, unload_resource to alter the content of this variable.
        ///

        /// Accept duplicate and keep track of non shared resources
        std::map<unsigned long, std::vector< gdf::kernel::tracker_ptr<Resource> >* > _resources;
//        std::map<unsigned long, gdf::kernel::tracker_ptr<Resource> > resources;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        static unsigned long local_instance_id_counter;


        std::map< unsigned long, unsigned long> duplicate_tracker_;
};

// resourceholder.tpp
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T>
T* ResourceManager::load_resource(std::string uname, bool shared){

    for( auto it = _resources.begin(); it != _resources.end(); it++ ){
        if( !(*it).second->empty() ){
            if( (*it).second->operator[](0).get()->name() == uname ){
                return (T*)((*it).second->operator[](0).get());
                /*
                // Resource found !
                if( !shared ){

                    // create resource
                    T* res = new T( *static_cast<T*>((*it).second->operator[](0).get()) );
                    duplicate_tracker_[res->id_]++;
                    res->duplicate_ = duplicate_tracker_[res->id_];
                    gdf::kernel::tracker_ptr<T> tr(res);
                    (*it).second.push_back( gdf::kernel::tracker_ptr<T>(tr) );

                    return (T*)res;
                }else{
                    // shared allowed, already exist
                    return (T*)((*it).second->operator[](0).get());
                }
                */
            }
        }
    }

    // Doesn't exist
    T* res = new T();
    res->name_ = uname;
    res->id_ = local_instance_id_counter;
    res->is_shared_ = shared;
    res->duplicate_ = 0;

    duplicate_tracker_.emplace( res->id_, 0);
    _resources.emplace( res->id_, new std::vector< gdf::kernel::tracker_ptr<Resource> >() ) ;

    gdf::kernel::tracker_ptr<T> tr(res);
    _resources[res->id_]->push_back( tr );
    local_instance_id_counter++;

    return (T*)res;

/*
    for( auto it = resources.begin(); it != resources.end(); it++ ){
        if( (*it).second.get()->name() == uname ){
            std::cout << BYELLOW << FRED << BOLD <<"ResourceManager::load_resouce - Resource already exist name=" << name_ << RESET << std::endl;
            return (T*)((*it).second.get());
        }
    }

    T* res = new T();
    //! NOTE: Making the resource initilises itself ?( Generic init function ? )
    // Let the resource initialize its own.
    res->name_ = uname;
    res->id_ = local_instance_id_counter;
    res->is_shared_ = shared;


    // active_instance & copies are set to 0.
    gdf::kernel::tracker_ptr<T> tr(res);
    resources.emplace( local_instance_id_counter, tr ) ;

    local_instance_id_counter++;


    // Init the resource here ?
//    ((Resource*)res)->init2(-1, ... );

    return (T*)res;
    */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template < typename T >
gdf::kernel::tracker_ptr<T> ResourceManager::get(unsigned long id ){

    auto it = _resources.find(id);

    if(it != _resources.end() ){
        if(!(*it).second->empty() ){
            if( !(*it).second->operator[](0).get()->is_shared_ ){
                // Clone and return new resource
                T* res = new T( *static_cast<T*>((*it).second->operator[](0).get()) );
                duplicate_tracker_[res->id_]++;
                res->duplicate_ = duplicate_tracker_[res->id_];
                gdf::kernel::tracker_ptr<T> tr(res);
                (*it).second->push_back( gdf::kernel::tracker_ptr<T>(tr) );

                return tr;
            }else{
                return ((*it).second->operator[](0));
            }
        }else{
            return gdf::kernel::tracker_ptr<T>();
        }

    }else{
        std::cout << BYELLOW << FRED << BOLD  << "ResourceManager::get - Resource does not exist id=" << id << RESET << std::endl;
        return gdf::kernel::tracker_ptr<T>();
    }

/*
    auto it = resources.find(id);

    if(it != resources.end() ){
        if( (*it).second.get()->is_shared_ ){

            T* clone_res = new T( *((*it).second.get()) );
            return gdf::kernel::tracker_ptr<T>(clone_res);
        }else{
            return (*it).second;
        }
    }else{
        std::cout << BYELLOW << FRED << BOLD  << "ResourceManager::get - Resource does not exist id=" << id << RESET << std::endl;
        return gdf::kernel::tracker_ptr<T>();
    }
*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template < typename T >
gdf::kernel::tracker_ptr<T> ResourceManager::get(std::string uname){

    for( auto it = _resources.begin(); it != _resources.end(); it++ ){
        if( !(*it).second->empty() ){
            if( (*it).second->operator[](0).get()->name() == uname ){
                 if( !(*it).second->operator[](0).get()->is_shared_ ){
                    // Clone and return new resource
                    T* res = new T( *static_cast<T*>((*it).second->operator[](0).get()) );
                    duplicate_tracker_[res->id_]++;
                    res->duplicate_ = duplicate_tracker_[res->id_];
                    gdf::kernel::tracker_ptr<T> tr(res);
                    (*it).second->push_back( gdf::kernel::tracker_ptr<T>() );
                    (*it).second->operator[]( (*it).second->size()-1 ) = tr;

                    ResourceManager* rm = gdf::kernel::GameInfo::game_info.get()->get_component<ResourceManager>();
                    rm->verbose();

                    return tr;
                }else{
                    // shared allowed, already exist
                    return ((*it).second->operator[](0));
                }
            }
        }
    }

    // Doesn't exist
    std::cout << BYELLOW << FRED << BOLD  << "ResourceManager::get - Resource does not exist name=" << uname << RESET << std::endl;
    return gdf::kernel::tracker_ptr<T>();

/*

    for( auto it = resources.begin(); it != resources.end(); it++ ){
        if( (*it).second.get()->name() == uname ){
            if( (*it).second.get()->is_shared_ ){

                T* clone_res = new T( *static_cast<T*>( (*it).second.get() ) );
                return gdf::kernel::tracker_ptr<T>(clone_res);
            }else{
                return (*it).second;
            }
        }
    }

    std::cout << BYELLOW << FRED << BOLD <<"ResourceManager::load_resouce - Resource does not exist name=" << uname << RESET << std::endl;
    return gdf::kernel::tracker_ptr<T>();
*/
}
#endif // RESOURCEMANAGER_H
