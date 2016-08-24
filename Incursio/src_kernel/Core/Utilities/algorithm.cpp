#include "algorithm.h"

//#include "Core/Graphic/Animation/StateMachine/animatorcondition.h"


bool Algorithm::evaluateCondition(void* v, AnimatorCondition* cond){
    /*
    // std::cout << *(float*)v << std::endl;

    if( cond->mode == AnimatorConditionMode::Equals ){
        if( *(float*)v == cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == AnimatorConditionMode::NotEquals ){
        if( *(float*)v != cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == AnimatorConditionMode::Greater ){
        if( *(float*)v > cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == AnimatorConditionMode::Less ){
        if( *(float*)v < cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    //Used for booleans
    if( cond->mode == AnimatorConditionMode::If ){
        if( *(bool*)v == cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    if( cond->mode == AnimatorConditionMode::IfNot ){
        if( *(bool*)v != cond->threshold ){
            return true;
        }else{
            return false;
        }
    }
    return false;
    */
}

sf::Vector2f Algorithm::min(sf::Vector2f p1, sf::Vector2f p2){
    return sf::Vector2f( p1.x < p2.x ? p1.x : p2.x , p1.y < p2.y ? p1.y : p2.y);
}

sf::Vector2f Algorithm::max(sf::Vector2f p1, sf::Vector2f p2){
    return sf::Vector2f( p1.x > p2.x ? p1.x : p2.x , p1.y > p2.y ? p1.y : p2.y);
}

sf::Time Algorithm::clamp(const sf::Time &t, sf::Time min, sf::Time max){
    if( t < min )
        return min;
    else if( t > max )
        return max;
    else
        return t;
}
