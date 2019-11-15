#include "componentfactory.h"

#include "component.h"

#include "terminal_colors.h"

namespace gdf {
namespace kernel {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentFactory::ComponentFactory()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentFactory::~ComponentFactory()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentFactory::init(){


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentFactory::verbose() const{
    std::cout << FGREEN << BOLD << "Registered items (&ctor):" << std::endl;
    std::cout << FGREEN << BOLD << "---------------------------" << std::endl;

    std::cout << RESET_BOLD;
    for( auto it : factory_map ){
        std::cout << "&ctor →\t" << it.first << std::endl;
    }
    std::cout << BOLD << "---------------------------" ;

    std::cout << RESET << std::endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentFactory::register_component(std::string component_name, Component* (*ctor)(void) ){
    auto it = factory_map.find(component_name);
    if( it == factory_map.end() ){
        factory_map[component_name] = ctor;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Component* ComponentFactory::get(std::string component_name) const{
    auto it = factory_map.find(component_name);
    if( it != factory_map.end() ){
        return ((*it).second)();
    }else{
//        std::cout << BOLD << FRED << "&cotr '" << component_name << "' does not exist." << std::endl;
        return nullptr;
    }
}

}}
