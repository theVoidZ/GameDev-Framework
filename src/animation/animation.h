#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>

#include "component.h"
#include "wrapmode.h"
#include "bounds.h"

#include "operators.h"


namespace gdf {

namespace graphic {
class SpriteRenderer;
class Sprite2D;

}


namespace animation{

enum class AnimationCullingType{
    AlwaysAnimate, //Animation culling is disabled - object is animated even when offscreen.
    BasedOnRenderers //Animation is disabled when renderers are not visible.
};

class AnimationClip;
class BlendTree;
class KeyFrame;

//! NOTE: Legacy animation, used as component
class Animation : public gdf::kernel::Component
{
    public:
        Animation();
        ~Animation();

        void verbose();

    public:
        //Default update
        void init();
        void update(sf::Time dt);

        //! NOTE: Used with legacy animation
        void animate_clip( sf::Time dt);

    public:
        void play();
        void stop();
        void reset();

    public:
        gdf::graphic::Sprite2D* currently_playing_sprite = nullptr;

    public:
        //! is public
        //Uses only one at a time.
        //! Clip attached to this animation ( not automatically instantiated because it is a resource )
        AnimationClip* clip = nullptr;
        //! BlendTree attached to this aniamtion

        gdf::graphic::SpriteRenderer* sprt_rend = nullptr;

        WrapMode wrap_mode = WrapMode::Once; //How should time beyond the playback range of the clip be treated?
        int clamp_index = 0; // Used with WrapMod::ClampForever

    private:
//        bool animate_physics; //When turned on, animations will be executed in the physics loop. This is only useful in conjunction with kinematic rigidbodies.
//        AnimationCullingType cullingType; //Controls culling of this Animation component.

        bool is_playing = true; //Are we playing any animations?
        bool should_plays = true; //Allow the clip to play

        sf::Time play_back = sf::Time::Zero; //related to the timeline of the animation or lifetime of the animation ?
        // SHOULD BE 1 or -1.
        short play_direction = 1; // Used with WrapMode::PingPong ( -1: backward playing in forward mode )

    private:
        //Used for internal functionning
        int pindex = -1; // allow to identify changes in frames,initially is (-1) to trigger the change in the first frame
        int index = 0; // current index of the frame
        sf::Time elapsed_frame_time = sf::Time::Zero;

    private:
        //! NOTE: Private setters used by the time rewind mechanism
        void set_is_playing(bool val);
        void set_should_plays(bool val);
        void set_play_back( sf::Time play_b );
        void set_play_direction(short play_dir);

};

}}

#endif // ANIMATION_H
