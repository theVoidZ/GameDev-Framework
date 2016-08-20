#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <list>

class AnimationEvent;

class KeyFrame
{
    public:
        KeyFrame();
        KeyFrame(int sprite_id, int frame_id, float frame_rate);

    public:
        std::list<AnimationEvent*> starting_events;
        std::list<AnimationEvent*> ending_events;

        int sprite_id;
        int frame_id;

        //Specific frame rate of this keyframe. ( duration of this keyframe )
        float frame_rate;

};

#endif // KEYFRAME_H
