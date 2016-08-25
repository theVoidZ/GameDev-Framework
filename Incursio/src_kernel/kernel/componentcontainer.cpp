#include "componentcontainer.h"

#include "kernel/component.h"
#include "kernel/kernelrules.h"

namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentContainer::ComponentContainer(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentContainer::~ComponentContainer(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentContainer::make_linking(gdf::kernel::Component* comp, std::list<gdf::kernel::Component*>* lc){
    // For every component x of LC
    // - set comp as their child
    // - set x as a parent of comp.
    for( auto it = lc->begin(); it != lc->end(); it++ ){
        comp->parents_components_.push_back( *it );
        (*it)->children_components_.push_back(comp);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComponentContainer::can_attach_component(ComponentContainer* host, gdf::kernel::Component *comp, std::list< gdf::kernel::Component*> *lc ) const{
    return true;
/*
    // Or may be inherits ?
    bool host_limitation_rule = true;

    boost::typeindex::type_index t;

//    // Host Dependency check
    for( auto it2 : KernelRules::kernel->hostobject_limitation_rules){
        if( comp->inherits( it2.first.c_str() ) ){ // find
        // Rule located

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::any_of(it2.second.cbegin(), it2.second.cend(),
                        [this, host](std::string dependency){
                             //! FIXME: TO be implemented ( take in consideration ) inheritance...
                             boost::typeindex::type_index t1 = boost::typeindex::type_id_runtime(*host);
                             if( t1.pretty_name() == dependency ){
                                 return true;
                             }
                        } )
            ){
                // Mark dependency check as success
                host_limitation_rule = true;
            }else{
                std::cout << FRED << "Requirements not met for: " << BOLD << it2.first << std::endl;
                std::cout << RESET_BOLD << "\tREQUIRES to be on top of:\t" << BOLD << FRED;
                for( std::string str : it2.second ){
                    std::cout << str << ", " ;
                }
                std::cout << RESET << std::endl;
                host_limitation_rule = false;
            }
            break;
        }
    }


    // Or may be inherits ?
    bool comp_dependency_result = true;

    // Components Dependency check
    for( auto it2 : KernelRules::kernel->components_dependency_rules){
        if( comp->inherits( it2.first.c_str() ) ){ // find
        // Rule located

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::all_of(it2.second.cbegin(), it2.second.cend(),
                        [this, lc](std::string dependency){
                            for( gdf::kernel::Component* c : all_items ){
                                if( c->inherits(dependency.c_str()) ){
                                    lc->push_back( c );
                                    return true;
                                }
                            }
                            return false;
                        } )
            ){
                // Mark dependency check as success
                comp_dependency_result = true;
            }else{
                std::cout << FRED << "Requirements not met for: " << BOLD << it2.first << std::endl;
                std::cout << RESET_BOLD << "\tREQUIRES:\t" << BOLD << FRED;
                for( std::string str : it2.second ){
                    std::cout << str << ", " ;
                }
                std::cout << RESET << std::endl;
                comp_dependency_result = false;
            }
            break;
        }
    }

    // Singleton check
    bool cardinality_result = true;
    for( auto it : KernelRules::kernel->components_cardinality_rules){
        // Rule located
        if( comp->inherits( it.first.c_str() ) ){ // find

            // Singleton check tells that, only one instance of that type can be instantiated within the same Object.
            if (std::any_of(all_items.cbegin(), all_items.cend(),
                        [comp](gdf::kernel::Component* c){
                            return comp->inherits( c->metaObject()->className() );
                        } )
            ){
                // Singleton check success
                std::cout << FORANGE << BOLD << "Attempting to add a second component of " << comp->metaObject()->className() << " while it is suposed to be " << RESET_BOLD << ITALIC << "'singleton'" << RESET << std::endl;
                cardinality_result = false;
            }else{
                // No requirement listed for comp.
                cardinality_result = true;
            }

            break;
        }
    }

    // Return the final result
    return host_limitation_rule && cardinality_result && comp_dependency_result;
*/
}

}}
