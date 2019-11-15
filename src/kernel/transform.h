#ifndef TRANSFORM_H
#define TRANSFORM_H

// c++-includes
#include <list>
#include <math.h>

// sfml-includes
#include <SFML/System.hpp>

// qt-includes
#include <iostream>

// user-includes
#include "component.h"

namespace gdf {
namespace kernel {

//! Transform is a component that defines a position, a rotation and a scale for a game object in 2d-coordinates.
/*!
 * Every game object object in a scene has a Transform. \n
 * It's used to store and manipulate the position, rotation and scale of the game object.
 * It is structured hierarchically, each game object can have a parent and a list of children.
 */
class Transform final : public gdf::kernel::Component,
                        private sf::Transformable
{
    friend class gdf::kernel::GameObject;

    public:
        //! Default constructor
        Transform();
        ~Transform();

        void init();

    public:
        // Indexing


    public:
        sf::Vector2f transform_point( sf::Vector2f point ) const;

        //Transform manipulation
        //! Translate the current transform by 'vector'
        /*!
         * \param vector Amount in pixel to translate by.
         */
        void translate( sf::Vector2f vector );

        //! Rotate the transform by 'angle'
        /*!
         * Default rotation center is the origin of the transform.
         * \param angle Amount of rotation in degree to rotate with.
         */
        void rotate(float euler_angle );

        //! Scales the transform by factor.
        /*!
         * Unlike setScale, This method scales the current dimensions of the transform by specified factor each call.
         * \param factor Scale factor.
         */
        void scale( sf::Vector2f factor );

    public:
        //! When true, the transform CANNOT change no matter what. Even using setters.
        bool is_static_ = false;

    protected:
        sf::Vector2f local_scale_ = {1.0f, 1.0f};

    public:
        //Getters
        //! getXXX: is relative to the parent
        //! getWorldXXX: is relative to the root

        //! Holds the world transform of this component.
        /*! This method returns the transformation matrix from local to world coordinates.
         * It gathers all transform all along the hierarchy (upward) til it reaches the topmost node which is the root.\n
         * If it encounters a topmost node different from the root, the transformation matrix is built based on the
         * topmost node ( local root ). And it may gives false result in this case. We suggest to check if the node
         * belongs to the hierarchy before invoking this method.
         * \return World transform matrix of this transform
         */
        const sf::Transform local_to_world_matrix() const;

        //! Holds the inverse world transform of the component.
        /*! This method processes exactly the same way as 'localToWorldMatrix' does.\n
         * It computes the inverse of the localToWorldMatrix and returns it.
         * \return Inverse World transform matrix
         */
        const sf::Transform world_to_local_matrix() const;

        //! Return the rotation of the transform in world coordinates.
        float get_world_rotation() const;

        //! Return the rotation of the transform in local coordinates ( based on sf::Transformable )
        float get_rotation() const;

        //! Return the position of the transform in world coordinates
        const sf::Vector2f get_world_position() const;

        //! Return the position of the transform in local coordinates ( based on sf::Transformable )
        const sf::Vector2f get_position() const;

        //! Return the scale of the transform in world coordinates - read only
        const sf::Vector2f get_world_scale() const;

        //! Return the scale of the transform in local coordinates ( based on sf::Transformable )
        const sf::Vector2f get_scale() const;

    //Setters
        // Will uses intelligently attachChild and detachChild depending on the value of the parameter.
        void set_position( sf::Vector2f pos );
        void set_world_position( sf::Vector2f pos );

        void set_rotation(float euler_angle );
        void set_world_rotation( float euler_angle );

        void set_scale( sf::Vector2f factor );

};

}}

#endif // TRANSFORM_H
