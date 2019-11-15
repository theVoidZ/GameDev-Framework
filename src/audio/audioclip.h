#ifndef AUDIOCLIP_H
#define AUDIOCLIP_H

// c++-includes
#include <string>
#include <string.h>
#include <iostream>

// sfml-includes
#include <SFML/Audio/SoundBuffer.hpp>

// qt-includes

// user-includes
#include "resource.h"


namespace gdf {
namespace audio {


class AudioClip : public Resource, public sf::SoundBuffer
{
    public:
        AudioClip();
        AudioClip(const AudioClip& buf);

        ~AudioClip();

    public:
        void init( std::string file_name );
};

}}

#endif // AUDIOCLIP_H
