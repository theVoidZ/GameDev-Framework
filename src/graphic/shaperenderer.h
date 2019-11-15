#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

// user-includes
#include "renderer.h"

class ShapeRenderer : public gdf::graphic::Renderer
{
    public:
        ShapeRenderer();
        ~ShapeRenderer();

    public:
        void setShape(sf::Drawable *shape);
};

#endif // SHAPERENDERER_H
