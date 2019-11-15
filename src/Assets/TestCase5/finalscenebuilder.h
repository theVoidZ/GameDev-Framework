#ifndef FINALSCENEBUILDER_H
#define FINALSCENEBUILDER_H

#include "monobehavior.h"

#include <fstream>

namespace gdf {
namespace graphic {
class Sprite2D;

}}

class FinalSceneBuilder : public gdf::kernel::MonoBehavior
{
    public:
        FinalSceneBuilder();

        void init();
        void post_init();
        void load_resources();
        void build();

    protected:
        gdf::graphic::Sprite2D* sprt2d;
};

#endif // FINALSCENEBUILDER_H
