#ifndef TRANSFORM_H
#define TRANSFORM_H

// c++-includes
#include <list>

// sfml-includes
#include <SFML/System.hpp>

// qt-includes
#include <iostream>

// user-includes
#include "kernel/component.h"

//! Transform is a component that defines a position, a rotation and a scale for a game object in 2d-coordinates.
/*!
 * Every game object object in a scene has a Transform. \n
 * It's used to store and manipulate the position, rotation and scale of the game object.
 * It is structured hierarchically, each game object can have a parent and a list of children.
 */
class Transform final : public gdf::kernel::Component,
                        public sf::Transformable //! WARNING: private to public
{
    Q_OBJECT
    public:
        //! Default constructor
        Transform();
        ~Transform();

    public:
        // Indexing


    public:
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

        //! Rotate the transform by angle around a custom center.
        /*!
         * Unlike rotate, this method rotate around a custom 'temporary' center specified using 'origin'.
         * \param angle Amount of rotation in degree to rotate with.
         * \param origin Center of rotation.
         */
        void rotate_around( float euler_angle, sf::Vector2f origin );

        //! Set the rotation of the transform at a specific angle.
        /*!
         * Make the forward vector (x_axis) of the transform points to the lookAt location.
         * \param location Look at location.
         */
        void look_at( sf::Vector2f location );

        //! Scales the transform by factor.
        /*!
         * Unlike setScale, This method scales the current dimensions of the transform by specified factor each call.
         * \param factor Scale factor.
         */
        void scale( sf::Vector2f factor );

        // Matrices
        //! Transform local coordinates of a point to world coordinate
        sf::Vector2f transform_point( sf::Vector2f point ) const;

        //! Transform world coordinates of a point to local coordinate
        sf::Vector2f inverse_transform_point( sf::Vector2f point ) const;

        //! Transform local coordinates of a vector to world coordinate
        sf::Vector2f transform_vector( sf::Vector2f vector ) const;

        //! Transform world coordinates of a vector to local coordinate
        sf::Vector2f inverse_transform_vector( sf::Vector2f vector ) const;

    //! WARNING: Changed to public
    public:
        //! Parent of the transform.
        Transform* parent;

        //! Children attached to this transform.
        std::list< Transform* > children;

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

        //! Its own transform, from sf::Transformable
        const sf::Transform& get_matrix() const;

        //!
        const sf::Vector2f forward() const; //Forward  - x:axis of the transform in world coordinates
        const sf::Vector2f right() const; //Right - y:axis of the transform in world coordinates

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

    // Getters
        //!
        Transform* getParent() const;

        //!
        const std::list<Transform *>& getChildren() const;

        //! Returns the topmost transform in the hierarchy.
        /*!
         * This methods does return systematically the root of the scene ( hierarchy ).
         * \return Topmost transform
         */
        Transform* getRoot() const;

        //! Returns the top-most transform that is connected to this transform.
        /*!
         * This methods does not return systematically the root of the scene ( hierarchy )
         * but returns the local root of this transform.
         * \return Topmost transform
         */
        Transform* getLocalRoot();

        //! Returns the number of children
        unsigned int child_count() const;

    //Setters
        // Will uses intelligently attachChild and detachChild depending on the value of the parameter.
        void set_position( sf::Vector2f pos );
        void set_world_position( sf::Vector2f pos );

        void set_rotation(float euler_angle );
        void set_world_rotation( float euler_angle );

        void set_scale( sf::Vector2f factor );

};

#endif // TRANSFORM_H
