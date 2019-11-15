#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <memory>

#include <boost/type_index.hpp>
#include <boost/type_traits.hpp>

#include "terminal_colors.h"

#include "tracker_ptr.h"

#include "componentfactory.h"

namespace gdf {
namespace kernel{

class Component;
class GameObject;
class ComponentFactory;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The ComponentContainer class provides a specific way of orgnazing components.
///
/// It is structured in a multi-root tree. A non cyclic directed graph with several source-nodes and
/// several (final/well?) nodes.
///
/// \image html images/ComponentContainer.png
///
/// Every node can have multiple parents and multiple chidren. Note that, the top-most nodes have no parents,
/// and the bottom-most nodes have no children. See \a Component
///
/// Here as shown in the figure, \a all_items container contains all the components regardless of their positionning
/// and relation in the hierarchy.
///
/// As for the \a top_most_items container, it contains only Layer 1's components. ex: n1, n2, n3
///
/// This tree structure allows to create a dependency relationship between components. For example, n5 depends on
/// n1 and n2.
class ComponentContainer
{
    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ComponentContainer();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        virtual ~ComponentContainer();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Register a given Class by binding its name and constructor together. Used by the
        /// \a ComponentFactory.
        ///
        /// \sa gdf::kernel::ComponentFactory::register_component
        ///
        /// \param name Name of the registered class.
        /// \param Pointer to function to the constructor of the class
        ///
        static void register_component(const std::string& name, Component* (* ctor)(void));
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Add a newly created component of type T
        ///
        /// When ever a component is added, \a all_items keeps trace of it. Besides, if the component does not
        /// depend on other components, it will be added on Layer 1. i.e in \a top_most_items.
        ///
        /// Otherwise, it is added as a child of the components it depends on.
        ///
        /// The \a container argument when specified, allows to automatically insert that created component into
        /// this container, usually to keep track of it. Otherwise, it does nothing.
        ///
        /// for example: In order to keep track of all cameras within the Scene. Each time the scene adds a
        /// camera component, it will keep track of it inside a container called 'cameras'
        ///
        /// \code
        /// scene->addComponent<Camera>( &scene->camera );
        /// \endcode
        ///
        /// Otherwise, the method is simply called so
        /// \code
        /// scene->addComponent<GarbageCollector>();
        /// \endcode
        ///
        /// \note This method always return a new component, never returns nullptr.
        ///
        /// \param container The container where this component is optionally added into it.
        /// \return A new component.
        ///
        /// \sa getComponent, getComponentOfType
        ///
        template< typename T >
        T* add_component(std::list<T*>* container);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        template< typename T >
        T* add_component(std::list< gdf::kernel::tracker_ptr<T> >* container);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Overloade method, \sa addComponent.
        ///
        /// The Component instance can be passed as parameter through-out \a exisiting_comp. if not,
        /// the method will create a new instance of that component.
        ///
        /// \param existing_comp Parameter created outside and passed as parameter, if NULL create new instance.
        /// ( \a exisiting_comp will stay \b nullptr )
        /// \return Instance of type T
        ///
        template< typename T >
        T* add_component(Component* existing_comp = nullptr);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Overloaded method of \sa addComponent,
        ///
        /// Specify a Tracke pointer (tracker_ptr) that will hold the instance of the Component.
        ///
        /// The Component instance can be passed as parameter through-out \a exisiting_comp. if not,
        /// the method will create a new instance of that component.
        ///
        /// \param vessel Tracker pointer holding the instance of the component object.
        /// \param existing_comp Parameter created outside and passed as parameter, if NULL create new instance.
        /// ( \a exisiting_comp will stay \b nullptr )
        /// \return Instance of type T
        ///
        template < typename T >
        T* add_component(tracker_ptr<Component> vessel, Component* existing_comp, std::string comp_classname);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Find the component \a comp and returns a tracker_ptr of it. if \a comp does not figure in the list,
        /// returns an empty, expired tracker_ptr.
        ///
        template< typename T >
        gdf::kernel::tracker_ptr<T> get_component_tracker(gdf::kernel::Component* comp);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


        //! FIXEME: Do they take in consideration sub-classes?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Among the \a all_items components, retrieve the first component which is of type T and returns
        /// it.
        ///
        /// \return Component of type T, nullptr otherwise.
        ///
        /// \sa getComponents
        ///
        template< typename T >
        T* get_component() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Among the \a all_items components, retrieve all the components which are of type T and returns
        /// a list of objects of type T.
        ///
        /// \return List of Components of type T, empty list otherwise.
        ///
        /// \sa getComponentsOfType
        ///
        template< typename T >
        std::list<T*> get_components() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Among the \a all_items components, retrieve the first component which is of type T or a
        /// sub-class of T and returns it
        ///
        /// \return Component of type T or sub-class of T, nullptr otherwise.
        ///
        /// \sa getComponent
        ///
        template< typename T >
        T* get_component_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// \brief Among the \a all_items components, retrieve all the components which are of type T or
        /// sub-class of T and returns a list of polymorphic objects of base type T.
        ///
        /// \return List of Components of type T, empty list otherwise.
        ///
        /// \sa getComponents
        ///
        template< typename T >
        std::list<T*> get_components_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Establish a relatioship between the component \a comp and the list of components \a lc
        ///
        /// Makes the component \a comp as a child of every component in the list \a lc, and vice-versa. Each
        /// component of \a lc is parent of \a comp.
        ///
        /// \param comp Component to attach as a child.
        /// \param lc List of parent components
        ///
        void make_linking(tracker_ptr<Component> comp_holder, std::list< tracker_ptr<Component> >* lc);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Checks whether a component \a comp can be attached to the hierarchy of components.
        ///
        /// Based on a pre-defined rules in \a KernelRules. A component can be attached if it satisfies on of
        /// those rules.
        ///
        /// A rule is defined as follow:\n
        /// \f$ R → C1, C2, ....Cn \f$, where R, C1, C2,..., Cn are class names
        ///
        /// A rule is statisfied toward an object \a Obj if and only if:
        /// \li Each item of the second part of the rule must have an instance (sub_class) within the target object.
        /// \li If so, Then the Component A can be attached to the object \a Obj.
        ///
        /// \param comp Component to test its attachement with the current Object
        /// \param lc Output variable to store the involved components during the checking. This is used in
        /// combination with \a make_linking.
        /// \return True if the component can be attached, false otherwise.
        ///
        bool can_attach_component(ComponentContainer* host, Component *comp, std::list< tracker_ptr<Component> > *lc ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of all the components of the hierarchy regardless of their layer.
        ///
        std::list< tracker_ptr<Component> > all_items;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief The top-most components of the hierarchy, items of the first layer only.
        ///
        std::list< tracker_ptr<Component> > top_most_items;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#include "componentcontainer.inl"

#endif
