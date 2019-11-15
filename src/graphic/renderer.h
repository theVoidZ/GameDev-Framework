#ifndef RENDERER_H
#define RENDERER_H

// c++-includes
#include <algorithm>

// sfml-includes
#include <SFML/Graphics.hpp>

// qt-includes

// user-includes
#include "component.h"
#include "bounds.h"

namespace gdf {

namespace graphic {


class Renderer : public gdf::kernel::Component
{
    public:
        Renderer();
        ~Renderer();

    public:
        virtual void update( sf::Time dt );
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;


    public:
//        void set_drawable(sf::Drawable *drawable);

    public: // Callbacks
        void onBecameInvisible();
        void onBecameVisible();

    public:
        //Getters
        virtual Bounds getBounds() const;
        virtual Bounds getGlobalBounds() const;

    protected:
        // Should have a global AABB of all items inside this renderer

        // true when visible on at least on camera, false, when is not visible on every camera
        bool visible_ = false;

//        int sortig_layer_id; //Layer of rendering
//        std::string sorting_layer_name; //Name of the current sorting layer
//        unsigned int sorting_order; //Order of the renderer inside the sorting order.

//        bool receive_shadows; // Does it receive any shadows

    public:
        sf::Drawable* drawable_ = nullptr;

};

}}

#endif // RENDERER_H
