#include <gameinfo.h>
#include "animatorcondition.h"

namespace gdf {
namespace animation{

AnimatorCondition::AnimatorCondition(){

}

AnimatorCondition::AnimatorCondition(std::string parameter, AnimatorConditionMode mode, float threshold){

    this->parameter = parameter;
    this->mode = mode;
    this->threshold = threshold;
}

AnimatorCondition::~AnimatorCondition(){

}


std::string AnimatorCondition::to_string(AnimatorConditionMode mode){
    if( mode == AnimatorConditionMode::If){
        return "if";
    }else if( mode == AnimatorConditionMode::IfNot){
        return "ifNot";
    }else if( mode == AnimatorConditionMode::Greater){
        return "Greater";
    }else if( mode == AnimatorConditionMode::Less){
        return "Less";
    }else if( mode == AnimatorConditionMode::Equals){
        return "Equals";
    }else if( mode == AnimatorConditionMode::NotEquals){
        return "NotEquals";
    }
}

AnimatorConditionMode AnimatorCondition::from_string(std::string mode){
    if( mode == "If" ){
        return AnimatorConditionMode::If;
    }else if( mode == "IfNot" ){
        return AnimatorConditionMode::IfNot;
    }else if( mode == "Equals" ){
        return AnimatorConditionMode::Equals;
    }else if( mode == "NotEquals" ){
        return AnimatorConditionMode::NotEquals;
    }else if( mode == "Greater" ){
        return AnimatorConditionMode::Greater;
    }else if( mode == "Less" ){
        return AnimatorConditionMode::Less;
    }

}

bool AnimatorCondition::evaluate_condition(void* v, gdf::animation::AnimatorCondition *cond){
    if( cond == nullptr )
        return false;
//     std::cout << *(float*)v << std::endl;

    if( cond->mode == gdf::animation::AnimatorConditionMode::Equals ){
        if( *(float*)v == cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == gdf::animation::AnimatorConditionMode::NotEquals ){
        if( *(float*)v != cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == gdf::animation::AnimatorConditionMode::Greater ){
        if( *(float*)v > cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == gdf::animation::AnimatorConditionMode::Less ){
        if( *(float*)v < cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    //Used for booleans
    if( cond->mode == gdf::animation::AnimatorConditionMode::If ){
        if( *(bool*)v == (bool)cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == gdf::animation::AnimatorConditionMode::IfNot ){
        if( *(bool*)v != (bool)cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    return false;

}

}}
