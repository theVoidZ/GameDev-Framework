#ifndef ANIMATORUPDATEMODE
#define ANIMATORUPDATEMODE

enum class AnimatorUpdateMode{
    Normal,//	Normal update of the animator.
    AnimatePhysics,//	Updates the animator during the physic loop in order to have the animation system synchronized with the physics engine.
    UnscaledTime//	Animator updates independently of Time.timeScale.
};

#endif // ANIMATORUPDATEMODE

