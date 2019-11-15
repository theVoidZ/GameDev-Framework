#include "animationevent.h"

namespace gdf {
namespace animation{

AnimationEvent::AnimationEvent()
{
    event = [](void*){

    };
}

void AnimationEvent::exec(void *ptr){
    event(ptr);
}

}}
