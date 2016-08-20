#ifndef RENDERER_H
#define RENDERER_H

// c++-includes
#include <algorithm>

// sfml-includes
#include <SFML/Graphics.hpp>

// qt-includes

// user-includes
#include "kernel/component.h"
#include "Core/DataStruct/bounds.h"

class Renderer : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        Renderer();
        ~Renderer();

    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    public:
        virtual void update( sf::Time dt );

    public: // Callbacks
        void onBecameInvisible();
        void onBecameVisible();

    protected:
        // Should have a global AABB of all items inside this renderer

        bool enabled = true; // Does not inherit from behaviour ... but need its own enabled property.

        bool is_visible = false;

        int sortig_layer_id; //Layer of rendering
        QString sorting_layer_name; //Name of the current sorting layer
        unsigned int sorting_order; //Order of the renderer inside the sorting order.

        bool receive_shadows; // Does it receive any shadows

    public:
        //Getters
        virtual Bounds getBounds();
        bool isEnabled();
};

#endif // RENDERER_H
