#ifndef SOG_H
#define SOG_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "monobehavior.h"


class Collider;
namespace gdf {

namespace graphic {
class Sprite2D;
}

namespace kernel {
class GameObject;
template <typename T > class tracker_ptr;
class Transform;
}

namespace animation {
class Animator;
class AnimatorTransitionBase;

}}

class SoG : public gdf::kernel::MonoBehavior
{
    public:
        SoG();

    public:
        void init_res();
        void flowchart_1();
        void flowchart_2();
        void flowchart_3();


        void init();
        void update(sf::Time dt);
        void on_key_pressed(const sf::Event &event);
        void on_key_released(const sf::Event &event);

        void on_enter_state(gdf::animation::AnimatorTransitionBase *transition);
        void on_exit_state(gdf::animation::AnimatorTransitionBase *transition);
        void on_enter_collision(Collider *obj1, Collider *obj2);
        void on_stay_collision(Collider *obj1, Collider *obj2);
        void on_exit_collision(Collider *obj1, Collider *obj2);

    public:
        gdf::animation::Animator* animator = nullptr;

        sf::Vector2f velocity = sf::Vector2f();
        float direction = 1;
        bool is_attacking = false;

        sf::Vector2f pvelocity = sf::Vector2f();
        float pdirection = 2;
        bool pis_attacking = false;



        bool control_frozen = false;

        gdf::kernel::tracker_ptr<gdf::kernel::GameObject> Foo_tracker;


    private:
        sf::Time slash_wind_lifetime = sf::milliseconds(2500);
        gdf::graphic::Sprite2D* sprite;
};

#endif // SOG_H
