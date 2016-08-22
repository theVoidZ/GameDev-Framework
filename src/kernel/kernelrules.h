#ifndef KERNELRULES_H
#define KERNELRULES_H

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <list>
#include <algorithm>

namespace gdf{
namespace kernel{

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The KernelRules class defines a set of rules in order to check the satisfiability of the add
/// and the remove actions.
///
/// It is mainly used with \a ComponentContainer::addComponent and \a GameObject::destroy in order to
/// check whether these actions can be performed.
///
/// Since, the ComponentContainer defines a dependency relationship between components, whenever
/// addComponent is invoked on \a T ( template method ). A checking process must be performed in order to
/// verify the satisfiability of the 'T rule'.
///
/// Suppose we have:
/// \code
/// //kernelrules
/// create_rule("TimeWinder", "Chrono");
/// create_rule("TimeWinder", "Transform");
/// create_rule("TimeWinder", "TimeKeeper");
/// create_rule("Renderer", "Transform");
///
/// \endcode
///
/// This generates the following rules: ( →  means: requires )
///
/// \f$ Renderer → Transform \f$
///
/// \f$ TimeWinder → Transform, TimeKeeper, Chrono \f$
///
/// Thus, in order to add a TimeWinder Component on a given GameObject, the game object must already have
/// all the listed (and required) components of the "TimeWinder" rule.
///
/// Otherwise, the component will not be created
///
/// Same case for the destroy action, but condition check is applied in a reverse way. Means that you cannot remove
/// a component if another active component depends on it.
///
///
/// \section Multiplicity
/// Another rule type is about instance multiplicity.
///
/// These set of rules allow a limited number of T-type Component within the same GameObject/ComponentContainer.
///
/// \code
/// //kernelrules
/// make_singleton("Transform");
///
/// //GameObject
/// addComponent<Transform>(); // Transform component is created
/// addComponent<Transform>(); // Error . a transform already exists, as Transform is marked as singleton ( x1 )
///
/// \endcode
///
/// \section User-defined-rules
/// Another point is about defining User-rules
///
/// It allows the user to define its own set of rule according to its application logic.
///
/// With a (dummy) example:
///
/// \note A hero represents a scene object (GameObject). and weapon equippements are Components
///
/// \li A hero cannot have more than one sword and one shield.
/// \li A sword cannot be equipped unless the hero is equipped with combat-gloves.
///
/// The generated rules whould be:
/// \code
/// // user_kernelrules
/// make_singleton("Sword");
/// make_singleton("Shield");
///
/// create_rule("Sword", "CombatGloves");
///
/// \endcode
///
/// Note that CombatGloves is not affected by the singleton rules, means that there is no number restriction
/// for that type of object.
class KernelRules {
    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        KernelRules();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default destructor
        virtual ~KernelRules();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Initializes a set of pre-defined rules for the built-in components
        ///
        /// Invokes KernelRules::on_init in order to allow user-rules
        ///
        virtual void init();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief In addition to pre-defined rules, they can be extended with a more high-level set of user rules.
        ///
        virtual void on_init();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Creates a rule \f$ A → B \f$, A and B are of cardinality of 1.
        ///
        /// In order to create a rule as \f$ A → B, C, ..., D \f$, it must be done separatly
        ///
        /// \f$ A → B \f$
        ///
        /// \f$ A → C \f$
        ///
        /// \f$ A → D \f$
        ///
        /// \note Adapt to std::initializer_list in order to accept a list of string. [incoming]

        /// \param dependent Is the left side item of the rule. ( the dependent )
        /// \param depended Is the right side item of the rule. ( the depended )
        ///
        void create_rule(std::string dependent, std::string depended );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Create a multiplicity rule, by setting the class \a target to be singleton
        ///
        /// \note Only singleton rule are used [incoming: >1 multiplicity]
        /// \param target Classname target
        ///
        void make_singleton( std::string target );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Display all the rules.
        ///
        void show_rules();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Singleton of the KernelRules class
        ///
        static KernelRules* kernel;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of dependecies rules
        ///
        std::map<std::string, std::list< std::string> > dependencies_rules;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of the classes set as singleton
        ///
        std::map<std::string, bool> singletons_rules;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#endif // KERNELRULES_H
