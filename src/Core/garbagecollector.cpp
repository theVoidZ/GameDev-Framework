#include "garbagecollector.h"

#include "chrono.h"
#include "tracker_ptr.h"

#include "gameobject.h"

GarbageCollector::GarbageCollector()
{

}

GarbageCollector::~GarbageCollector(){
// Destroy all items on the list
//    for( auto it = junk_objects.begin(); it != junk_objects.end(); ){
//        delete (*it).first;
//        it = junk_objects.erase(it);
//    }
}

void GarbageCollector::init(){
    // get time referential
    gdf::kernel::ComponentContainer* cc = host_object<gdf::kernel::ComponentContainer>();
    if( cc != nullptr ){
        // The component is a gameobject component
        if( dynamic_cast<gdf::kernel::GameObject*>(cc) != nullptr ){
            gdf::kernel::GameObject* go = dynamic_cast<gdf::kernel::GameObject*>(cc);
            if( go->scene() != nullptr ) {
                if( !go->scene()->chrono().expired() ) {
                    ch = go->scene()->chrono().get();
                }
            }
            // The component is a scene component
        }else{
            ch = host_object_->get_component<gdf::temporal::Chrono>();
        }
    }

    // establish auto-bindr
}

void GarbageCollector::update(sf::Time dt){
    if( ch->status_ == gdf::temporal::ChronoPlayStatus::FORWARD ) {

        //!NOTE: Destroy components first
        if( junk_component != nullptr ) {

            //! WARNING: MUST BE ADAPTED WITH the time_management module.
            // Check for spoiled items
            // if current_time >= ttd
            for( auto tr : *junk_component ) {
                if( !tr.first.expired() ) {
                    if( ch->lifetime_ >= tr.second ) {
                        //! NOTE: Destroy the object
                        std::cout << BOLD << BRED << FYELLOW << "[GB] Component DESTROYED [" << boost::typeindex::type_id_runtime(*(tr.first.get())).pretty_name() << "]\tafter\t" << ch->lifetime_.asMilliseconds() << " ms" << RESET << std::endl;
                        gdf::kernel::tracker_ptr<gdf::kernel::Component> tt = tr.first;
                        tt.reset();

                    }
                }
            }
            for( auto it = junk_component->begin(); it != junk_component->end(); it++ ) {
                if( it->first.expired() ) {
                    junk_component->erase(it);
                }
            }
        }


        //!NOTE: Destroy gameobject in second
        if( junk_gameobjects != nullptr ) {
            //! WARNING: MUST BE ADAPTED WITH the time_management module.
            // Check for spoiled items
            // if current_time >= ttd
            for( auto m_it : *junk_gameobjects ) {
                if( !m_it.first.expired() ) {
                    if( ch->lifetime_ >= m_it.second ) {
                        //! NOTE: Destroy the object
                        std::cout << BOLD << BRED << FYELLOW << "[GB] GameObject " << m_it.first.get()->name() << " DESTROYED [" << boost::typeindex::type_id_runtime(*(m_it.first.get())).pretty_name() << "]\tafter\t" << ch->lifetime_.asMilliseconds() << " ms" << RESET << std::endl;
                        gdf::kernel::tracker_ptr<gdf::kernel::GameObject> tt = m_it.first;
                        tt.reset();
                    }
                }

                for( auto it = junk_gameobjects->begin(); it != junk_gameobjects->end(); it++ ) {
                    if( it->first.expired() ) {
                        junk_gameobjects->erase(it);
                    }
                }
            }

        }
    }else if( ch->status_ == gdf::temporal::ChronoPlayStatus::BACKWARD){

        //!NOTE: Destroy components first
        if( junk_component != nullptr ) {

            //! WARNING: MUST BE ADAPTED WITH the time_management module.
            // Check for spoiled items
            // if current_time >= ttd
            for( auto tr : *junk_component ) {
                if( !tr.first.expired() ) {
                    if( ch->lifetime_ <= tr.second ) {
                        //! NOTE: Destroy the object
                        std::cout << BOLD << FRED << BYELLOW << "[GB] Component DESTROYED [" << boost::typeindex::type_id_runtime(*(tr.first.get())).pretty_name() << "]\tafter\t" << ch->lifetime_.asMilliseconds() << " ms" << RESET << std::endl;
                        gdf::kernel::tracker_ptr<gdf::kernel::Component> tt = tr.first;
                        tt.reset();
                    }
                }
            }
            for( auto it = junk_component->begin(); it != junk_component->end(); it++ ) {
                if( it->first.expired() ) {
                    junk_component->erase(it);
                }
            }
        }


        //!NOTE: Destroy gameobject in second
        if( junk_gameobjects != nullptr ) {
            //! WARNING: MUST BE ADAPTED WITH the time_management module.
            // Check for spoiled items
            // if current_time >= ttd
            for( auto m_it : *junk_gameobjects ) {
                if( !m_it.first.expired() ) {
                    if( ch->lifetime_ <= m_it.second ) {
                        //! NOTE: Destroy the object
                        std::cout << BOLD << FRED << BYELLOW << "[GB] GameObject " << m_it.first.get()->name() << " DESTROYED [" << boost::typeindex::type_id_runtime(*(m_it.first.get())).pretty_name() << "]\tafter\t" << ch->lifetime_.asMilliseconds() << " ms" << RESET << std::endl;
                        gdf::kernel::tracker_ptr<gdf::kernel::GameObject> tt = m_it.first;
                        tt.reset();
                    }
                }

                for( auto it = junk_gameobjects->begin(); it != junk_gameobjects->end(); it++ ) {
                    if( it->first.expired() ) {
                        junk_gameobjects->erase(it);
                    }
                }
            }

        }
    }

}

void GarbageCollector::bind(std::map<gdf::kernel::tracker_ptr<gdf::kernel::GameObject>, sf::Time> *go_junk_container,
                            std::map<gdf::kernel::tracker_ptr<gdf::kernel::Component> , sf::Time> *c_junk_container){
    junk_gameobjects = go_junk_container;
    junk_component = c_junk_container;
}
