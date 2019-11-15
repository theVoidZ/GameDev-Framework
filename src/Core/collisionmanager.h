#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SFML/System/Vector2.hpp>

#include "monobehavior.h"

#include "tracker_ptr.h"

namespace gdf{
namespace kernel{
    class GameObject;
}}

struct PairCollider{

    PairCollider( Collider* col1, Collider* col2 ){
        if( col1 < col2 ){
            first = col1;
            second = col2;
        }else{
            first = col2;
            second = col1;
        }
    }

    Collider* first;
    Collider* second;
};

class CollisionManager : public gdf::kernel::MonoBehavior
{
    public:
        CollisionManager();

        void fixed_update(sf::Time dt);
        PairCollider* find( Collider* col1, Collider* col2 );

    public:
        std::map< PairCollider*, bool > colliding_objects;

};

#endif // COLLISIONMANAGER_H
