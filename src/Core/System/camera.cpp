#include "camera.h"
#include "kernel/gameinfo.h"
#include "Core/System/transform.h"

#include "Core/Exception/nullpointerexception.h"
#include "Core/Exception/invalidreturn.h"

Camera::Camera(){
    main_win_size = (sf::Vector2f)gdf::kernel::GameInfo::game_info->sf::RenderWindow::getSize();
    viewport_position = sf::Vector2f(0,0);
    viewport_size = main_win_size;

    viewport_size = sf::Vector2f(640,480);


    viewport_extent = sf::Vector2f(viewport_size.x/2, viewport_size.y/2);


    view.reset( sf::FloatRect( 0, 0 , viewport_size.x, viewport_size.y));
    // Positionning and size according to the screen
    view.setViewport( sf::FloatRect( viewport_position.x/main_win_size.x, viewport_position.y/main_win_size.y,
                                     viewport_size.x/main_win_size.x, viewport_size.y/main_win_size.y ) );
}

Camera::~Camera(){

}

void Camera::update(sf::Time){

}

sf::Vector2f Camera::screenToViewport(sf::Vector2f point) const{
    return gdf::kernel::GameInfo::game_info->mapPixelToCoords( (sf::Vector2i)point, view);
}

sf::Vector2f Camera::viewportToScreen(sf::Vector2f point) const{
    return (sf::Vector2f)gdf::kernel::GameInfo::game_info->mapCoordsToPixel( point, view);
}

sf::Vector2f Camera::screenToWorld(sf::Vector2f point) const{
    return viewportToWorld( screenToViewport(point) );
}

sf::Vector2f Camera::worldToScreen(sf::Vector2f point) const{
    return viewportToScreen( worldToViewport(point) );
}

sf::Vector2f Camera::viewportToWorld(sf::Vector2f point) const{
    return point - gdf::kernel::GameInfo::game_info->active_scene()->root()->transform()->get_position();
}

sf::Vector2f Camera::worldToViewport(sf::Vector2f point) const{
    return point + gdf::kernel::GameInfo::game_info->active_scene()->root()->transform()->get_position() ;
}

void Camera::move( sf::Vector2f pos ){
    view.move(pos);
}

void Camera::rotate( float angle ){
    view.rotate( angle );
}

void Camera::zoom( float ){

}

sf::View& Camera::getView(){
    return view;
}

Bounds Camera::getBounds() const{
    Bounds b;
    b.setMinMax( view.getCenter() - viewport_extent, view.getCenter() + viewport_extent );
    return b;
}

void Camera::setViewportPosition(sf::Vector2f view_port_pos){
    viewport_position = view_port_pos;
    view.setViewport( sf::FloatRect( viewport_position.x/main_win_size.x, viewport_position.y/main_win_size.y,
                                     viewport_size.x/main_win_size.x, viewport_size.y/main_win_size.y ) );
}

void Camera::setCameraLocation(sf::Vector2f location){
    view.setCenter( location + viewport_extent );
}

