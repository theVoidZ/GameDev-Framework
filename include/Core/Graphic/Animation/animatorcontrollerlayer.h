#ifndef ANIMATORCONTROLLERLAYER_H
#define ANIMATORCONTROLLERLAYER_H

#include <string>

#include "Core/Graphic/Animation/animatorlayerblendingmode.h"

class AnimatorStateMachine;


class AnimatorControllerLayer
{
    public:
        AnimatorControllerLayer();

    public:
        /*
        GetOverrideBehaviours(); Gets the override behaviour list for the state on the given layer.
        GetOverrideMotion();	Gets the override motion for the state on the given layer.
        SetOverrideBehaviours();	Sets the override behaviour list for the state on the given layer.
        SetOverrideMotion();	Sets the override motion for the state on the given layer.
        */

    public:
        //The blending mode used by the layer. It is not taken into account for the first layer.
        AnimatorLayerBlendingMode blending_mode;
        //The default blending weight that the layers has. It is not taken into account for the first layer.
        float default_weight;
        //When active, the layer will have an IK pass when evaluated. It will trigger an OnAnimatorIK callback.
        bool ik_pass;
        //	The name of the layer.
        std::string name;
        //The state machine for the layer.
        AnimatorStateMachine* state_machine;

};

#endif // ANIMATORCONTROLLERLAYER_H
