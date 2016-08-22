#ifndef SCENE_H
#define SCENE_H

// c++-includes
#include <iostream>
#include <iomanip>
#include <list>

// boost-includes
#include <boost/type_index.hpp>

// sfml-includes
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

// box2d-includes

// qt-includes

// user-includes
#include "Core/Utilities/terminal_colors.h"
#include "kernel/componentcontainer.h"

class Camera;

namespace gdf {
namespace kernel {


class GameInfo;
class Object;
class GameObject;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Scene class is the base class for all scenes.
///
/// The scene class provides a way for creating and organizing several items in a tree strucutre.
///
/// This class serves as a container for \a GameObject, allowing theirs initialization, updating and rendering.
///
/// \note Scene inherits from \a ComponentContainer which provides it with a Component Container.
class Scene :       public ComponentContainer
{
    public:
        friend class gdf::kernel::GameInfo;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        Scene();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        virtual ~Scene();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Initializes the scene.
        ///
        /// This method does:
        /// \li Creates and initializes the root node (GameObject)
        /// \li Invokes \a on_init int order Initialize an overridden scene.
        /// \li Initializes the components of the Scene
        /// \li Loads all the resources needed by the scene's objects
        /// \li Constructs and initializes the scene's objects.
        ///
        /// \note This method cannot be overridden.
        ///
        /// See \a Scene::on_init

        virtual void init() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Invoked after all scenes are inited
        ///
        virtual void post_init() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Used when overriding from Scene to specify specific inits.
        ///
        virtual void on_init() = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads at first necessary resource needed by the scene.
        ///
        virtual void load_resources() = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Constructs the scene, by instantiating all the objects of the scene.
        ///
        /// Building can be achieved:
        /// \li In a static way (hard-coding)
        /// \li Loading a save-file.
        ///
        virtual void build() = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Handle events related to the scene and it objects.
        ///
        /// This method does:
        /// \li Invoke \a Scene::on_event to handle scene's related events.
        /// \li Performs events-related callbacks on all objects of the scene. See \a MonoBehavior
        ///
        /// \param event Event thrown and carried by the method
        ///
        virtual void handle_events(const sf::Event& event) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Used when overriding from Scene to specify specific event handling proper the scene.
        ///
        /// \param event Event captured
        ///
        virtual void on_event(const sf::Event& event) = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an normal update of the elements of the scene with dt amount of time.
        ///
        ///
        /// \note The scene's elements are updated recursively in depth-first, any object not connected to the
        /// hierarchy is not updated. i.e not a child of \a Scene::root_
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        virtual void update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an update regarding the physics of the elements of the scene with dt amount of time.
        ///
        /// \note The scene's elements are updated recursively in depth-first, any object not connected to the
        /// hierarchy is not updated. i.e not a child of \a Scene::root_
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        virtual void fixed_update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a normal update of the elements of the scene that comes nearly at end of loop with
        /// dt amount of time.
        ///
        /// \note The scene's elements are updated recursively in depth-first, any object not connected to the
        /// hierarchy is not updated. i.e not a child of \a Scene::root_
        ///
        /// \param dt The elapsed amount of time
        ///
        virtual void late_update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a rendering of the elemens of the scene.
        ///
        /// The rendering process will render the content of all the cameras of the scene.
        ///
        /// \note The scene's elements are rendered recursively in depth-first, any item not connected to the
        /// hierarchy is not rendered. i.e not a child of \a Scene::root_
        ///
        virtual void render() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a rendering of the scene regarding the HUD.
        ///
        /// The gui-rendering process will render the hud parts of the scene. See \a Gui
        ///
        /// \note The scene's elements are rendered recursively in depth-first, any item not connected to the
        /// hierarchy is not rendered. i.e not a child of \a Scene::root_
        ///
        virtual void render_gui() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        // Setters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Sets the scene daemon's property to true or false.
        ///
        /// \param daemon Value to be set.
        ///
        void set_as_daemon(bool daemon);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        // Getters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the list of cameras of the scene.
        /// \return List of camera
        ///
        std::list<Camera*>& cameras();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the root of the scene
        /// \return Scene's root
        ///
        gdf::kernel::GameObject* root() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the list of game objects of the scene.
        /// \return List of all game objects managed by the scene
        ///
        std::list< gdf::kernel::GameObject* >& game_objects();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieve the list of discarded objects, ready to be destroyed
        /// \return List of objects.
        ///
        std::map<Object*, sf::Time>& junkyard();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the daemon property of the scene
        /// \return True when the scene is a daemon, false otherwise.
        ///
        bool is_daemon() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieve the loading status of the status.
        /// \return True if the scene is loaded, false otherwise
        ///
        bool is_loaded() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieves the clear color of the scene.
        /// \return Scene's clear color
        ///
        sf::Color clear_color() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string name() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief See. Scene::junkyard_, but used for orphan objects.
        ///
        static std::map< Object*, sf::Time > global_junkyard_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of all camera of the scene
        ///
        /// Using \a ComponentContainer::addComponent and \a ComponentContainer::destroy will alter the
        /// content of this container.
        ///
        /// \note Cameras are used in Scene::render to draw the object, keeping a reference of all created cameras is
        /// crucial for performance.
        ///
        std::list<Camera*> cameras_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Represents the top-most object of the scene's hierarchy
        ///
        /// Every GameObject that belongs to the scene is created as a direct or indirect child of the root.
        ///
        /// \note The root object cannot be destroyed. [Not implemented yet]
        ///
        GameObject* root_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of all game objects of the scene.
        ///
        /// \attention Game objects that are not connected to the root's scene are not listed in this container.
        ///
        std::list< GameObject* > game_objects_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief A container to hold all objects marked for destruction [NOT USED]
        ///
        /// A Garbage Collector will bind to this container to process and destroy the objects
        ///
        /// \attention Requires a base class, such as Object.
        /// \note Only objects of type \a Object are destroyable.
        ///
        /// \attention This will be used with GC later
        ///
        std::map< Object*, sf::Time > junkyard_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Property to tell whether the scene is a daemon or not.
        ///
        /// A daemon scene is a scene that advances ( updates ) even if it is not active.
        ///
        bool is_daemon_ = false;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Property to tell if the scene is loaded or not.
        ///
        bool is_loaded_ = false;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default clear color of the scene
        ///
        sf::Color clear_color_ = sf::Color::Black;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string name_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


};

}}

#endif // SCENE_H
