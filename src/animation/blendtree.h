#ifndef BLENDTREE_H
#define BLENDTREE_H

#include <vector>
#include <functional>

#include "motion.h"

namespace gdf {
namespace animation{

class AnimationClip;

class BlendTree : public Motion
{
    public:
        BlendTree();

    public:
        void update_function();

    public:
        //Function specific
        std::vector< float > threshold_;

        std::vector<gdf::animation::AnimationClip*> clips_;
        std::function< int(float) > function_;

        std::string parameter_; // considered a float for now


};

}}

#endif // BLENDTREE_H
