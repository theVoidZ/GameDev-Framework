#include "animatorcontrollerlayer.h"

#include "animatorstatemachine.h"

namespace gdf {
namespace animation{

AnimatorControllerLayer::AnimatorControllerLayer()
{
    state_machine = new gdf::animation::AnimatorStateMachine();
}

}}
