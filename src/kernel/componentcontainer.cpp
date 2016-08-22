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
bool ComponentContainer::can_attach_component(gdf::kernel::Component *comp, std::list< gdf::kernel::Component*> *lc ) const{

    // Or may be inherits ?
    bool dependency_result = true;

    // Dependency check
    for( auto it2 : KernelRules::kernel->dependencies_rules){

        /// QT: comp->inherits( it2.first.c_str() )
        if( comp->inherits( it2.first.c_str() ) ){ // find
        // Rule located

            // Check the second part of the rule
            // i.e For each item of the rule, there must be at least one component of item's rule type or its subclass. ( using all_of )
            if (std::all_of(it2.second.cbegin(), it2.second.cend(),
                        [this, lc](std::string dependency){
                            for( gdf::kernel::Component* c : all_items ){
                                /// QT: c->inherits(dependency.c_str())
                                if( c->inherits(dependency.c_str()) ){
                                    lc->push_back( c );
                                    return true;
                                }
                            }
                            return false;
                        } )
            ){
                // Mark dependency check as success
                dependency_result = true;
            }else{
                std::cout << FRED << "Requirements not met for: " << BOLD << it2.first << std::endl;
                std::cout << RESET_BOLD << "\tREQUIRES:\t" << BOLD << FRED;
                for( std::string str : it2.second ){
                    std::cout << str << ", " ;
                }
                std::cout << RESET << std::endl;
                dependency_result = false;
            }
            break;
        }
    }

    // Singleton check
    bool singleton_result = true;
    for( auto it : KernelRules::kernel->singletons_rules){
        // Rule located
        /// QT: comp->inherits( it.first.c_str() )
        if( comp->inherits( it.first.c_str() ) ){ // find

            // Singleton check tells that, only one instance of that type can be instantiated within the same Object.
            if (std::any_of(all_items.cbegin(), all_items.cend(),
                        [comp](gdf::kernel::Component* c){
                            /// QT: comp->inherits( c->metaObject()->className() );
                            return comp->inherits( c->metaObject()->className() );
                        } )
            ){
                // Singleton check success
                /// QT: comp->metaObject()->className()
                std::cout << FORANGE << BOLD << "Attempting to add a second component of " << comp->metaObject()->className() << " while it is suposed to be " << RESET_BOLD << ITALIC << "'singleton'" << RESET << std::endl;
                singleton_result = false;
            }else{
                // No requirement listed for comp.
                singleton_result = true;
            }

            break;
        }
    }

    // Return the final result
    return singleton_result && dependency_result;

}

}}
