#ifndef ANIMATIONCLIP_H
#define ANIMATIONCLIP_H

#include <list>

#include "motion.h"
#include "bounds.h"
#include "wrapmode.h"


namespace gdf {

namespace graphic {
class SpriteSheet;

}


namespace animation{

class KeyFrame;

class AnimationClip : public Motion
{
    public:
        AnimationClip(std::string name="");

    public:
        void add_sprite( gdf::kernel::tracker_ptr < gdf::graphic::SpriteSheet > sprt_tile);

        void add_frame(int sprite_id, int frame_id, int frame_rate = gdf::kernel::GameInfo::delta_time.asMilliseconds() );
        void addFramesInSequence(int sprite_id, int end_frame, int frame_rate = gdf::kernel::GameInfo::delta_time.asMilliseconds());
        void addFramesInRange(int sprite_id, int start_frame, int end_frame, int frame_rate = gdf::kernel::GameInfo::delta_time.asMilliseconds());

        //! WARNING: Not optimal function ( lot of iteration )
        int get_frame( int cumulative_time );
        int animation_duration() const;

    private:
        void recompute_cumulative_frame_timeline();

    public:
        //Make it possible to access the SPrite through name. ( implies MAP structure )
        //! NOTE: This should be a vector of std::shared_ptr ( for reference count )
        std::vector< gdf::kernel::tracker_ptr<gdf::graphic::SpriteSheet> > tiles;

        std::vector<KeyFrame*> keyframes;

        Bounds local_bounds;

};

}}

#endif // ANIMATIONCLIP_H
