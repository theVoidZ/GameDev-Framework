#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <memory>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>

#include <SFML/System/Time.hpp>

#include "tracker_ptr.h"
#include "component.h"

#include "terminal_colors.h"

namespace gdf {
namespace audio {

class AudioClip;
class AudioListener;


class AudioSource : public gdf::kernel::Component
{
    public:
        AudioSource();

    public:
        void init();
        void update(sf::Time dt);

        void set_audioclip(gdf::kernel::tracker_ptr<AudioClip> audio_clip);


        void play();
        void stop();

    public:
        gdf::kernel::tracker_ptr< AudioClip > clip_tr;
        gdf::kernel::tracker_ptr<sf::Sound> sound_tr;


        AudioListener* listener = nullptr;
        sf::Time playback = sf::Time::Zero;
};

}}
#endif // AUDIOSOURCE_H
