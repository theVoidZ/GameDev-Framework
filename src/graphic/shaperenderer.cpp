#include "shaperenderer.h"

ShapeRenderer::ShapeRenderer()
{

}

ShapeRenderer::~ShapeRenderer(){

}

void ShapeRenderer::setShape(sf::Drawable *shape){
    drawable_ = shape;
}
