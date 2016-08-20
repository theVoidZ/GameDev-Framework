#include "timekeeper.h"

#include "time_management/event.h"
#include "time_management/eventvelocity.h"
#include "time_management/eventtranslation.h"
#include "time_management/eventvaluechange.h"
#include "time_management/eventanimationstatechanged.h"

#include "Assets/TestCases/velocitydef.h"
#include "Assets/TestCases/simulatorcomponent.h"
#include "Core/Graphic/Animation/animation.h"

#include "time_management/chrono.h"

TimeKeeper::TimeKeeper()
{

}

void TimeKeeper::init(){

}

void TimeKeeper::insert_event( Event& ev){
    past_events.push( &ev );
    ev.verbose();
}

void TimeKeeper::verbose(){
    std::cout << UNDERLINE << FGREEN << BOLD << "# Content of the TimeKeeper: " << RESET << std::endl;
    std::cout << FGREEN << BOLD << "# Events of the Past " << RESET_BOLD << std::endl;
    std::stack<Event*> copy_events = std::stack<Event*>(past_events);
    while( !copy_events.empty() ){
        Event* ev= copy_events.top();
        copy_events.pop();
        ev->verbose();
    }

    std::cout << FGREEN << BOLD << "# Events of the future " << RESET_BOLD << std::endl;
    std::stack<Event*> copy_events2 = std::stack<Event*>(future_events);
    while( !copy_events2.empty() ){
        Event* ev= copy_events2.top();
        copy_events2.pop();
        ev->verbose();
    }

    std::cout << RESET << std::endl;

}

void TimeKeeper::onVelocityChanged(VelocityDef *target, sf::Vector2f old_v, sf::Vector2f new_v, unsigned long timestamp){
    Chrono* ch = game_object()->getComponent<Chrono>();
    if( ch != nullptr && ch->status_ == ChronoPlayStatus::FORWARD )
        this->insert_event( *EventVelocity::create_event(target, old_v, new_v, timestamp ) );
}

void TimeKeeper::onTranslationChanged(VelocityDef *target, sf::Vector2f old_p, sf::Vector2f new_p, unsigned long timestamp){
    Chrono* ch = game_object()->getComponent<Chrono>();
    if( ch != nullptr && ch->status_ == ChronoPlayStatus::FORWARD )
        this->insert_event( *EventTranslation::create_event(target, old_p, new_p, timestamp ) );
}

void TimeKeeper::onValueChanged(SimulatorComponent *target, int old_val, int new_val, unsigned long timestamp){
    Chrono* ch = game_object()->getComponent<Chrono>();
    if( ch != nullptr && ch->status_ == ChronoPlayStatus::FORWARD )
        this->insert_event( *EventValueChange::create_event(target, old_val, new_val, timestamp ) );
}

void TimeKeeper::onAnimationStateChanged(Animation *target, int old_status, int new_status, unsigned long timestamp){
    Chrono* ch = game_object()->getComponent<Chrono>();
    if( ch != nullptr && ch->status_ == ChronoPlayStatus::FORWARD )
        this->insert_event( *EventAnimationStateChanged::create_event(target, old_status, new_status, timestamp ) );
}

