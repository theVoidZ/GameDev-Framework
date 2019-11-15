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
#include "component.h"
#include "tracker_ptr.h"


namespace gdf {
namespace temporal {
class Chrono;
}

namespace kernel {

class Object;
class GameObject;
class Component;

}}

/*! The Garbage Collector does physically destroy objects only when it is requested by GameObject::destroy
 * However, it does not locate&destroy orphan object for example.
 * This is a stateLess (time) GC. Scene-Time and Deadlines are received every time
 */
class GarbageCollector : public gdf::kernel::Component
{
    public:
        GarbageCollector();
        virtual ~GarbageCollector();

    public:
        void init();

        // Clean
        void update(sf::Time dt);

        void bind(std::map< gdf::kernel::tracker_ptr<gdf::kernel::GameObject>, sf::Time>* go_junk_container,
                  std::map< gdf::kernel::tracker_ptr<gdf::kernel::Component> , sf::Time>* c_junk_container);


    protected:
        //! Object*: item to destroy
        //! unsigned long long: time when the object should be destroyed ( in microseconds ), may use sf::Time instead
        std::map< gdf::kernel::tracker_ptr<gdf::kernel::GameObject>, sf::Time>* junk_gameobjects = nullptr;
        std::map< gdf::kernel::tracker_ptr<gdf::kernel::Component>, sf::Time>* junk_component = nullptr;

        //! Time of the entity attached to this Garbage Collector is retrieved from the host's chrono component
        gdf::temporal::Chrono* ch;
};

#endif // GARBAGECOLLECTOR_H
