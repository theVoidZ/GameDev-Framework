#include "transform.h"


Transform::Transform()
{
    parent = nullptr;
}

Transform::~Transform(){
/*
    // detaches from any parent + parent remove the entry to this transform
    detach(); // May be called to ensure action ( it is already performed )

    if( game_object() != nullptr ){
        this->game_object()->transform_ = nullptr;
    }
*/
}

void Transform::translate( sf::Vector2f vector ){
    this->sf::Transformable::move( vector );
}

void Transform::rotate( float euler_angle ){
    this->sf::Transformable::rotate( euler_angle );
}

void Transform::rotate_around( float euler_angle, sf::Vector2f origin ){
    //Save old origin
    sf::Vector2f old_origin = this->getOrigin();

    //APply new origin & rotate
    this->setOrigin(origin);
    this->sf::Transformable::rotate( euler_angle );

    //Load back the old origin
    this->setOrigin( old_origin );
}

void Transform::look_at( sf::Vector2f location ){
    sf::Vector2f vec = location - Transform::get_position();
    float angle = atan2(vec.y, vec.x) * 180 / M_PI;
    Transform::set_rotation(angle);
}

void Transform::scale( sf::Vector2f factor ){
    this->sf::Transformable::scale( factor );
}

sf::Vector2f Transform::transform_point( sf::Vector2f point ) const{
    return local_to_world_matrix() * point;
}

sf::Vector2f Transform::inverse_transform_point( sf::Vector2f point ) const{
    return world_to_local_matrix() * point;
}

sf::Vector2f Transform::transform_vector( sf::Vector2f vector ) const{
    return transform_point( vector ) - transform_point( sf::Vector2f(0,0) );
}

sf::Vector2f Transform::inverse_transform_vector( sf::Vector2f vector ) const{
    return inverse_transform_point( vector ) - inverse_transform_point( sf::Vector2f(0,0) );
}

const sf::Transform Transform::local_to_world_matrix() const{
    sf::Transform world_t = sf::Transform::Identity;

    for( const Transform* current = this; current != nullptr; current = current->parent ){
        world_t = current->get_matrix() * world_t;
    }
    return world_t;
}

const sf::Transform Transform::world_to_local_matrix() const{
    return local_to_world_matrix().getInverse();
}

const sf::Transform& Transform::get_matrix() const{
    return this->sf::Transformable::getTransform();
}

const sf::Vector2f Transform::forward() const{
    return transform_vector( sf::Vector2f(1,0) );
}

const sf::Vector2f Transform::right() const{
    return transform_vector( sf::Vector2f(0,1) );
}

float Transform::get_world_rotation() const{
    float world_angle = 0;
    const Transform* t = this;

    while( t != nullptr ){
        world_angle += t->get_rotation();
        t = t->parent;
    }

    return world_angle;
}

float Transform::get_rotation() const{
    return sf::Transformable::getRotation();
}

const sf::Vector2f Transform::get_world_position() const{
    return local_to_world_matrix() * sf::Vector2f();
}

const sf::Vector2f Transform::get_position() const{
    return sf::Transformable::getPosition();
}

const sf::Vector2f Transform::get_world_scale() const{
    sf::Vector2f world_scale = sf::Vector2f(1,1);
    const Transform* t = this;

    while( t != nullptr ){
        world_scale += sf::Vector2f( world_scale.x * t->get_scale().x, world_scale.y * t->get_scale().y );
        t = t->parent;
    }

    return world_scale;
}

const sf::Vector2f Transform::get_scale() const{
    return sf::Transformable::getScale();
}


Transform* Transform::getParent() const{
    return parent;
}

const std::list<Transform *>& Transform::getChildren() const{
    return children;
}

Transform* Transform::getRoot() const{
    //! FIXME:
//    return gdf::kernel::GameInfo::game_info->active_scene()->root()->transform();
}

Transform* Transform::getLocalRoot(){
    Transform* current = this;

    while( current->parent != nullptr )
        current = current->parent;

    return current;
}

unsigned int Transform::child_count() const{
    return children.size();
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
