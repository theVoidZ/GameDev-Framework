#include "transform.h"

#include "gameobject.h"

namespace gdf {
namespace kernel{

Transform::Transform()
{
//    std::cout << BRED << "TRANSFORM INVOKED" << RESET << std::endl;

}

Transform::~Transform(){
//    std::cout << BYELLOW << BOLD << "~Transform" << RESET << std::endl;
//    std::cout << "TRANSFORM IS DESTROYED - SPECIFIC EVENT GOES HERE " << std::endl;

}

void Transform::init(){
    if( game_object() != nullptr ){
        game_object()->transform();
    }
}

sf::Vector2f Transform::transform_point( sf::Vector2f point ) const{
    return local_to_world_matrix() * point;
}

void Transform::translate( sf::Vector2f vector ){
    this->sf::Transformable::move( vector );
}

void Transform::rotate( float euler_angle ){
    this->sf::Transformable::rotate( euler_angle );
}

void Transform::scale( sf::Vector2f factor ){
    this->sf::Transformable::scale( factor );
    local_scale_ = { local_scale_.x * factor.x, local_scale_.y * factor.y };
}

const sf::Transform Transform::local_to_world_matrix() const{
    //! FIXME:
    sf::Transform world_t = sf::Transform::Identity;

    if( game_object()->scene()->root().expired() ){
        std::cout << BOLD << FRED << "Root GameObject invalid" << RESET << std::endl;
        return world_t;
    }

    if( !game_object()->hierarchy().expired() ){
        Hierarchy* h = game_object()->hierarchy().get();
        for( const Hierarchy* current = h; current != game_object()->scene()->root().get()->hierarchy().get(); current = current->parent() ){

            //! WARNING: These case are rare, to be managed
            if( current->game_object()->transform().expired() ){
                continue;
            }
            if( current == nullptr ){
                // ERROR
                std::cout << FRED << BOLD << "Attempting to get global position from a non-attached game object" << RESET << std::endl;
            }
            world_t = current->game_object()->transform().get()->getTransform() * world_t;
        }
    }
    return world_t;
}

const sf::Transform Transform::world_to_local_matrix() const{
    return local_to_world_matrix().getInverse();
}

float Transform::get_world_rotation() const{
    float world_r = 0.f;

    if( game_object()->scene()->root().expired() ){
        std::cout << BOLD << FRED << "Root GameObject invalid" << RESET << std::endl;
        return world_r;
    }

    if( !game_object()->hierarchy().expired() ){
        Hierarchy* h = game_object()->hierarchy().get();
        for( const Hierarchy* current = h; current != game_object()->scene()->root().get()->hierarchy().get(); current = current->parent() ){

            //! WARNING: These case are rare, to be managed
            if( !current->game_object()->transform().expired() ){
                continue;
            }
            if( current == nullptr ){
                // ERROR
                std::cout << FRED << BOLD << "Attempting to get global rotation from a non-attached game object" << RESET << std::endl;
            }
            world_r += current->game_object()->transform().get()->get_rotation();
        }
    }
    return world_r;
}

float Transform::get_rotation() const{
    return sf::Transformable::getRotation();
}

const sf::Vector2f Transform::get_world_position() const{
    return local_to_world_matrix() * sf::Vector2f() ;
}

const sf::Vector2f Transform::get_position() const{
    return sf::Transformable::getPosition();
}

const sf::Vector2f Transform::get_world_scale() const{
    //! FIXME:
    sf::Vector2f world_s = {1.0f, 1.0f };

    if( game_object()->scene()->root().expired() ){
        std::cout << BOLD << FRED << "Root GameObject invalid" << RESET << std::endl;
        return world_s;
    }

    if( !game_object()->hierarchy().expired() ){
        Hierarchy* h = game_object()->hierarchy().get();
        for( const Hierarchy* current = h; current != game_object()->scene()->root().get()->hierarchy().get(); current = current->parent() ){

            //! WARNING: These case are rare, to be managed
            if( !current->game_object()->transform().expired() ){
                continue;
            }
            if( current == nullptr ){
                // ERROR
                std::cout << FRED << BOLD << "Attempting to get global scale from a non-attached game object" << RESET << std::endl;
            }
            sf::Vector2f v = current->game_object()->transform().get()->get_scale();
            world_s =  sf::Vector2f(world_s.x / v.x , world_s.y / v.y);
        }
    }
    return world_s;
}

const sf::Vector2f Transform::get_scale() const{
    return getScale();
}

void Transform::set_position( sf::Vector2f pos ){
    sf::Transformable::setPosition( pos );
}

void Transform::set_world_position( sf::Vector2f pos ){
    sf::Transformable::move( pos - get_world_position() );
}

void Transform::set_rotation( float euler_angle ){
    sf::Transformable::setRotation( euler_angle );
}

void Transform::set_world_rotation(float euler_angle ){
    sf::Transformable::rotate( euler_angle - get_world_rotation() );
}

void Transform::set_scale( sf::Vector2f factor ){
    sf::Transformable::setScale( factor );
}

}}
