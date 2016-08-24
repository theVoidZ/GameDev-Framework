#ifndef BEHAVIOR_H
#define BEHAVIOR_H

// c++-includes

// sfml-includes

// qt-includes

// user-includes
#include "kernel/component.h"

class Behavior : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        Behavior();
        ~Behavior();

        virtual void update(sf::Time dt);

    protected:
        //! Holds whether the behaviour is enabled or not.
        bool enabled = true;


    public:
        //!
        bool is_enabled();

};

#endif // BEHAVIOR_H
