#ifndef CAMERA_H
#define CAMERA_H

// c++-includes

// sfml-includes
#include <SFML/Graphics.hpp>

// qt-includes
#include <iostream>
#include <map>
#include <memory>

// user-includes
#include "bounds.h"

#include "transform.h"

namespace gdf {
namespace kernel {

class GameInfo;

//! WARNING: Position of the View is located on the TOP-LEFT of the view
//! This class represent a view for the scene.
/*!
 * It is considered as a concrete view of the scene used to display elements onto the window.
 */
class Camera final :    public gdf::kernel::Component,
                        public sf::View

{
    public:
        //! Default constructor
        /*!
         * A Scene can adapt one or many cameras to display the elements. A camera is defined by a 'resolution' and
         * a view port which specify the area inside the window where the camera should display its rendering.
         */
        Camera();

        //! Destructor
        ~Camera();

        void init();
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

    protected:
        //! Size of the main window
        sf::Vector2f main_win_size;

        //! Size of the Camera ( window )
        sf::Vector2f viewport_size;


        float scale_factor = 1.0f;


        // If the position follows the owner gameobject
        bool follow_game_object;
        sf::Vector2f aspect_ratio = {1.0f, 1.0f};

    public:
        //Getters
        Bounds getBounds() const;

        //Setters

    public:
        //! OBSOLETE: Cannot be used directly
        void setSize(float width, float height) = delete;
        void setSize(const sf::Vector2f &size) = delete;
        void setViewport(const sf::FloatRect &viewport) = delete;

    public:
        void set_viewport(const sf::FloatRect &viewport);
        void set_aspect_ratio( sf::Vector2f aspect );
};

}}

#endif // CAMERA_H
