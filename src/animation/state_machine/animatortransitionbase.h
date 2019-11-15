#ifndef ANIMATORTRANSITIONBASE_H
#define ANIMATORTRANSITIONBASE_H

#include <list>
#include <string>

#include "object.h"
#include "animatorconditionmode.h"

namespace gdf {
namespace animation{

class AnimatorState;
class AnimatorCondition;

class AnimatorTransitionBase : public gdf::kernel::Object
{
    friend class gdf::animation::AnimatorState;

    public:
        AnimatorTransitionBase();
        AnimatorTransitionBase(AnimatorState* source, AnimatorState* dest);
        ~AnimatorTransitionBase();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void verbose();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //! Add new condition to this transition ( do not check validity of the parameter )
        void addCondition( std::string parameter, AnimatorConditionMode mode, float threshold );

    public:
        //! Add Or And Xor condition evaluation within the same Transition
        //!  CREATE A HIERARCHICAL Condition structure.
        //! ie: does not require a container but a hierarchy and a root item
        std::list<AnimatorCondition*> conditions_;

        AnimatorState* source_state_ = nullptr;
        AnimatorState* destination_state_ = nullptr;

        bool mute_ = false; // is ignored
        bool solo_ = false; // Set active and mute others 'non-soloed'

        bool can_transition_to_self_ = true;
        bool has_exit_time_ = false;

        AnimatorTransitionBase* opposite_transition = nullptr;

    private:
        sf::Time exit_time_ = sf::Time::Zero;
        sf::Time* duration_ = nullptr; // Duration of the transition

    public:
        // Getter
        sf::Time exit_time() const;
        sf::Time duration() const;

        // Setter
        //! This will force has_exit_time to true
        void set_exit_time( sf::Time duration_ );
};

}}

#endif // ANIMATORTRANSITIONBASE_H
