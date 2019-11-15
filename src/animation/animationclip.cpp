#include "animationclip.h"

#include "spritesheet.h"

#include "keyframe.h"
#include "resourcemanager.h"

namespace gdf {
namespace animation{

AnimationClip::AnimationClip(std::string name)
{
    name_ = name;
}

void AnimationClip::add_sprite( gdf::kernel::tracker_ptr <gdf::graphic::SpriteSheet > sprt_tile){
    tiles.push_back( sprt_tile );
}

void AnimationClip::add_frame(int sprite_id, int frame_id, int frame_rate){
    if( ( sprite_id < tiles.size() && sprite_id >= 0 ) && ( frame_id < tiles[sprite_id].get()->sheet_boundaries.size() && frame_id >= 0 ) ){
        keyframes.push_back( new KeyFrame(sprite_id, frame_id, frame_rate) );

        recompute_cumulative_frame_timeline();
    }
}

void AnimationClip::addFramesInSequence(int sprite_id, int end_frame, int frame_rate){
    for( int i=0; i < end_frame; i++ ){
        add_frame( sprite_id, i, frame_rate );
    }

    recompute_cumulative_frame_timeline();
}

void AnimationClip::addFramesInRange(int sprite_id, int start_frame, int end_frame, int frame_rate){
    if( start_frame < end_frame ){
        for( int i=start_frame; i < end_frame; i++ ){
            add_frame( sprite_id, i, frame_rate );
        }

        recompute_cumulative_frame_timeline();
    }
}

int AnimationClip::get_frame(int cumulative_time){
    if( cumulative_time < 0 ){
        return -1;
    }else if( cumulative_time > keyframes[ keyframes.size()-1 ]->frame_rate_cumulative ){
        return keyframes.size();
    }

    for( int i=0; i < keyframes.size(); i++ ){
        if( cumulative_time < keyframes[i]->frame_rate_cumulative && cumulative_time >= keyframes[i]->frame_rate_cumulative - keyframes[i]->frame_rate ){
            return i;
        }
    }
}

void AnimationClip::recompute_cumulative_frame_timeline(){
    if( keyframes.size() > 0 ){
        keyframes[0]->frame_rate_cumulative = keyframes[0]->frame_rate;

        for( int i=1; i < keyframes.size(); i++ ){
            keyframes[i]->frame_rate_cumulative = keyframes[i-1]->frame_rate_cumulative + keyframes[i]->frame_rate;
        }
    }
}

int AnimationClip::animation_duration() const{
    return keyframes[ keyframes.size()-1 ]->frame_rate_cumulative;
}

}}
