#ifndef MYCOMPONENT_H
#define MYCOMPONENT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "kernel/component.h"

class MyComponent : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        MyComponent();
		void init();
		
        void update(sf::Time dt);
        
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        
    private:
    	sf::Texture tex;
    	sf::Sprite comp_sprt;

};

#endif // MYCOMPONENT_H
