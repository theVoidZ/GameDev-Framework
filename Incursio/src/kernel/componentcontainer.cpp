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

    // Host Dependency check
    bool host_limitation_rule = true;

    boost::typeindex::type_index t_comp = boost::typeindex::type_id_runtime(*comp);

    // Locate the rule
    for( auto it2 : KernelRules::kernel->hostobject_limitation_rules){
        if( t_comp.pretty_name() == it2.first ){ // find rule entry


            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::any_of(it2.second.cbegin(), it2.second.cend(),
                        [this, host](std::string dependency){
                             boost::typeindex::type_index t_host = boost::typeindex::type_id_runtime(*host);
                             if( t_host.pretty_name() == dependency ){
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



    // Components Dependency check
    bool comp_dependency_result = true;

    // Locate the rule
    for( auto it2 : KernelRules::kernel->components_dependency_rules){
        //! INHERITANCE ISSUE ( checking only same class ).
        if( t_comp.pretty_name() == it2.first ){

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::all_of(it2.second.cbegin(), it2.second.cend(),
                        [this, lc, t_comp](std::string dependency){
                            for( gdf::kernel::Component* c : all_items ){
                                boost::typeindex::type_index t_c = boost::typeindex::type_id_runtime(*c);
                                if( t_c.pretty_name() == dependency ){
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
    // Locate rule
    for( auto it : KernelRules::kernel->components_cardinality_rules){
        if( t_comp.pretty_name() ==  it.first ){ // find

            // Singleton check tells that, only one instance of that type can be instantiated within the same Object.
            if (std::any_of(all_items.cbegin(), all_items.cend(),
                        [t_comp](gdf::kernel::Component* c){
                            boost::typeindex::type_index t_c = boost::typeindex::type_id_runtime(*c);

                            return t_comp.pretty_name() == t_c.pretty_name() ;
                        } )
            ){
                // Singleton check success
                std::cout << FORANGE << BOLD << "Attempting to add a second component of " << t_comp.pretty_name() << " while it is suposed to be " << RESET_BOLD << ITALIC << "'singleton'" << RESET << std::endl;
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
}

}}
