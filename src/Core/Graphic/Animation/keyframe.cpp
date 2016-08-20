#include "keyframe.h"

#include "Core/Graphic/Animation/animationevent.h"

KeyFrame::KeyFrame()
{

}

KeyFrame::KeyFrame(int sprite_id, int frame_id, float frame_rate){
    this->sprite_id = sprite_id;
    this->frame_id = frame_id;
    this->frame_rate = frame_rate;
}
