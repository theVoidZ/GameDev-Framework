#ifndef CHRONO_H
#define CHRONO_H

#include <SFML/System/Time.hpp>

#include <iostream>

#include "kernel/component.h"

class GameObject;

enum class ChronoPlayStatus{
    FORWARD,
    STOPPED,
    BACKWARD
};

class Chrono    : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        Chrono();
        ~Chrono();

        void init();
        void update(sf::Time dt);

    public:
        //! Lifetime of the component/gameobject,
        //! self relative referential of time ( do not account freeze time )
        sf::Time lifetime;

    private:
        // NOT USED YET
        //! Related to GameInfo ( it is not affected by any time manipulator )
        sf::Time absolute_time;

        //! Time of spawning in absolute time ( relative to the scene time )
        sf::Time spawn_time;

        //! Amount of time the component was time-frozen
        sf::Time freeze_time;

    public:
        ChronoPlayStatus status_;
};

#endif // CHRONO_H
