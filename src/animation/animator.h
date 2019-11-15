#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <algorithm>

#include "component.h"

namespace gdf {

namespace graphic {
class SpriteRenderer;
}

namespace animation{
enum class AnimatorUpdateMode{
    Normal,//	Normal update of the animator.
    AnimatePhysics,//	Updates the animator during the physic loop in order to have the animation system synchronized with the physics engine.
    UnscaledTime//	Animator updates independently of Time.timeScale.
};

enum class AnimatorCullingMode{
    AlwaysAnimate,	//Always animate the entire character. Object is animated even when offscreen.
    CullUpdateTransforms,	//Retarget, IK and write of Transforms are disabled when renderers are not visible.
    CullCompletely	//Animation is completely disabled when renderers are not visible.
};

class AnimatorCondition;
class AnimatorController;
class AnimatorState;
class AnimatorTransitionBase;
class Animation;
class Animation2;

class Animator : public gdf::kernel::Component
{
    public:
        Animator();

    public:
        void update( sf::Time dt );

    protected:
        void update_animation( sf::Time dt );

    public:
        AnimatorCullingMode culling_mode;
        AnimatorUpdateMode update_mode;

    public:
        AnimatorController* runtime_animator_controller;
        sf::Time play_back = sf::Time::Zero;

    public:
        //Working variable
        AnimatorState* current_state = nullptr;
        AnimatorTransitionBase* next_transition = nullptr;
        AnimatorState* next_state = nullptr;

        //While transiting, keeps track of the next state and the duration of the transition, because time will run over several updates
    private:
        // Holds a pointer to the current playing animation ( legacy / blendtree )
        Animation2* current_playing_animation = nullptr;

        // Trigger a reset in animation when a state or inner BlendTree animation is changed
        int last_clip_index = -1;

        bool is_transiting = false;
        sf::Time remaining_transition_duration = sf::Time::Zero;

        //! Used as exit_time tracker
        sf::Time last_transition_time = sf::Time::Zero;

};

}}

#endif // ANIMATOR_H
