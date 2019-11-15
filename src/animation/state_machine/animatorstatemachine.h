#ifndef ANIMATORSTATEMACHINE_H
#define ANIMATORSTATEMACHINE_H

#include <string>
#include <list>
#include <vector>

#include "object.h"

namespace gdf {
namespace animation{

class AnimatorState;
class AnimatorTransitionBase;

class AnimatorStateMachine : public gdf::kernel::Object
{
    public:
        AnimatorStateMachine(std::string name_="StateMachine");

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void verbose();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        AnimatorState* add_state(std::string name_ );
        AnimatorTransitionBase* add_transition(AnimatorState* source_state, AnimatorState* destination_state);

        AnimatorState* find( std::string state_name );
        AnimatorTransitionBase* find( std::string trans_source_name, std::string trans_dest_name );

    public:
        //! Sub states machines
        std::vector<AnimatorStateMachine*> state_machines_;

        //! All states
        std::vector< AnimatorState* > states_;
        std::vector< AnimatorTransitionBase* > transitions_;


};

}}

#endif // ANIMATORSTATEMACHINE_H
