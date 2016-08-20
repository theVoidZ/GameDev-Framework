#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include <iostream>
#include <stack>

#include "Core/System/behavior.h"
#include "time_management/event.h"

//! TimeKeeper is a Component that records events within the game_object
//! -> How to record user action ?

//! Uses one TimeKeeper per game_object
//! Then a TimeManager ( similar thing ) will collect data from GameObject's TimeKeeper and proceed for time manipulation.

class VelocityDef;
class SimulatorComponent;
class Animation;

class EventVelocity;
class EventTranslation;
class EventValueChanged;
class EventAnimationStateChanged;

class TimeKeeper : public Behavior
{
    Q_OBJECT
    public:
        TimeKeeper();
        void init();

        void insert_event(Event& ev);

        void verbose(); // rewind in debug mod

    public:
        //! NOTE: IMPLEMENT CALLBACKs IN TIMEKEEPER....
        virtual void onVelocityChanged(VelocityDef* target, sf::Vector2f old_v, sf::Vector2f new_v, unsigned long int timestamp );
        virtual void onTranslationChanged(VelocityDef* target, sf::Vector2f old_p, sf::Vector2f new_p, unsigned long int timestamp );
        virtual void onValueChanged(SimulatorComponent* target, int old_val, int new_val, unsigned long int timestamp );
        virtual void onAnimationStateChanged(Animation* target, int old_status, int new_status, unsigned long int timestamp );

//        onAnimationOver();
//        onTransformTranslated();
//        onVelocityChanged();

//        onStepsChanged();

    public:
        std::stack<Event*> past_events;
        std::stack<Event*> future_events;

        //! NOTE: How the watching is performed ? TimeKeeper watch the GO or GO notifies the TK ?

};

#endif // TIMEKEEPER_H
