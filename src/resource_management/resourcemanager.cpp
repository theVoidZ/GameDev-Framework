#include "resourcemanager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager(){

}

void ResourceManager::verbose(){
    std::cout << FGREEN << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD <<"Resource manager content:" << RESET_BOLD << std::endl;

    for( auto it = resources.begin(); it != resources.end(); it++ ){
        Resource* r = (*it).second.get();
        std::cout << std::left <<std::setw(12) << r->metaObject()->className() << "\tName: " << std::left << std::setw(12) << r->name_ << "\tid=" << std::right << std::setw(6) << r->id_ << "  " << "shared = "<< ( r->is_shared == 1 ? "true" : "false") << "  count = " << std::setw(3) << (*it).second.use_count()<< std::endl;
    }

    std::cout << "--------------------------------------------------------------------------------" << RESET << std::endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceManager::unload_resource(unsigned long id ){

    auto it = resources.find( id );

    if( it != resources.end() ){
        if( !(*it).second.unique() ){
            std::cout << "ResourceManager::unload_resource: Cant unload the resource, because it is still in-use, ref.cout="<< (*it).second.use_count() << std::endl;
        }else{
            (*it).second.reset();
            it = resources.erase( it );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ResourceManager::unload_unused_resources(){
    std::cout << FGREEN << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << BOLD << "Resource manager: cleaning process:" << RESET_BOLD << FRED << std::endl;

    for( auto it = resources.begin(); it != resources.end(); ){
        if( (*it).second.unique() && (*it).second->is_shared ){
            Resource* r = (*it).second.get();
            std::cout << "-cleaned:  " << std::left <<std::setw(12) << r->metaObject()->className() << "\tName: " << std::left << std::setw(12) << r->name_ << "\tid=" << std::right << std::setw(6) << r->id_ << "  " << "shared = "<< ( r->is_shared == 1 ? "true" : "false") << std::endl;
            (*it).second.reset();
            it = resources.erase( it );
        }else{
            it++;
        }
    }
    std::cout << FGREEN << "--------------------------------------------------------------------------------" << RESET << std::endl;
}
