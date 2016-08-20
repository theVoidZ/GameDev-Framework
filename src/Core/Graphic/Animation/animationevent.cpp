#include "animationevent.h"

AnimationEvent::AnimationEvent()
{
    event = [](void*){

    };
}

void AnimationEvent::exec(void *ptr){
    event(ptr);
}
