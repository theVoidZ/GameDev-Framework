#ifndef TIMEWINDER_H
#define TIMEWINDER_H

#include <SFML/System/Time.hpp>

#include <vector>

#include "kernel/component.h"

class GameObject;

class TimeWinder : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        TimeWinder();

    public:
        void init();

    public:
        void watch( gdf::kernel::GameObject* go );
        void verbose(); // rewind in debug mode

        void update( sf::Time dt );
    public:
        std::vector<gdf::kernel::GameObject*> watched_list;
        float rewind_factor = 1.f;
};

#endif // TIMEWINDER_H
