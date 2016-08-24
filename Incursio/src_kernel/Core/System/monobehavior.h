#ifndef MONOBEHAVIOUR_H
#define MONOBEHAVIOUR_H

// c++-includes

// sfml-includes

// qt-includes
#include <iostream>

// user-includes
#include "Core/System/behavior.h"

class Camera;

class MonoBehavior : public Behavior
{
    Q_OBJECT
    public:
        MonoBehavior();
        ~MonoBehavior();

    public:
        virtual void fixed_update(sf::Time dt);
        virtual void late_update(sf::Time dt);

/*
        start();
        awake();
        reset(); //editor only
*/
    public:
        // Callback functions --------------------------------------------------

        //! Callback - Invoked before a camera starts rendering the first item
        /*!
         * Concerns only Component of camera's gameobject
         * \param camera Specify the camera responsible for the callback
         */
        virtual void on_pre_render( Camera* camera );

        //! Callback - Invoked after a camera finishes rendering the last item
        /*!
         * Concerns only Component of camera's gameobject
         * \param camera Specify the camera responsible for the callback
         */
        virtual void on_post_render( Camera* camera );

        //! Callback - Invoked to render the canvas. Draw into the screen.
        virtual void on_gui();

        //! Callback - Invoked when the Renderer Component becomes visible on any camera
        virtual void onBecameVisible();

        //! Callback - Invoked when the Renderer Component becomes invisible on all camera
        virtual void onBecameInvisible();


        //! Callback - Invoked when the game object attached to this monobehavior is detroyed
        virtual void onDestroy();

        //! Callback - Windows
        virtual void on_closed(const sf::Event& event);
        virtual void on_resized(const sf::Event& event);
        virtual void on_gained_focus(const sf::Event& event);
        virtual void on_lost_focus(const sf::Event& event);
        virtual void on_mouse_entered(const sf::Event& event);
        virtual void on_mouse_left(const sf::Event& event);

        //! Callback - Related to Inputs.Mouse
        virtual void on_mouse_button_pressed(const sf::Event& event);
        virtual void on_mouse_button_released(const sf::Event& event);
        virtual void on_mouse_moved(const sf::Event& event);
        virtual void on_mouse_wheel_moved(const sf::Event& event);
        virtual void onMouseDoubleClick(const sf::Event& event);

        //! Callback - Related to Inputs.Keyboard
        virtual void on_key_pressed(const sf::Event& event);
        virtual void on_key_released(const sf::Event& event);
        virtual void on_text_entered(const sf::Event& event);


        //! Callback - Joystick
        virtual void on_joystick_button_pressed(const sf::Event& event);
        virtual void on_joystick_button_released(const sf::Event& event);
        virtual void on_joystick_moved(const sf::Event& event);
        virtual void on_joystick_connected(const sf::Event& event);
        virtual void on_joystick_disconnected(const sf::Event& event);

//        Q_INVOKABLE void hello( int i );
//        Q_INVOKABLE void hello( int i, QString a);
/*

        //StateMachineBehaviour
        OnStateMachineEnter
        OnStateMachineExit
        Messages
        OnStateEnter
        OnStateExit
        OnStateIK
        OnStateMove
        OnStateUpdate

        //ScriptableObject
        onDestroy();
        onDisable();
        onEnable();

        //Animator
        onAnimatorSOMETHING();

        //Application
        onApplicationFocus();
        onApplicationPause();
        onApplicationQuit();

        //Audio
        onAudioFilterRead();

        //Renderer
        onBecomeInvisible();
        onBecomeVisible();

        //Physic
        onCollisionEnter();
        onCollisionStay();
        onCollisionExit();
        onTriggerEnter();
        onTriggerStay();
        onTriggerExit();
//        OnControllerColliderHit ??
        onJointBreak();

        //Network
//        onConnectedToServer();
//        onDisconnectedFromServer();
//        onFailToConnect();
//        onMasterServerEvent();
        onPlayerConnected();
        onPlayerDisconnected();
        onServerInitialized();

        //Gameobject
        onDestroy();
        onDisable();
        onEnable();
        onTransformParentCHanged();
        onTransformChildrenChanged();

        //Rendering CANVAS
        onGui();
        onDrawGizmos();
        onDrawGizmosSelected();

        //Level
        onLevelWasLoaded();

        //MouseEvents
        onMouseDown();
        onMouseUp();
        onMouseDrag();
        onMouseEnter();
        onMouseOver();
        onMouseExit();

        //Cameras
        onPreRender();
        onPostRender();
        onRenderObject();
*/
};

#endif // MONOBEHAVIOUR_H
