#ifndef ANIMATIONEVENT_H
#define ANIMATIONEVENT_H

#include <functional>

class AnimationEvent
{
    public:
        AnimationEvent();

    public:
        void exec(void*);

    public:
        //Offset from the beginning ( zero by default )
        float relative_firing_time = 0.0f;

    private:
        //Function accept one parameter
        std::function< void(void*) > event;
};

#endif // ANIMATIONEVENT_H
