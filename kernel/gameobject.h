#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// c++-includes
#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

// sfml-includes
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// qt-includes
#include <QVariant>

// user-includes
#include "kernel/object.h"
#include "Core/gotag.h"
#include "Core/golayer.h"
#include "kernel/componentcontainer.h"

#include "Core/transform.h"
#include "kernel/hierarchy.h"

namespace gdf {
namespace kernel{

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
/// \section Transform
/// Since the game object is a scene node, it has a pre-created \a Transform Component that helps creating the
/// tree structure.
class GameObject final :    public Object,
                            protected sf::NonCopyable,
                            protected sf::Drawable,
                            public ComponentContainer
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

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! Default destructor
        ~GameObject();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Displays a detailed information about the game object
        ///
        void verbose();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overridden funtion from sf::Drawable::draw , used to draw the game object.
        ///
        /// Since the Game Object does not represent a concrete object, drawing a game objec will draw all the
        /// drawable component of that game object, See \a Renderer
        ///
        /// The drawing process is performed in a recursive way, in depth-first according to the arborescence.
        ///
        /// \param target RenderTarget
        /// \param states RenderState
        ///
        void draw( sf::RenderTarget &target, sf::RenderStates states) const override;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        // Complements to methods in "ComponentContainer" when the host is involved in a hierarchy.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponent, but invoked from the parent of this game object.
        ///
        template< typename T >
        T* getComponentInParent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponents, but invoked from the parent of this game object.
        ///
        template< typename T >
        std::list<T*> getComponentsInParent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentOfType, but invoked from the parent of this
        /// game object.
        ///
        template< typename T >
        T* getComponentInParentOfType() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentsOfType, but invoked from the parent of this
        /// game object.
        ///
        template< typename T >
        std::list<T*> getComponentsInParentOfType() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponent, but invoked for all children of of this
        ///
        template< typename T >
        T* getComponentInChildren() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponents, but invoked for all children of of this
        /// game object.
        ///
        template< typename T >
        std::list<T*> getComponentsInChildren() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentOfType, but invoked for all children of of this
        /// game object.
        ///
        template< typename T >
        T* getComponentInChildrenOfType() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Similar to \a ComponentContainer::getComponentsOfType, but invoked for all children of of this
        /// game object.
        ///
        template< typename T >
        std::list<T*> getComponentsInChildrenOfType() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< typename T >
        void getComponentInChildren_recursive(T** result, const GameObject* current_node, bool look_for_subtypes ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        template< typename T >
        void getComponentsInChildren_recursive(std::list<T*>* result, const GameObject* current_node, bool look_for_subtypes) const;
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
        ///
        /// QT: void send_message(const char* method_name, std::vector<QVariant> args ) const;
        ///
        void send_message(const char* method_name, std::vector<QVariant> args ) const;
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
        ///
        /// QT: void send_message(const char* method_name, std::vector<QVariant> args ) const;
        ///
        void send_message_upwards( const char* method_name, std::vector< QVariant > args ) const;
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
        /// QT: void send_message(const char* method_name, std::vector<QVariant> args ) const;
        ///
        void broadcast_message(const char* method_name, std::vector<QVariant> args ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Finds a game object with name \a name
        ///
        /// \bug Which scene to look for
        ///
        /// \param name Game object's name
        /// \return GameObject with name \a name, nullptr otherwise.
        ///
        static GameObject* find(std::string name);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Instantiate a game object and add it automatically on the scene
        ///
        /// \bug Which scene is concerned ? how to specify it. Or may be do not automatically attach GO to root ?
        /// Gives more flexibility.
        ///
        /// Game objects cannot be instantiated directly using theirs constructor.
        ///
        /// This method creates an instance of game object and add it to the scene hierarchy, if no parent is
        /// specified, the game object is set as a child of \a Scene::root_
        ///
        /// \return Instance of GameObject
        ///
        template< int scene_index>
        static GameObject* instantiate();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overloaded function of GameObject::instantiate
        ///
        /// \param go_name Game object's name
        /// \param pos Initial position
        /// \param rotation Initial rotation
        /// \return Instance of GameObject
        ///
        template< int scene_index>
        static GameObject* instantiate(std::string go_name, sf::Vector2f pos = sf::Vector2f(0,0), float rotation = 0);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overloaded function of GameObject::instantiate
        ///
        /// \param parent Parent of the game object
        /// \param go_name Game object's name
        /// \param pos Initial position
        /// \param rotation Initial rotation
        /// \return Instance of GameObject
        ///
        template< int scene_index>
        static GameObject* instantiate(Hierarchy* parent, std::string go_name = "", sf::Vector2f pos = sf::Vector2f(0,0), float rotation = 0);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destroy a game object after \a ttd_ms amount of time in milliseconds
        ///
        /// Instantly destroy the game object by default
        ///
        /// \param go Game object to destroy
        /// \param ttd_ms Amount of time after when to physically destroy the game object
        ///
        static void destroy(GameObject* go , unsigned long long ttd_ms = 0 );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destroy a component after \a ttd_ms amount of time in milliseconds.
        ///
        /// Instantly destroy the component by default
        ///
        /// \param comp Component to destroy
        /// \param ttd_ms Amount of time after when to physically destroy the component
        ///
        static void destroy(Component* comp , unsigned long long ttd_ms = 0);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //Setters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the game object to active
        ///
        /// \param etat True active, false otherwise.
        ///
        void set_active_self( bool etat );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        /// \brief Retrieves the transform component attached to the game object.
        ///
        /// \return Transform of the game object
        ///
        Transform* transform() const;
        Hierarchy* hierarchy() const;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the parent of the game object, through the transform component
        ///
        /// \return Parent game object
        ///
        GameObject* parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the children of the game object, through the transform component
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
        gdf::kernel::Scene* scene();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Game Object counter.
        ///
        /// \bug Not related to a specific scene. Accounts all instances
        ///
        static unsigned long game_object_counter;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief True when the game object is enabled/active, false otherwise
        ///
        bool active_self_ = true;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Physical coordinates of the game object.
        ///
        /// Transform component allows the game object to be located in a 2-dimensional coordiante system.
        ///
        /// It gives him a position, a rotation, and a scale.
        ///
        Transform* transform_ = nullptr;
        Hierarchy* hierarchy_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Represents the scene where the game object is instantiated into.
        ///
        /// Only the root holds a pointer to the owning scene, children have this reference set to nullptr.
        ///
        /// Thus, in order for a given child game object to get the reference to the scene, it must get it
        /// through the root game object.
        ///
        gdf::kernel::Scene* scene_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


};

}}

#include "./gameobject.inl"

#endif // GAMEOBJECT_H
