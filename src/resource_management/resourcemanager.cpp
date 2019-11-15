#include "resourcemanager.h"

unsigned long ResourceManager::local_instance_id_counter = 300;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager(){

}

void ResourceManager::verbose(){

    std::cout << FGREEN << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD <<"Resource manager content:" << RESET_BOLD << std::endl;

    for( auto it = _resources.begin(); it != _resources.end(); it++ ){
        if( !(*it).second->empty() ){

//            for( auto it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++ ){

//            }
        }

        if( (*it).second->operator[](0).expired() )
            continue;

        Resource* r = (*it).second->operator[](0).get();

//        r->verbose();
        std::cout << std::left <<std::setw(27) << boost::typeindex::type_id_runtime(*r).pretty_name() << "\tName: " << std::left << std::setw(14) << r->name_ << "\tid=" << std::right << std::setw(4) << r->id_ << " " <<  " count=" << std::setw(2);
        std::cout << (*it).second->operator[](0).tracker_count();
        if( (*it).second->size() > 1 ){
            std::cout << "," << (*it).second->operator[](1).tracker_count();
        }
        std::cout << "("<< duplicate_tracker_[r->id_]+1 << ")" << std::endl;
    }

    std::cout << "--------------------------------------------------------------------------------" << RESET << std::endl;

/*
    std::cout << FGREEN << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD <<"Resource manager content:" << RESET_BOLD << std::endl;

    for( auto it = resources.begin(); it != resources.end(); it++ ){
        if( (*it).second.expired() )
            continue;

        Resource* r = (*it).second.get();
        std::cout << std::left <<std::setw(27) << boost::typeindex::type_id_runtime(*r).pretty_name() << "\tName: " << std::left << std::setw(14) << r->name_ << "\tid=" << std::right << std::setw(4) << r->id_ << " " <<  " count=" << std::setw(2) << (*it).second.tracker_count()<< std::endl;
    }

    std::cout << "--------------------------------------------------------------------------------" << RESET << std::endl;
*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceManager::unload_resource(unsigned long id , bool force_unload){
    /*
    auto it = resources.find( id );

    if( it != resources.end() ){
        if( (*it).second.tracker_count() <= 1 || force_unload ){
            (*it).second.reset();
            it = resources.erase( it );

        }else{
            std::cout << FORANGE << BOLD << "Resource id:" << id << " (" << (*it).second.get()->name_ << ") is still in use" << RESET << std::endl;
        }
    }
    */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceManager::unload_unused_resources(){
    /*
    bool trigger_recursion;

    std::cout << FGREEN << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD << "Resource manager: cleaning process:" << RESET_BOLD << FRED << std::endl;

    clean_once_more:
    trigger_recursion = false;

    for( auto it = resources.begin(); it != resources.end(); ){
        if( (*it).second.expired() ){
            // Empty tracker
            it = resources.erase(it);
            std::cout << FORANGE << BOLD << "-cleaned:  " << RESET_BOLD << std::left << " [undefined/empty slot]." << RESET << std::endl;
        }else if( (*it).second.tracker_count() <= 1 ){
            // Used by more than one instance ( which is the resource manager )
            Resource* r = (*it).second.get();
            std::cout << FORANGE<< BOLD << "-cleaned:  " << RESET_BOLD << std::left <<std::setw(12) << boost::typeindex::type_id_runtime(*r).pretty_name() << "\tName: " << std::left << std::setw(12) << r->name_ << "\tid=" << std::right << std::setw(6) << r->id_ << RESET << std::endl;
            (*it).second.reset();
            it = resources.erase( it );
            trigger_recursion = true;
        }else{
            // Resource in use
            // Auto increased in other cases, but not here
            it++;
        }
    }

    if(trigger_recursion )
        goto clean_once_more;

    std::cout << FGREEN << "--------------------------------------------------------------------------------" << RESET << std::endl;
    */
}
