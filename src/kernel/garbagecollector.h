#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

// c++-includes
#include <map>

// sfml-includes
#include <SFML/System/Time.hpp>

// qt-includes
#include <iostream>
#include <string>

// user-includes
#include "kernel/component.h"

class Chrono;

namespace gdf {
namespace kernel {

class Object;
class GameObject;
class Component;

/*! NOTE: The Garbage Collector does physically destroy objects only when it is requested by GameObject::destroy
 * However, it does not locate&destroy orphan object for exmple.
 * This is a stateLess (time) GC. Scene-Time and Deadlines are received every time
 */
class GarbageCollector : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        GarbageCollector();
        virtual ~GarbageCollector();

    public:
        void init();
        void update(sf::Time dt);

//        void bind(std::map<Object*, unsigned long long>* junk_container);

    public:
        //! ttd: Time to die ( offset time )
        virtual void collect(Object* obj, sf::Time ttd);

        //! Perform cleaning
        virtual void clean(sf::Time dt);

    protected:
        //! Object*: item to destroy
        //! unsigned long long: time when the object should be destroyed ( in microseconds ), may use sf::Time instead
        std::map<Object*, unsigned long long> junk_objects;

        //! Time of the entity attached to this Garbage Collector is retrieved from the host's chrono component
        Chrono* ch;
};

}}

#endif // GARBAGECOLLECTOR_H
