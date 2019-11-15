#ifndef ANIMATORCONDITION_H
#define ANIMATORCONDITION_H

#include <iostream>

#include <string>
#include <functional>
#include "animatorconditionmode.h"


namespace gdf {
namespace animation{

/*
 * Condition that is used to determine if a transition must be taken
 */
class AnimatorCondition
{
    public:
        AnimatorCondition();
        AnimatorCondition( std::string parameter, AnimatorConditionMode mode, float threshold );
        ~AnimatorCondition();

        static bool evaluate_condition(void* v, AnimatorCondition* cond);

        static std::string to_string(AnimatorConditionMode mode);
        static AnimatorConditionMode from_string(std::string mode);

    public:
        //!	The name of the parameter used in the condition.
        std::string parameter;
        //! The mode of the condition.
        AnimatorConditionMode mode;
        //! The AnimatorParameter's threshold value for the condition to be true.
        float threshold;

};

}}
#endif // ANIMATORCONDITION_H
