#include "kernelrules.h"

#include "Core/Utilities/terminal_colors.h"

namespace gdf{
namespace kernel{

KernelRules* KernelRules::kernel = nullptr;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
KernelRules::KernelRules(){
    if( kernel == nullptr ){
        kernel = this;
    }else if( kernel != this ){
        delete kernel;
        kernel = this;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
KernelRules::~KernelRules(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::init(){
    //! NOTE: MUST RESPECT NAMESPACES
    // create rules here
    // using a graphic way ( graph of dependencies ? )
    make_singleton("gdf::kernel::Hierarchy");
    make_singleton("ArduinoTest");
    make_singleton("TimeKeeper");
    make_singleton("GarbageCollector");
    make_singleton("ResourceManager");
    make_singleton("TimeWinder");
    make_singleton("Chrono");

    create_rule("Transform", "gdf::kernel::Hierarchy" );
    create_rule("VelocityDef", "gdf::kernel::Hierarchy" );
    create_rule("VelocityDef", "Transform" );
    create_rule("ArduinoTest", "gdf::kernel::Hierarchy");

    create_rule("TimeKeeper", "Chrono");
    create_rule("GarbageCollector", "Chrono");

    create_host_limitation_rule("GarbageCollector", "TestCaseScene");
    create_host_limitation_rule("GarbageCollector", "TestCaseGameInfo");
    create_host_limitation_rule("gdf::kernel::Hierarchy", "gdf::kernel::GameObject");
    create_host_limitation_rule("ArduinoTest", "gdf::kernel::GameObject");


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::on_init(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::create_rule(std::string dependent, std::string depended){
    auto it = components_dependency_rules.find( dependent );
    if( it != components_dependency_rules.end() ){
        if( std::none_of( (*it).second.begin(),
                         (*it).second.end(),
                         [&](std::string item){ return item == depended;}
                         ) ){
            // Rule does not exist
            components_dependency_rules[ (*it).first ].push_back( depended );
        }
    }else{
        components_dependency_rules[dependent] = {depended};
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::create_host_limitation_rule(std::string dependent, std::string host){
    auto it = hostobject_limitation_rules.find( dependent );
    if( it != hostobject_limitation_rules.end() ){
        if( std::none_of( (*it).second.begin(),
                         (*it).second.end(),
                         [&](std::string item){ return item == host;}
                         ) ){
            // Rule does not exist
            hostobject_limitation_rules[ (*it).first ].push_back( host );
        }
    }else{
        hostobject_limitation_rules[dependent] = {host};
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::make_singleton(std::string target){
    components_cardinality_rules[target] = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::show_rules(){
    std::cout << FGREEN << "-------------------------------------------" << std::endl;
    std::cout << BOLD << "#Singletons:" << RESET_BOLD << std::endl;
    for( auto it : components_cardinality_rules ){
        std::cout << std::left << std::setw(30) << it.first << 1 << std::endl;
    }

    std::cout << BOLD << "#Requirements: [Components]" << RESET_BOLD << std::endl;
    for( auto it : components_dependency_rules ){
        std::cout << std::left << std::setw(30) << it.first << std::left << std::setw(15) << "'requires'";
        for( std::string str : it.second ){
            std::cout << str << ", " ;
        }
        std::cout << std::endl;
    }
    std::cout << BOLD << "#Requirements: [Host Objects]" << RESET_BOLD << std::endl;
    for( auto it : hostobject_limitation_rules ){
        std::cout << std::left << std::setw(30) << it.first << std::left << std::setw(15) << "'requires'";
        for( std::string str : it.second ){
            std::cout << str << ", " ;
        }
        std::cout << std::endl;
    }

    std::cout << "-------------------------------------------" << RESET << std::endl;
}

}}
