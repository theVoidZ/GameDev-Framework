#include "operators.h"

#include "hierarchy.h"
#include "gameobject.h"
#include "chrono.h"

std::ostream& operator<<( std::ostream& out, sf::Time time ){
    out << time.asMilliseconds() ;
    return out;
}

std::ostream &operator<<(std::ostream &os, sf::Vector2f const &v) {
    return os << "(" << v.x << ", " << v.y << ")";
}

std::ostream& operator<<(std::ostream &os, gdf::kernel::Hierarchy const &h){
    if( h.game_object() != nullptr ){
        return os << "H:" << h.game_object()->name();
    }else{
        return os << "H: none";
    }
}

std::ostream& operator<<(std::ostream &os, gdf::kernel::tracker_ptr< gdf::kernel::Hierarchy> const &h){
    if( h.expired() )
        return os;

    if( h.get()->game_object() != nullptr ){
        return os << "H:" << h.get()->game_object()->name();
    }else{
        return os << "H: none";
    }
}

std::ostream& operator<<(std::ostream &os, gdf::kernel::GoTag const &h){
    if( gdf::kernel::GoTag::Default == h ){
        return os << "Default";
    }else{
        return os;
    }
}

std::ostream& operator<<(std::ostream &os, gdf::kernel::GoLayer const &h){
    if( gdf::kernel::GoLayer::Default == h ){
        return os << "Default";
    }else if( gdf::kernel::GoLayer::Ground == h ){
        return os << "Ground";
    }else if( gdf::kernel::GoLayer::Air == h ){
        return os << "Air";
    }else{
        return os;
    }
}

std::ostream& operator<<(std::ostream &os, gdf::temporal::ChronoPlayStatus const &h){
    if( gdf::temporal::ChronoPlayStatus::FORWARD == h ){
        return os << "Forward";
    }else if( gdf::temporal::ChronoPlayStatus::BACKWARD == h ){
        return os << "Backward";
    }else if( gdf::temporal::ChronoPlayStatus::STOPPED == h ){
        return os << "Stopped";
    }else{
        return os;
    }
}
