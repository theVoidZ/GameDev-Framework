#include "componentcontainer.h"

#include "gameinfo.h"
#include "kernelrules.h"
#include "component.h"
#include "componentfactory.h"
namespace gdf {
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentContainer::ComponentContainer(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
ComponentContainer::~ComponentContainer(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentContainer::register_component(const std::string& name, Component* (* ctor)(void)){
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component( name, ctor );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentContainer::make_linking(tracker_ptr<Component> comp_holder, std::list< tracker_ptr<Component> >* lc){
    // For every component x of LC
    // - set comp as their child
    // - set x as a parent of comp.

    if( !comp_holder.expired() ){
        all_items.push_back( comp_holder );

        for( auto it = lc->begin(); it != lc->end(); it++ ){
            if( !(*it).expired() ){
                // Perform two-directional linking
                comp_holder.get()->parents_components_.push_back( *it );
                (*it).get()->children_components_.push_back( comp_holder );
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ComponentContainer::can_attach_component(ComponentContainer* host, Component *comp, std::list< tracker_ptr<Component> > *lc ) const{

    // Host Dependency check
    bool host_limitation_rule = true;

    boost::typeindex::type_index t_comp = boost::typeindex::type_id_runtime(*comp);

    // Locate the rule
    for( auto it2 : GameInfo::game_info->kernel()->hostobject_limitation_rules){
        if( t_comp == it2.first ){ // find rule entry

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            /// WARNING: Polymorphism ? not included
            if (std::any_of(it2.second.cbegin(), it2.second.cend(),
                        [this, host](boost::typeindex::type_index dependency){
                             if( boost::typeindex::type_id_runtime(*host) == dependency ){
                                 return true;
                             }
                        } )
            ){
                // Mark dependency check as success
                host_limitation_rule = true;
            }else{
                std::cout << FRED << "Requirements not met for: " << BOLD << it2.first.pretty_name() << std::endl;
                std::cout << RESET_BOLD << "\tREQUIRES to be on top of:\t" << BOLD << FRED;
                for( boost::typeindex::type_index str : it2.second ){
                    std::cout << str.pretty_name() << ", " ;
                }
                std::cout << RESET << std::endl;
                host_limitation_rule = false;
            }
            break;
        }
    }

    //--------------------------------------------------------------------------------------------------------------
    // Components Dependency check
    bool comp_dependency_result = true;

    // Locate the rule
    for( auto it2 : GameInfo::game_info->kernel()->components_dependency_rules){
        if( t_comp == it2.first ){

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::all_of(it2.second.cbegin(), it2.second.cend(),
                        [this, lc, t_comp](boost::typeindex::type_index dependency){
                            for( tracker_ptr<Component> c : all_items ){
                                if( !c.expired() ){
                                    if( boost::typeindex::type_id_runtime(*(c.get()) ) == dependency ){
                                        tracker_ptr<Component> tr(c);
                                        lc->push_back( tr );
                                        return true;
                                    }
                                }
                            }
                            return false;
                        } )
            ){
                // Mark dependency check as success
                comp_dependency_result = true;
            }else{
                std::cout << FRED << "Requirements not met for: " << BOLD << it2.first.pretty_name() << std::endl;
                std::cout << RESET_BOLD << "\tREQUIRES:\t" << BOLD << FRED;
                for( auto str : it2.second ){
                    std::cout << str.pretty_name() << ", " ;
                }
                std::cout << RESET << std::endl;
                comp_dependency_result = false;
            }
            break;
        }
    }

    //--------------------------------------------------------------------------------------------------------------
    // Singleton check
    bool cardinality_result = true;
    // Locate rule
    for( auto it : GameInfo::game_info->kernel()->components_cardinality_rules){
        if( t_comp ==  it.first ){ // found

            unsigned char instance_counter = 0;

            /// WARNING: sub-classes are not considered
            for( tracker_ptr<Component> c : all_items ){
                if( !c.expired() ){

                    if( boost::typeindex::type_id_runtime(*(c.get())) == t_comp){
                        instance_counter++;
                    }
                }
            }

            if( instance_counter >= it.second ){
                // Singleton check success
                std::cout << FORANGE << BOLD << "Attempting to add a component of " << t_comp.pretty_name() << ", max instance " << RESET_BOLD << ITALIC << (int)it.second << RESET << std::endl;
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
