#include "animatorcondition.h"

AnimatorCondition::AnimatorCondition(std::string parameter, AnimatorConditionMode mode, float threshold){

    this->parameter = parameter;
    this->mode = mode;
    this->threshold = threshold;
}

AnimatorCondition::~AnimatorCondition(){

}
