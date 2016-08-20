#ifndef GUI_H
#define GUI_H

// c++-includes

// sfml-includes
#include <SFML/Graphics.hpp>

// box2d-includes

// qt-includes

// user-includes

//! Class used to render the Gui
/*!
 * It uses the defaultView of the active GameInfo to render items onto the screen. All the methods are statics,
 * this class should not be instantiated.
 * Allow inheritance to draw complex elements at once
 */
class Gui
{
    private:
        //! Constructor
        Gui();

    public:
        //! Render a circle
        /*!
         * \param radius Radius of the circle in pixels.
         */
        static void drawCircle(float radius);

        static void drawRectangle( float x, float y, float w, float h);

//        static void draw( sf::Drawable item );
};

#endif // GUI_H
