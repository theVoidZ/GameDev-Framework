#include "kernelrules.h"

#include "chrono.h"
#include "transform.h"
#include "hierarchy.h"
#include "gameobject.h"
#include "camera.h"

namespace gdf{
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
KernelRules::KernelRules(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
KernelRules::~KernelRules(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::init(){
    //! NOTE: MUST RESPECT NAMESPACES
    // create rules here
    // using a graphic way ( graph of dependencies ? )

    //!
    set_type_cardinality( KernelRules::type_id_with_cvr<gdf::kernel::Transform>() , 1);
    set_type_cardinality( KernelRules::type_id_with_cvr<gdf::kernel::Hierarchy>() , 1);

    //!
    create_rule( KernelRules::type_id_with_cvr<gdf::kernel::Transform>(), KernelRules::type_id_with_cvr<gdf::kernel::Hierarchy>() );

    //!
    create_host_limitation_rule( KernelRules::type_id_with_cvr<gdf::kernel::Transform>(), KernelRules::type_id_with_cvr<gdf::kernel::GameObject>());
    create_host_limitation_rule( KernelRules::type_id_with_cvr<gdf::kernel::Hierarchy>(), KernelRules::type_id_with_cvr<gdf::kernel::GameObject>());
    create_host_limitation_rule( KernelRules::type_id_with_cvr<gdf::kernel::Camera>(), KernelRules::type_id_with_cvr<gdf::kernel::GameObject>());

    // User rules
    on_init();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::on_init(){
//    set_type_cardinality( KernelRules::type_id_with_cvr<ArduinoController>() , 1);
//    create_rule( KernelRules::type_id_with_cvr<gdf::kernel::Transform>(), KernelRules::type_id_with_cvr<gdf::kernel::Hierarchy>() );

}


void KernelRules::create_rule(boost::typeindex::type_index dependent, boost::typeindex::type_index depended){
    auto it = components_dependency_rules.find( dependent );
    if( it != components_dependency_rules.end() ){
        if( std::none_of( (*it).second.begin(),
                         (*it).second.end(),
                         [&](boost::typeindex::type_index item){ return item == depended;}
                         ) ){
            // Rule does not exist
            components_dependency_rules[ (*it).first ].push_back( depended );
        }
    }else{
        components_dependency_rules[dependent] = {depended};
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::create_host_limitation_rule(boost::typeindex::type_index dependent, boost::typeindex::type_index host){
    auto it = hostobject_limitation_rules.find( dependent );
    if( it != hostobject_limitation_rules.end() ){
        if( std::none_of( (*it).second.begin(),
                         (*it).second.end(),
                         [&](boost::typeindex::type_index item){ return item == host;}
                         ) )
        {
            // Rule does not exist
            hostobject_limitation_rules[ (*it).first ].push_back( host );
        }
    }else{
        hostobject_limitation_rules[dependent] = {host};
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::set_type_cardinality(boost::typeindex::type_index t, unsigned char max){
    components_cardinality_rules[t] = max;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void KernelRules::show_rules(){
    std::cout << FGREEN << "-------------------------------------------" << std::endl;
    std::cout << BOLD << "#Singletons-TYPED:" << RESET_BOLD << std::endl;
    for( auto it : components_cardinality_rules ){
        std::cout << std::left << std::setw(30) << it.first.pretty_name() << (unsigned int)(it.second) << std::endl;
    }
    std::cout << RESET_BOLD << std::endl;

    std::cout << BOLD << "#Requirements: [Components]-TYPED" << RESET_BOLD << std::endl;
    for( auto it : components_dependency_rules ){
        std::cout << std::left << std::setw(30) << it.first << std::left << std::setw(15) << "'requires'";
        for( auto str : it.second ){
            std::cout << str.pretty_name() << ", " ;
        }
        std::cout << std::endl;
    }
    std::cout << RESET_BOLD << std::endl;

    std::cout << BOLD << "#Requirements: [Host Objects]-TYPED" << RESET_BOLD << std::endl;
    for( auto it : hostobject_limitation_rules ){
        std::cout << std::left << std::setw(30) << it.first.pretty_name() << std::left << std::setw(15) << "'requires'";
        for( boost::typeindex::type_index str : it.second ){
            std::cout << str.pretty_name() << ", " ;
        }
        std::cout << std::endl;
    }
    std::cout << RESET_BOLD << std::endl;

    std::cout << "-------------------------------------------" << RESET << std::endl;
}



}}
