#ifndef ANIMATIONCLIP_H
#define ANIMATIONCLIP_H

#include <list>

#include "Core/Graphic/Animation/motion.h"
#include "Core/DataStruct/bounds.h"
#include "Core/Graphic/Animation/wrapmode.h"

class KeyFrame;
class SpriteTile;

class AnimationClip : public Motion
{
    public:
        AnimationClip();

    public:
        void addSprite(const SpriteTile& sprt_tile);

        void addFrame(int sprite_id, int frame_id, float frame_rate = gdf::kernel::GameInfo::delta_time.asSeconds() );
        void addFramesInSequence(int sprite_id, int end_frame, float frame_rate = gdf::kernel::GameInfo::delta_time.asSeconds());
        void addFramesInRange(int sprite_id, int start_frame, int end_frame, float frame_rate = gdf::kernel::GameInfo::delta_time.asSeconds());

    public:
        //Make it possible to access the SPrite through name. ( implies MAP structure )
        //! NOTE: This should be a vector of std::shared_ptr ( for reference count )
        std::vector< const SpriteTile*> tiles;

        std::vector<KeyFrame*> keyframes;

        Bounds local_bounds;
        WrapMode wrap_mode;

};

#endif // ANIMATIONCLIP_H
