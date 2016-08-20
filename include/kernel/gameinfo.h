#ifndef MYCANVAS_H
#define MYCANVAS_H

// c++-includes
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>

// boost-includes

// sfml-includes
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

//box2d-includes

// qt-includes

// user-includes
#include "kernel/kernelrules.h"
#include "Core/Utilities/terminal_colors.h"
#include "hierarchicalcontainer.h"

namespace gdf {
namespace kernel {

class Scene;
class Object;
class Component;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GameInfo is a class that represents the main class of the application.
///
/// The GameInfo has a pre-defined (gamelogic) way of handling events, updating, drawing etc. and also integrates a minimum
/// of necessary components to ensure a good functionning.
///
/// It supports multi-scenes management. [But NOT fully functionning at the moment]
///
/// You can override this class in order to implement your own GameLogic ( from scratch )
///
/// \note GameInfo inherits from \a HierarchicalContainer which provides it with a Component Container.
class GameInfo :    public sf::RenderWindow,
                    public HierarchicalContainer
{

    public :
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Construct a concrete GUI-Window application. and defines updating, drawing and event handling
        /// logics to be used.
        ///
        /// \param size Size of the window
        /// \param title Title of the window
        ///
        GameInfo(const sf::Vector2i& size, std::string title);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default destructor
        ///
        ~GameInfo();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Initializes the GameInfo
        ///
        /// This method does:
        /// \li Invokes \a on_init: in order to initialize an overridden-GameInfo.
        /// \li Initializes the components of the GameInfo
        /// \li Initializes all the Scenes
        ///
        /// \note This method cannot be overridden.
        ///
        /// See \a GameInfo::on_init
        ///
        virtual void init() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Used when overriding from GameInfo to specify specific inits.
        ///
        virtual void on_init() = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Defines the GameLogic of the application.
        ///
        /// GameLogic is a set of organized methods, mechanisms used for updating, events handling and drawing.
        ///
        /// Performs in a loop:
        /// \li Events handling
        /// \li Normal updating
        /// \li Physics updating
        /// \li Normal/Late updating
        /// \li Drawing
        ///
        /// \image html images/gameloop_elementary_cycle.png
        ///
        virtual void gameloop() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Captures events and forward them to scenes event handler.
        ///
        /// Only the active scene can handle events.
        ///
        /// \note This method cannot be overridden.
        ///
        /// See \a on_event
        ///
        virtual void handle_events() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Used when overriding from GameInfo to specify specific event handling proper the game info.
        ///
        /// \param event Event captured
        ///
        virtual void on_event(const sf::Event& event) = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an normal update of the scenes with dt amount of time.
        ///
        /// Only active scene and scenes marked as \a daemon are updated. See \a Scene::is_daemon_
        ///
        /// \note Active scene always update before daemon scenes
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        virtual void update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs an update regarding the physics of the scenes with dt amount of time.
        ///
        /// Only active scene and scenes marked as \a daemon are updated. See \a Scene::is_daemon_
        ///
        /// \note Fixed update concerns physics update, and comes after normal update. See \a GameInfo::gameloop
        ///
        /// \note Active scene always updates before daemon scenes
        ///
        /// \param dt The elapsed amount of time between two calls
        ///
        virtual void fixed_update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a normal update of the scene that comes nearly at end of loop with dt amount of time.
        ///
        /// Only active scene and scenes marked as \a daemon are updated. See \a Scene::is_daemon_
        ///
        /// \note Active scene always updates before daemon scenes
        ///
        /// \param dt The elapsed amount of time between two calls.
        ///
        virtual void late_update(sf::Time dt) final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Performs a draw of the elemens of the active scene.
        ///
        /// The rendering process displays intially the content of all cameras of the active scene. Then it
        /// displays the HUD, in order to keep it always on top.
        ///
        /// \note Only the active scene performs rendering
        ///
        /// \image html images/draw_cycle.png
        ///
        virtual void render() final;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        // Setters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the scene 'scene_name' as active.
        ///
        /// If the scene name does not exist, the previous scene is kept active.
        ///
        /// \param scene_name The scene name to set to active
        ///
        void set_active_scene(std::string scene_name );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        //Getters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief scenes Retrieve the list of scenes of the game info.
        ///
        /// \return All available scenes
        ///
        std::map< std::string, Scene* >& scenes();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Retrieve the list of discarded objects, ready to be destroyed
        /// \return List of objects.
        ///
        std::map<Object*, unsigned long long>& junkyard();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief active_scene Retrieve the active scene
        /// \return Active scene, nullptr otherwise
        ///
        Scene* active_scene() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Represents the necessary amount of time needed to perform an update.
        ///
        static const sf::Time delta_time;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Singleton of the GameInfo itself, to always keep one active reference of the GameInfo
        ///
        static std::unique_ptr<GameInfo> game_info;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    private:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Used internally.
        ///
        sf::Clock clock;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief List of named scenes of the game info.
        ///
        std::map< std::string, Scene* > scenes_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Pointer to the active scene.
        ///
        /// The active scene is an item of the \a scenes container.
        ///
        Scene* active_scene_ = nullptr;
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
        std::map< Object*, unsigned long long > junkyard_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#endif // MYCANVAS_H