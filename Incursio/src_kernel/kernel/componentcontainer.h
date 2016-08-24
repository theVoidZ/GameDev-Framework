#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <QObject>

#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#include <boost/type_index.hpp>


#include "Core/Utilities/terminal_colors.h"

namespace gdf {
namespace kernel{

class Component;
class GameObject;

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
/// in the hierarchy.
///
/// As for the \a top_most_items container, it contains only Layer 1's components. ex: n1, n2, n3
///
/// This tree structure allows to create a dependency relationship between components. For example, n5 depends on
/// n1 and n2.
class ComponentContainer
{
//    Q_OBJECT
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
        /// \brief Add a newly created component of type T
        ///
        /// When ever a component is added, \a all_items keeps trace of it. Besides, if the component does not
        /// depend on other components, it will be added on Layer 1. i.e in \a top_most_items.
        ///
        /// Otherwise, it is added as a child of the components it depends on.
        ///
        /// The \a container argument when specified, allows to automatically insert that created component into
        /// this container. Otherwise, it does nothing.
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
        T* addComponent(std::list<T*>* container = nullptr);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Among the \a all_items components, retrieve the first component which is of type T and returns
        /// it.
        ///
        /// \return Component of type T, nullptr otherwise.
        ///
        /// \sa getComponents
        ///
        template< typename T >
        T* getComponent() const;
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
        std::list<T*> getComponents() const;
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
        T* getComponentOfType() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// \brief Among the \a all_items components, retrieve all the components which are of type T or
        /// sub-class of T and returns a list of polymorphic objects of base type T.
        ///
        /// \return List of Components of type T, empty list otherwise.
        ///
        /// \sa getComponents
        ///
        template< typename T >
        std::list<T*> getComponentsOfType() const;
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
        void make_linking(gdf::kernel::Component* comp, std::list<gdf::kernel::Component*>* lc);
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
        bool can_attach_component(ComponentContainer* host, gdf::kernel::Component *comp, std::list< gdf::kernel::Component*> *lc ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of all the components of the hierarchy regardless of their layer.
        ///
        std::list< gdf::kernel::Component* > all_items;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief The top-most components of the hierarchy, items of the first layer only.
        ///
        std::list< gdf::kernel::Component* > top_most_items;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#include "kernel/componentcontainer.inl"

#endif // COMPONENTCONTAINER_H
