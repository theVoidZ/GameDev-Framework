#ifndef ANIMATORCONTROLLER_H
#define ANIMATORCONTROLLER_H

#include <QVariant>

#include <vector>
#include <map>
#include <string>

#include "kernel/object.h"
#include "Core/Graphic/Animation/animatorcontrollerlayer.h"

class AnimatorControllerLayer;
class AnimationClip;

class AnimatorController /* : public RuntimeAnimatorController*/ : public gdf::kernel::Object
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
        std::list<AnimationClip*> animation_clips;


        std::vector<AnimatorControllerLayer*> layers;
        std::map<std::string, void* > parameters; // Make a class that inherits this type ( map< string, void* > )
};

#include "Core/Graphic/Animation/animatorcontroller.tpp"

#endif // ANIMATORCONTROLLER_H
