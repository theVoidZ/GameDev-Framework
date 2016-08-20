#include "animationclip.h"

#include "resource_management/spritetile.h"

#include "Core/Graphic/Animation/keyframe.h"
#include "resource_management/resourcemanager.h"

AnimationClip::AnimationClip()
{
//    SpriteTile& s = GameInfo::game_info->getActiveScene()->getResourceManager()->get<SpriteTile>(3);

//    addSprite(s);

//    addFramesInSequence(0,15, 45.f/1000);

}

void AnimationClip::addSprite(const SpriteTile& sprt_tile){
    tiles.push_back( &sprt_tile );
}

void AnimationClip::addFrame(int sprite_id, int frame_id, float frame_rate){
    if( ( sprite_id < tiles.size() && sprite_id >= 0 ) && ( frame_id < tiles[sprite_id]->tex_tile.size() && frame_id >= 0 ) ){
        keyframes.push_back( new KeyFrame(sprite_id, frame_id, frame_rate) );

    }
}

void AnimationClip::addFramesInSequence(int sprite_id, int end_frame, float frame_rate){
    for( int i=0; i < end_frame; i++ ){
        addFrame( sprite_id, i, frame_rate );
    }
}

void AnimationClip::addFramesInRange(int sprite_id, int start_frame, int end_frame, float frame_rate){
    if( start_frame < end_frame ){
        for( int i=start_frame; i < end_frame; i++ ){
            addFrame( sprite_id, i, frame_rate );
        }
    }
}
