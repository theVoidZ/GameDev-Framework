#ifndef ANIMATION2_H
#define ANIMATION2_H

#include <iostream>

#include "component.h"
#include "wrapmode.h"
#include "bounds.h"

#include "operators.h"


namespace gdf {

namespace kernel {
class GameObject;
}

namespace graphic {
class SpriteRenderer;
class Sprite2D;
}


namespace animation{

class Animator;
class AnimationClip;
class BlendTree;
class KeyFrame;

//! NOTE: Mechanim animation, used with an Animator
class Animation2
{
    friend class gdf::animation::Animator;

    public:
        Animation2();
        ~Animation2();

    public:
        gdf::graphic::Sprite2D* step( sf::Time dt, float param_value);

    public:
        void play();
        void stop();
        void reset();

    public:
        sf::RectangleShape get_hitbox();

    public:
        gdf::graphic::Sprite2D* currently_playing_sprite = nullptr;

        gdf::kernel::GameObject* game_object = nullptr;

    public:
        //! is public
        //Uses only one at a time.
        //! BlendTree attached to this aniamtion ( not automatically instantiated because it is a resource )
        BlendTree* blend_tree = nullptr;

    public:
        bool is_playing = true; //Are we playing any animations?
        bool should_plays = true; //Allow the clip to play

        WrapMode wrap_mode = WrapMode::Once; //How should time beyond the playback range of the clip be treated?

        int clamp_index = 0; // Used with WrapMod::ClampForever

        int clip_index;
        int pclip_index = -1;

    public:
        //Used for internal functionning
        int pindex = -1; // allow to identify changes in frames,initially is (-1) to trigger the change in the first frame
        int index = 0; // current index of the frame
    private:
        // SHOULD BE 1 or -1.
        short play_direction = 1; // Used with WrapMode::PingPong ( -1: backward playing in forward mode )

        sf::Time play_back = sf::Time::Zero; //related to the timeline of the animation or lifetime of the animation ?
        sf::Time elapsed_frame_time = sf::Time::Zero;

};

}}

#endif // ANIMATION2_H
