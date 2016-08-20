#include "garbagecollector.h"

#include "time_management/chrono.h"
#include "kernel/hierarchicalcontainer.h"

namespace gdf {
namespace kernel{

GarbageCollector::GarbageCollector()
{

}

GarbageCollector::~GarbageCollector(){
    //! BUG: May cause error
    // Destroy all itemson the list
//    for( auto it = junk_objects.begin(); it != junk_objects.end(); ){
//        delete (*it).first;
//        it = junk_objects.erase(it);
//    }
}

void GarbageCollector::init(){
    // REQUIRES CHRONO TO BE INSTANTIATED
    ch = host_object_->getComponent<Chrono>();
}

void GarbageCollector::update(sf::Time dt){
    clean(dt);
}

void GarbageCollector::collect(Object *obj, sf::Time ttd){
    auto it = junk_objects.find(obj);
    if( it == junk_objects.end() ){

        // insert new item if it does not exist
        junk_objects[obj] = (ch->lifetime + ttd).asMicroseconds();
    }

    // If it exist, think about updating the time ?!
}

void GarbageCollector::clean(sf::Time dt){
    //! WARNING: MUST BE ADAPTED WITH the time_management module.
    // Check for spoiled items
    // if current_time >= ttd
    for( auto it = junk_objects.begin(); it != junk_objects.end(); ){
        if ( ch->lifetime.asMicroseconds() >= (*it).second ){
            //! NOTE: Destroy the object
            std::cout << "Object DESTROYED ["<< (*it).first->metaObject()->className()<<"]\tafter\t" << ch->lifetime.asMilliseconds() << " ms" << std::endl;

            delete (*it).first;

            // destroy the entry of the map and point to the next item or std::end
            it = junk_objects.erase(it);

        }else{
            it++;
        }
    }
}

}}
