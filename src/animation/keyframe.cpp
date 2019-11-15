#include "keyframe.h"

#include "animationevent.h"

namespace gdf {
namespace animation{

KeyFrame::KeyFrame()
{

}

KeyFrame::KeyFrame(int sprite_id, int frame_id, int frame_rate){
    this->sprite_id = sprite_id;
    this->frame_id = frame_id;
    this->frame_rate = frame_rate;
}

}}
