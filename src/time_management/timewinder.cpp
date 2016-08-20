#include "timewinder.h"

#include "kernel/gameobject.h"
#include "time_management/timekeeper.h"
#include "time_management/chrono.h"

#include "kernel/object.h"

TimeWinder::TimeWinder()
{

}

void TimeWinder::init(){

}

void TimeWinder::watch(gdf::kernel::GameObject *go){
//    std::cout << "*** " << go->name() << " is add to the watch_list of the TimeWinder *** " << std::endl;
    //! NOTE: SUB GAME_OBJECT ARE AUTOMATICALLY AFFECTED.
    //! FIXME:
    watched_list.push_back(go);
}

void TimeWinder::verbose(){
    // Unite all stacks of TimerKeepers of the Watched list.
    // NOW: print a separate list for each item
    for( gdf::kernel::GameObject* go : watched_list){
        TimeKeeper* tk = go->getComponent<TimeKeeper>();
        if( tk ){
            tk->verbose();
        }
    }
}

void TimeWinder::update(sf::Time dt){
    for( const gdf::kernel::GameObject* go : watched_list ){
        TimeKeeper* tk = go->getComponent<TimeKeeper>();
        if( tk != nullptr ){
            // When rewinding
            if( !tk->past_events.empty() ){
                Event& ev = *( tk->past_events.top() );
                gdf::kernel::Component* target = dynamic_cast<gdf::kernel::Component*> ( ev.target );

                Chrono* ch = dynamic_cast<gdf::kernel::Component*>( ev.target )->game_object()->getComponent<Chrono>();
                if( ch != nullptr ){
                    if( ch->status_ == ChronoPlayStatus::BACKWARD ){
                        sf::Time current_target_life_time = ch->lifetime;

                        // Current game object life time is decreasing
                        if( current_target_life_time.asMilliseconds() <= ev.timestamp ){
                            tk->past_events.pop();
                            ev.verbose();
                            ev.reverse_exec();
                        }
                    }
                 }
            }
        }
    }
}
