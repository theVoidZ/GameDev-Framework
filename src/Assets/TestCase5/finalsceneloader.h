#ifndef FINALSCENELOADER_H
#define FINALSCENELOADER_H

#include "sceneloaderbase.h"

class FinalSceneLoader : public gdf::kernel::SceneLoaderBase
{
    public:
        FinalSceneLoader();

    public:
        void init();
};

#endif // FINALSCENELOADER_H
