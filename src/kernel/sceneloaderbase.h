#ifndef SCENELOADERBASE_H
#define SCENELOADERBASE_H

#include "component.h"

namespace gdf {
namespace kernel {

//! FIX: Must be accessible to end-user.
class SceneLoaderBase : public gdf::kernel::Component
{
    public:
        SceneLoaderBase();

    public:
        virtual void init();

};

}}

#endif // SCENELOADERBASE_H
