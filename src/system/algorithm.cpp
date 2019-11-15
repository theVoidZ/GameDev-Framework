#include "algorithm.h"

namespace gdf {
namespace system {

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

float Algorithm::length(sf::Vector2f vec){
    return sqrt( pow(vec.x,2) + pow(vec.y, 2) );
}

sf::Time Algorithm::abs(sf::Time time){
    if( time >= sf::Time::Zero ){
        return time;
    }else{
        return -time;
    }

}

void Algorithm::iamalive(){
    std::cout << "i am alive" << std::endl;
}
}}
