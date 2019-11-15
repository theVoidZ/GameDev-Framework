#ifndef ANIMATORCONTROLLER_H
#define ANIMATORCONTROLLER_H

#include <vector>
#include <map>
#include <string>

#include "object.h"
#include "animatorcontrollerlayer.h"

namespace gdf {
namespace animation{


class AnimatorControllerLayer;
class AnimationClip;

class AnimatorController
{
    public:
        AnimatorController();

    public:
        template< typename T >
        void addParameter( std::string arg_name, T value );

    public:
        // Restrict parameters to primitive types.
        template< typename T >
        void setParameter( std::string arg_name, T value );

        template< typename T >
        T getParameter(std::string arg_name);

    public:
        //Belongs to RuntimeController
//        std::list<AnimationClip*> animation_clips;

        std::vector<AnimatorControllerLayer*> layers;
        std::map<std::string, void* > parameters; // Make a class that inherits this type ( map< string, void* > )
};

template< typename T >
void AnimatorController::addParameter(std::string arg_name, T value){
    T* v = new T;
    *v = value;
    parameters[arg_name] = v;

}

template< typename T >
void AnimatorController::setParameter(std::string arg_name, T value ){
    parameters[arg_name] = &value;
}

template< typename T >
T AnimatorController::getParameter(std::string arg_name){
    auto it = parameters.find(arg_name);
    if( it != parameters.end() ){
        return *(T*)(it->second);
    }
}

}}


#endif // ANIMATORCONTROLLER_H
