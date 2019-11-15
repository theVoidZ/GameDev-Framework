#include "audioclip.h"

namespace gdf {
namespace audio {

AudioClip::AudioClip()
    :Resource()
{

}

AudioClip::AudioClip(const AudioClip& buf)
    :Resource(buf), sf::SoundBuffer(buf){
//    std::cout << "AudioClip::copy ctor " << std::endl;
}

AudioClip::~AudioClip(){

}

void AudioClip::init(std::string file_name){
    loadFromFile( file_name );
}

}}
