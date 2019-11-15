#ifndef RESOURCE_H
#define RESOURCE_H

// c++-includes
#include <string>
#include <iostream>
#include <cstdarg>

// sfml-includes

// qt-includes

// user-includes
#include "object.h"

class ResourceManager;

// Inherits Object for name.
class Resource  : public gdf::kernel::Object
{
    friend class ResourceManager;

    public:
        //! Constructor
        Resource();
        ~Resource();

        //! Copy constructor
        Resource(const Resource& res);

        void verbose();

        public:
        std::string filename_;

        /// Local instance id
        unsigned long id_ = 0x00;
        unsigned long duplicate_ = 0x0;

        //! If true, the resource can be used by refered by several object. else, the object trying to use this resource
        //! needs to create a new instance of that resource to use it.
        bool is_shared_ = false;

};

#endif // RESOURCE_H
