#include "animation.h"

#include "gameobject.h"

#include "animationclip.h"
#include "keyframe.h"
#include "spriterenderer.h"

#include "spritesheet.h"
#include "sprite2d.h"

#include "resourcemanager.h"

namespace gdf {
namespace animation{

Animation::Animation()
{
    currently_playing_sprite = new gdf::graphic::Sprite2D();

    // event: AnimationClip created
    // event: Sprite2D created
    // Initial values set
}

Animation::~Animation(){

}

void Animation::verbose(){

}

void Animation::init(){
    sprt_rend = this->game_object()->get_component<gdf::graphic::SpriteRenderer>();
}

void Animation::update(sf::Time dt){
    //! NOTE: by default, when used as behaviour
    animate_clip(dt);
}

void Animation::animate_clip(sf::Time dt){

    dt = dt * (float)play_direction;

    if( clip != nullptr ){
        if( should_plays ){
            play_back += dt;

            index = clip->get_frame( play_back.asMilliseconds() );
            if( index >= 0 && index < clip->keyframes.size() ){
                if( pindex != index ){
//                    std::cout << BOLD << index << ":" << play_back.asMilliseconds() << RESET << std::endl;
                    pindex = index;
                    // a change in frame happened
                    // Engage in a new frame & change sprite
                    if( sprt_rend == nullptr ){
                        sprt_rend = this->game_object()->get_component<gdf::graphic::SpriteRenderer>();
                    }

                    if( sprt_rend != nullptr ){
                        sf::IntRect rect;
                        gdf::kernel::tracker_ptr< gdf::graphic::SpriteSheet > ssheet = clip->tiles[ clip->keyframes[index]->sprite_id ];
                        rect = ssheet.get()->sheet_boundaries[ clip->keyframes[index]->frame_id ];

                        currently_playing_sprite->setTexture2D( clip->tiles[ clip->keyframes[index]->sprite_id ].get()->texutre2d );
                        currently_playing_sprite->setOrigin( clip->tiles[ clip->keyframes[index]->sprite_id ].get()->pivot_ );
                        currently_playing_sprite->setTextureRect( rect );
                        sprt_rend->setSprite2D( currently_playing_sprite );
                    }
                }else{
                    // Nothing to do, still on the same index
                }
            }else{
//                std::cout << index << "?" << clip->keyframes.size() << std::endl;
                if( index < 0 ){
                    if( wrap_mode == WrapMode::PingPong ){
                        //Return from PingPong
                        stop();
                    }
                }else if( index >= clip->keyframes.size() ){
                    if( wrap_mode == WrapMode::Once ){
                        // do not reset the playback time
                        stop();
                    }else if( wrap_mode == WrapMode::Loop ){
                        play_back = sf::Time::Zero;
                    }else if( wrap_mode == WrapMode::PingPong ){
                        play_direction = -play_direction;
                    }else if( wrap_mode == WrapMode::ClampForever ){
                        sf::Time goto_time = sf::milliseconds( clip->keyframes[clamp_index]->frame_rate_cumulative - clip->keyframes[clamp_index]->frame_rate );
                        play_back = goto_time;
                    }

                }
            }
        }
    }
}

void Animation::play(){
    if( !is_playing ){
        is_playing = true;
        should_plays = true;
    }
}

void Animation::stop(){
    if( is_playing ){
        is_playing = false;
        should_plays = false;

    }
}

void Animation::reset(){
    // When a new animation starts ( changing between blendTree's clips )
    play_back = sf::Time::Zero;
}

//! PRIVATE SETTERS
void Animation::set_is_playing(bool val){
    is_playing = val;
}

void Animation::set_should_plays(bool val){
    should_plays = val;
}

void Animation::set_play_back(sf::Time play_b){
    play_back = play_b;
}

void Animation::set_play_direction(short play_dir){
    play_direction = play_dir;
}

}}
