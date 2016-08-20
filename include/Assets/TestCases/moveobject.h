#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/System/monobehavior.h"

class MoveObject : public MonoBehavior
{
    Q_OBJECT
    public:
        MoveObject();

        void update(sf::Time dt);

        void on_text_entered(const sf::Event &event);

        void on_closed(const sf::Event &event);

        void on_mouse_button_pressed(const sf::Event &event);

        void on_key_pressed(const sf::Event &event);
        void on_key_released(const sf::Event &event);
    public:

};

#endif // MOVEOBJECT_H
