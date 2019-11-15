#ifndef CAMFOLLOWER_H
#define CAMFOLLOWER_H

#include <SFML/System/Vector2.hpp>

#include "monobehavior.h"

#include "tracker_ptr.h"

namespace gdf {
namespace kernel {

class GameObject;

}}


class CamFollower : public gdf::kernel::Component
{
    public:
        CamFollower();

    public:
        void init();
        void update(sf::Time dt);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        gdf::kernel::tracker_ptr< gdf::kernel::GameObject > following_go;
        gdf::kernel::Camera* cam = nullptr;
};

#endif // CAMFOLLOWER_H
