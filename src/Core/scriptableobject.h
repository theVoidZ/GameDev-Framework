#ifndef SCRIPTABLEOBJECT_H
#define SCRIPTABLEOBJECT_H

#include "kernel/object.h"

class ScriptableObject : public gdf::kernel::Object
{
    public:
        ScriptableObject();

    public:
        template< typename T >
        static T createInstance();

};

#endif // SCRIPTABLEOBJECT_H
