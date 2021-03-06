#ifndef ANIMATORCONDITIONMODE
#define ANIMATORCONDITIONMODE

#include <string>

namespace gdf {
namespace animation{

/*
 * The mode of the condition.
 */

enum class AnimatorConditionMode
{
    If, //! The condition is true when the parameter value is true.
    IfNot,//! The condition is true when the parameter value is false.
    Greater,//! The condition is true when parameter value is greater than the threshold.
    Less,//! The condition is true when the parameter value is less than the threshold.
    Equals,//! The condition is true when parameter value is equal to the threshold.
    NotEquals//! The condition is true when the parameter value is not equal to the threshold.
//    ExitTime //! Not used this way ( used separatly from conditions )
};

}}

#endif // ANIMATORCONDITIONMODE
