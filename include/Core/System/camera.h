#ifndef CAMERA_H
#define CAMERA_H

// c++-includes

// sfml-includes
#include <SFML/Graphics.hpp>

// qt-includes
#include <iostream>

// user-includes
#include "Core/System/behavior.h"
#include "Core/DataStruct/bounds.h"

class GameInfo;

//! WARNING: Position of the View is located on the TOP-LEFT of the view
//! This class represent a view for the scene.
/*!
 * It is considered as a concrete view of the scene used to display elements onto the window.
 */
class Camera final : public Behavior
{
    Q_OBJECT
    public:

        //! Default constructor
        /*!
         * A Scene can adapt one or many cameras to display the elements. A camera is defined by a 'resolution' and
         * a view port which specify the area inside the window where the camera should display its rendereding.
         */
        Camera();

        //! Destructor
        ~Camera();

        void update(sf::Time dt);

    public:
        //Mapping functions
        //! Convert screen cordinates to viewport coordinates
        /*!
         * \param point Screen coordinates to convert
         * \return Viewport coordinates
         */
        sf::Vector2f screenToViewport(sf::Vector2f point) const;

        //! Convert viewport cordinates to screen coordinates
        /*!
         * \param point Viewport coordinates to convert
         * \return Screen coordinates
         */
        sf::Vector2f viewportToScreen(sf::Vector2f point) const;

        //! Convert screen cordinates to world coordinates
        /*!
         * \param point Screen coordinates to convert
         * \return World coordinates
         */
        sf::Vector2f screenToWorld(sf::Vector2f point) const;

        //! Convert world cordinates to screen coordinates
        /*!
         * \param point World coordinates to convert
         * \return Screen coordinates
         */
        sf::Vector2f worldToScreen(sf::Vector2f point) const;

        //! Convert viewport cordinates to world coordinates
        /*!
         * \param point Viewport coordinates to convert
         * \return World coordinates
         */
        sf::Vector2f viewportToWorld(sf::Vector2f point) const;

        //! Convert world cordinates to viewport coordinates
        /*!
         * \param point World coordinates to convert
         * \return Viewport coordinates
         */
        sf::Vector2f worldToViewport(sf::Vector2f point) const;


    public:
        //! NOTE: How do they affect conversions ?
        /*!
          \sa move()
         */
        void move( sf::Vector2f pos );

        //! Problem in zooming & rotating in camera
        void zoom(float factor );
        void rotate(float rotation);

    protected:
        //! The concrete camera.
        sf::View view;

        //! Size of the main window
        sf::Vector2f main_win_size;

        //! Size of the Camera ( window )
        sf::Vector2f viewport_size;
        sf::Vector2f viewport_extent;


        //! Position of the camera relative to the screen
        sf::Vector2f viewport_position = sf::Vector2f(0,0);

        float scale_factor = 1.0f;

    public:
        //Getters
        //! Returns the instance of the view held by the camera.
        /*!
         * \return The view
         */
        sf::View& getView();
        Bounds getBounds() const;

        //Setters
        //! FIXME: These methods will reset current scale/rotation
        void setViewportPosition(sf::Vector2f view_port_pos );

        //! NOTE: Use move instead
        void setCameraLocation( sf::Vector2f location );

};

#endif // CAMERA_H
