#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>

#include "Core/System/behavior.h"
#include "Core/Graphic/Animation/wrapmode.h"
#include "Core/DataStruct/bounds.h"

enum class AnimationCullingType{
    AlwaysAnimate, //Animation culling is disabled - object is animated even when offscreen.
    BasedOnRenderers //Animation is disabled when renderers are not visible.
};

class AnimationClip;
class BlendTree;
class KeyFrame;
class SpriteRenderer;


class Animation : public Behavior
{
    public:
        Animation();

    public:
        //Default update
        void update(sf::Time dt);
        void animate_clip( sf::Time dt);
        void animate_blend_tree( sf::Time dt);

    public:
        void play();
        void play_reverse();
        void stop();

    public:
        //! is public
        //Uses only one at a time.
        //! Clip attached to this animation
        AnimationClip* clip = nullptr;
        //! BlendTree attached to this aniamtion
        BlendTree* blend_tree = nullptr;

    public:
        bool animate_physics; //When turned on, animations will be executed in the physics loop. This is only useful in conjunction with kinematic rigidbodies.
        AnimationCullingType cullingType; //Controls culling of this Animation component.
        bool is_playing; //Are we playing any animations?
        Bounds local_bounds; //AABB of this Animation animation component in local space.
        bool play_automatically; //Should the default animation clip (the Animation.clip property) automatically start playing on startup?
        WrapMode wrap_mode; //How should time beyond the playback range of the clip be treated?

    private:
        //Used for internal functionning
        int index = 0;
        sf::Time play_back = sf::Time::Zero; //related to the timeline of the animation or lifetime of the animation ?
        sf::Time elapsed_frame_time = sf::Time::Zero;
        bool should_plays = true; //Allow the clip to play
        int clamp_index = 0; // Used with WrapMod::ClampForever
        bool reverse_play = false; // Used with WrapMode::PingPong
};

#endif // ANIMATION_H
