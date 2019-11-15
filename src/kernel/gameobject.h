#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// c++-includes
#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

// sfml-includes

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// qt-includes

// user-includes
#include "object.h"
#include "componentcontainer.h"
#include "hierarchy.h"
#include "transform.h"

namespace gdf {

namespace temporal {
class Chrono;
}

namespace kernel{

enum class GoTag{
    Default,

    TagCount
};

enum class GoLayer{
    Default = 0,
    Air,
    Ground,
    LayerCount
};

class Component;
class Scene;
class Hierarchy;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The GameObject class represents a node's scene.
///
/// A GameObject has no representation on the scene, it is nothing but a container for Components.
/// In a way that, the meaning/context of a game object is defined by the its own components.
///
/// This class provides a set of tools to in order to manipulate these components.
///
/// \section Hierarchy
/// Since the game object is a scene node, it has a pre-created \a Hierarchy Component that helps creating the
/// tree structure.
class GameObject final :    public Object,
                            public ComponentContainer,
							public sf::Drawable
{
    friend class gdf::kernel::Scene;

    private:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Note that the constructor is \a private in order to deny the creation of game objects out of the
        /// \a GameObject::instantiate method.
        ///
        /// \param go_name Game object's name
        ///
        GameObject(std::string go_name = "");
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! Default destructor
        ~GameObject();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Displays a detailed information about the game object
        ///
        void verbose() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        void on_gui();


    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Initializes the GameObject
        ///
        /// This method does:
        /// \li Initializes the components of the GameObject
        /// \li Recursively in depth-first initializes the child game objects
        ///
        /// \note Since GameObject cannot be overridden, a method such on_init is not required to initialize
        /// GameObject's properties. Use a component instead.
        ///
        virtual void init();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an normal update of the game object with dt amount of time.
        ///
        /// Only active gameobjects are updated. See \a active_self \a active_in_hierarchy
        ///
        /// The update process does:
        /// \li Update the components of the game object
        /// \li Recursively in depth-first update child components
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        void update(sf::Time dt);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an normal update regarding the physics of the game object with dt amount of time.
        ///
        /// Only active gameobjects are updated. See \a active_self \a active_in_hierarchy
        ///
        /// The update process does:
        /// \li Update the components of the game object related to physics.
        /// \li Recursively in depth-first update child components
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        void fixed_update(sf::Time dt);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a normal update of the game object that comes nearly at end of loop with dt amount of
        /// time.
        ///
        /// Only active gameobjects are updated. See \a active_self \a active_in_hierarchy
        ///
        /// The update process does:
        /// \li Update the components of the game object related to physics.
        /// \li Recursively in depth-first update child components
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        void late_update(sf::Time dt);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overridden function from sf::Drawable::draw , used to draw the game object.
        ///
        /// Since the Game Object does not represent a concrete object, drawing a game objec will draw all the
        /// drawable component of that game object, See \a Renderer
        ///
        /// The drawing process is performed in a recursive way, in depth-first according to the arborescence.
        ///
        /// \param target RenderTarget
        /// \param states RenderState
        ///
        void draw( sf::RenderTarget &target, sf::RenderStates states) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:

        // Complements to methods in "ComponentContainer" when the host is involved in a hierarchy.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponent, but invoked from the parent of this game object.
        ///
        template< typename T >
        T* get_component_in_parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponents, but invoked from the parent of this game object.
        ///
        template< typename T >
        std::list<T*> get_components_in_parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentOfType, but invoked from the parent of this
        /// game object.
        ///
        template< typename T >
        T* get_component_in_parent_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentsOfType, but invoked from the parent of this
        /// game object.
        ///
        template< typename T >
        std::list<T*> get_components_in_parent_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponent, but invoked for all children of of this
        ///
        //　\BUG: GOT PROBLEMs　（　similar )
        template< typename T >
        T* get_component_in_children() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponents, but invoked for all children of of this
        /// game object.
        ///
        //　\BUG: GOT PROBLEMs　（　similar )
        template< typename T >
        std::list<T*> get_components_in_children() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentOfType, but invoked for all children of of this
        /// game object.
        //　\BUG: GOT PROBLEMs　（　similar )
        template< typename T >
        T* get_component_in_children_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentsOfType, but invoked for all children of of this
        /// game object.
        ///
        //　\BUG: GOT PROBLEMs　（ similar )
        template< typename T >
        std::list<T*> get_components_in_children_of_type() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //　\BUG: GOT PROBLEMs　( similar )
        template< typename T >
        void get_component_in_children__recursive(T** result, const GameObject* current_node, bool look_for_subtypes) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //　\BUG: GOT PROBLEMs　（ similar )
        template< typename T >
        void get_components_in_children__recursive(std::list<T*>* result, const GameObject* current_node, bool look_for_subtypes) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Calls the method named 'method_name' on every MonoBehaviour in this game object.
        ///
        /// \note Maximum number of parameter must not exceed 10
        /// \note proceed the method to invoke with the Qt MACRO \a Q_INVOKABLE
        ///
        /// \param method_name Method's name
        /// \param args Argument of the function
        ///
        /// \sa send_message_upwards, broadcast_message
        // TODO: Reimplement without Qt Modules
        void send_message(const char* method_name, std::vector<void*> args ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Calls the method named \a method_name on every MonoBehaviour in this game object and all
        /// parent game objects
        ///
        /// \note Maximum number of parameter must not exceed 10
        /// \note proceed the method to invoke with the Qt MACRO \a Q_INVOKABLE
        ///
        /// \param method_name Method's name
        /// \param args Argument of the function
        ///
        /// \sa send_message_upwards, broadcast_message
        // TODO: Reimplement without Qt Modules
        void send_message_upwards( const char* method_name, std::vector< void* > args ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Calls the method named \a method_name on every MonoBehaviour in this game object and all its
        /// children
        ///
        /// \note Maximum number of parameter must not exceed 10
        /// \note proceed the method to invoke with the Qt MACRO \a Q_INVOKABLE
        ///
        /// \param method_name Method's name
        /// \param args Argument of the function
        ///
        /// \sa send_message_upwards, broadcast_message
        ///
        // TODO: Reimplement without Qt Modules
        void broadcast_message(const char* method_name, std::vector<void*> args ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Finds a game object with name \a name
        // TODO: gamesobject's names must be unqiue
        /// \bug Which scene to look for
        ///
        /// \param name Game object's name
        /// \return GameObject with name \a name, nullptr otherwise.
        ///
        static GameObject* find(std::string name, Scene* scene_target=nullptr);
    public:
        static GameObject* find_in_scene(std::string name, Scene* scene_target);
        static GameObject* find_in_scene(unsigned long instance_id, Scene* scene_target);

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destroy a object after \a ttd_ms amount of time in milliseconds
        ///
        /// Instantly destroy object by default
        ///
        /// \param go Object to destroy
        /// \param ttd_ms Amount of time after when to physically destroy the Object
        ///
        static void destroy(GameObject* go , unsigned long long ttd_ms = 0 );
        static void destroy(tracker_ptr<GameObject> go , unsigned long long ttd_ms = 0 );
        static void destroy(Component* comp , unsigned long long ttd_ms = 0 );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //Setters

        //Getters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the status of the game object
        ///
        /// \return True if the game object is active, false otherwise.
        ///
        bool active_self() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the status of the game object within the hierarchy
        ///
        /// A game object is active in hierarchy, if the game object's active_self is true, and the ones of all
        /// its ancestors ( til the root game object ).
        ///
        /// \return True if the game object is active in the hierarchy, false otherwise.
        ///
        bool active_in_hierarchy() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the hierarchy component attached to the game object.
        ///
        /// \return Hierarchy of the game object
        ///
        tracker_ptr<Hierarchy>& hierarchy();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the transofrm component attached to the game object.
        ///
        /// \return Transform of the game object
        ///
        tracker_ptr<Transform>& transform();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        tracker_ptr<gdf::temporal::Chrono>& chrono();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the parent of the game object, through the hierarchy component
        ///
        /// \return Parent game object
        ///
        GameObject* parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the children of the game object, through the hierarchy component
        ///
        /// \return Children of the game object
        ///
        std::list<GameObject*> children() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the scene of this game object
        ///
        /// \return Game object's scene
        ///
        gdf::kernel::Scene* scene() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ! NOTE: Convert them into trackers ?
        tracker_ptr<Hierarchy> hierarchy_;
        tracker_ptr<Transform> transform_;
        tracker_ptr<gdf::temporal::Chrono> chrono_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Represents the scene where the game object is instantiated into.
        ///
        gdf::kernel::Scene* scene_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief True when the game object is enabled/active, false otherwise
        ///
        bool active_self_ = true;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
    \
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        GoLayer layer_ = GoLayer::Default;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        GoTag tag_ = GoTag::Default;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#include "./gameobject.inl"

#endif // GAMEOBJECT_H
