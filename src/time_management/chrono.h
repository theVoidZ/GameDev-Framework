#ifndef CHRONO_H
#define CHRONO_H

#include <SFML/System/Time.hpp>

#include <iostream>

#include "component.h"

namespace gdf {
namespace temporal {

enum class ChronoPlayStatus{
    FORWARD,
    STOPPED,
    BACKWARD
};

class Chrono    : public gdf::kernel::Component
{
    public:
        Chrono();
        ~Chrono();

        void init();
        void update(sf::Time dt);

    public:
        //! NOTE: SUGG: Implement here till new order.
        void rewind();
        void forward();
        void freeze();

    public:
        //! Lifetime of the component/gameobject,
        //! self relative referential of time ( do not account freeze time )
        sf::Time lifetime_ = sf::Time::Zero;

        // NOT USED YET
        //! Time of spawning in referential TLine
        //! OBSOLETE:
        sf::Time spawn_time_ = sf::Time::Zero;

        //! OBSOLETE: It is the job of the TimeKeeper.
        //! Amount of time the component was time-frozen

        // Play speed
        float speed_factor_ = 1.0f;

        // Manually input. Absolute time is replaced by this
        //! OBSOLETE: actually not used ( declared in between scene and gameinfo only )
        ChronoPlayStatus status_ = ChronoPlayStatus::FORWARD;

    public:
        void set_lifetime(sf::Time lifetime_);
        void set_spawn_time( sf::Time spawn_time );
        void set_speed_factor(float speed_fac);
        void set_status(gdf::temporal::ChronoPlayStatus status);

};

}}

#endif // CHRONO_H
