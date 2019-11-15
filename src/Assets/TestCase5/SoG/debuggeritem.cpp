#include "debuggeritem.h"

#include "gameobject.h"
#include "animator.h"
#include "animatorstate.h"
#include "animationclip.h"
#include "animation2.h"
#include "blendtree.h"
#include "keyframe.h"

DebuggerItem::DebuggerItem()
{

}

void DebuggerItem::init(){

}

void DebuggerItem::update(sf::Time dt){
    if( animator == nullptr ){
        animator = game_object()->get_component<gdf::animation::Animator>();
    }


}

void DebuggerItem::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    if(animator != nullptr ){
        if(animator->current_state != nullptr ){
            gdf::animation::Animation2* anim = animator->current_state->animation_;
            if( anim != nullptr ){
                target.draw( anim->get_hitbox(), states);
            }

        }
    }
}
