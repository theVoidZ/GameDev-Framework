#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H

#include <list>
#include <SFML/Audio.hpp>

#include "tracker_ptr.h"
#include "component.h"

namespace gdf {
namespace audio {

class AudioListener : public gdf::kernel::Component
{
    public:
        AudioListener();
        ~AudioListener();

    public:
        std::list< gdf::kernel::tracker_ptr<sf::Sound> > sounds_;
};

}}

#endif // AUDIOLISTENER_H
