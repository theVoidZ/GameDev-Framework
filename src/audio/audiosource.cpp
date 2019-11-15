#include "audiosource.h"

#include "audiolistener.h"
#include "audioclip.h"

#include "gameobject.h"
#include "transform.h"

#include "algorithm.h"

namespace gdf {
namespace audio {

AudioSource::AudioSource()
{

}

void AudioSource::init(){

}

void AudioSource::update(sf::Time dt){
    if( !sound_tr.expired() ){
//        if( sound_tr.get()->getPlayingOffset() < sf::seconds(1) ){
//            sound_tr.get()->setPitch( 0.85 );
//        }else{
//            sound_tr.get()->setPitch( 1.5 );

//        }
        if( listener != nullptr ){
//            float distance = gdf::system::Algorithm::length( listener->game_object()->transform().get()->get_position() - game_object()->transform().get()->get_position() );
//            if( distance > 300 ){
//                sound_tr.get()->setVolume(0);
//            }else{
//                sound_tr.get()->setVolume( (-100/300.f)*distance + 100 );
//            }

            //Use clamp function

        }

        std::cout << sound_tr.get()->getPlayingOffset().asMilliseconds() << std::endl;
        if( sound_tr.get()->getStatus() == sf::Sound::Status::Stopped ){
            playback = sound_tr.get()->getPlayingOffset();
            sound_tr.reset();
        }
    }
}

void AudioSource::set_audioclip(gdf::kernel::tracker_ptr<AudioClip> audio_clip){
    clip_tr = audio_clip;
}

void AudioSource::play(){
    if( listener != nullptr ){
        if( clip_tr.get() != nullptr ){

            if( !sound_tr.expired() ){

            }else{
                sound_tr = gdf::kernel::tracker_ptr<sf::Sound>( new sf::Sound() );
                sound_tr.get()->setBuffer(*clip_tr.get());

                listener->sounds_.push_back( sound_tr );

//                sound_tr.get()->setLoop(true);
                sound_tr.get()->setPlayingOffset( playback );
                sound_tr.get()->setVolume(45);
                sound_tr.get()->play();
            }
        }else{
            std::cout << BOLD << BYELLOW << FRED << "No audio clip is attached to the audio source." << RESET << std::endl;
        }

    }else{
        std::cout << BOLD << BYELLOW << FRED << "No audio listener to play sounds." << RESET << std::endl;
    }
}

void AudioSource::stop(){
    if( listener != nullptr ){
        playback = sound_tr.get()->getPlayingOffset();

        sound_tr.get()->stop();
        sound_tr.reset();
    }
}

}}
