#ifndef SIMULATORCOMPONENT_H
#define SIMULATORCOMPONENT_H

#include "Core/System/monobehavior.h"

class Chrono;

class SimulatorComponent : public MonoBehavior
{
    Q_OBJECT
    public:
        SimulatorComponent();

    public:
        void init();
        void update(sf::Time dt);

    public:
        Chrono* ch;

        sf::Time current = sf::Time::Zero;
        int steps = 0;
        sf::Time t;
};

#endif // SIMULATORCOMPONENT_H
