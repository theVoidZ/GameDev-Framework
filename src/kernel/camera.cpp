#include "camera.h"

#include "gameinfo.h"
#include "gameobject.h"

namespace gdf {
namespace kernel {

Camera::Camera()
    :sf::View()
{
    main_win_size = (sf::Vector2f)gdf::kernel::GameInfo::game_info->sf::RenderWindow::getSize();

//    viewport_position = sf::Vector2f(0,0);
    viewport_size = main_win_size;

    // Inner world: Center : Area to cover stretched on the defined viewport area.
    // Is defined from the viewport first
    this->sf::View::setViewport( sf::FloatRect( 0, 0, 1, 1) );
    this->sf::View::setSize( main_win_size );

}

Camera::~Camera(){

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::init(){
    //! OBSOLETE: Feature removed
    /*
    if( game_object() != nullptr ){
        std::list< gdf::kernel::GameObject*>::iterator it = game_object()->scene()->game_objects().begin();
        for ( it; it != game_object()->scene()->game_objects().end(); it++ ){
            game_objects_visibility_[ (*it)->instance_id() ] = false;
        }
    }
    */
}

void Camera::update(sf::Time){

}

sf::Vector2f Camera::screenToViewport(sf::Vector2f point) const{
    return gdf::kernel::GameInfo::game_info->mapPixelToCoords( (sf::Vector2i)point, *this);
}

sf::Vector2f Camera::viewportToScreen(sf::Vector2f point) const{
    return (sf::Vector2f)gdf::kernel::GameInfo::game_info->mapCoordsToPixel( point, *this);
}

sf::Vector2f Camera::screenToWorld(sf::Vector2f point) const{
    return viewportToWorld( screenToViewport(point) );
}

sf::Vector2f Camera::worldToScreen(sf::Vector2f point) const{
    return viewportToScreen( worldToViewport(point) );
}

sf::Vector2f Camera::viewportToWorld(sf::Vector2f point) const{
    if( game_object()->scene()->root().expired() ){
        std::cout << BOLD << FORANGE << "Cannot perform coordinates conversion, invalid root " << RESET << std::endl;
        return sf::Vector2f();
    }

    gdf::kernel::Transform* t;
    if( ( t = game_object()->scene()->root().get()->transform().get() ) != nullptr ){
        return point - t->get_position();
    }
}

sf::Vector2f Camera::worldToViewport(sf::Vector2f point) const{
    if( game_object()->scene()->root().expired() ){
        std::cout << BOLD << FORANGE << "Cannot perform coordinates conversion, invalid root " << RESET << std::endl;
        return sf::Vector2f();
    }

    gdf::kernel::Transform* t = nullptr ;
    if( ( t = game_object()->scene()->root().get()->transform().get() ) != nullptr ){
        return point + t->get_world_position() + getCenter();
    }else{
        return sf::Vector2f();
    }
}

Bounds Camera::getBounds() const{
    return Bounds::from_center_size( this->getCenter(), this->getSize() );
}

void Camera::set_viewport(const sf::FloatRect &viewport){
    this->sf::View::setViewport( viewport );

    //update view size
    this->sf::View::setSize( {main_win_size.x * this->getViewport().width / aspect_ratio.x, main_win_size.y * this->getViewport().height / aspect_ratio.y} );
/*
    //! NOTE: Update information in GameInfo::viewports from Camera
    gdf::kernel::GameInfo* gi = gdf::kernel::GameInfo::game_info.get();
    std::vector< gdf::kernel::Viewport *>::iterator it = gi->viewports().begin();
    for( it; it != gi->viewports().end(); it++ ){
        if( (*it)->camera == this ){
            (*it)->rect = viewport;
            break;
        }
    }
*/
}

void Camera::set_aspect_ratio(sf::Vector2f aspect){
    aspect_ratio = aspect;
    sf::Vector2f s = { getViewport().width * main_win_size.x, main_win_size.y * this->getViewport().height };
    this->sf::View::setSize( {s.x / aspect.x, s.y / aspect.y} );
}

}}
