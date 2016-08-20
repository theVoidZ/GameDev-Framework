#ifndef RESOURCE_H
#define RESOURCE_H

// c++-includes
#include <string>
#include <iostream>
#include <cstdarg>

// sfml-includes

// qt-includes

// user-includes
#include "kernel/object.h"

class ResourceManager;

class Resource  : public gdf::kernel::Object
{
    friend class ResourceManager;

    Q_OBJECT
    public:
        //! Constructor
        Resource();

        //! Copy constructor
        Resource(const Resource& res);

    public:
        //!< name is inherited
        unsigned long id_;
        bool is_shared = false;

        // ref_count, is_linked ?
        // The problem is: How to know when a resource is detached ?

};

#endif // RESOURCE_H
