#include "animation2.h"

#include "gameobject.h"

#include "animationclip.h"
#include "keyframe.h"
#include "spriterenderer.h"
#include "blendtree.h"
#include "spritesheet.h"
#include "sprite2d.h"

namespace gdf {
namespace animation{

Animation2::Animation2()
{
    currently_playing_sprite = new gdf::graphic::Sprite2D();

    // event: Animation2Clip created
    // event: Sprite2D created
    // Initial values set
}

Animation2::~Animation2(){

}

gdf::graphic::Sprite2D* Animation2::step(sf::Time dt, float param_value){
    dt = dt * (float)play_direction;

    if( blend_tree != nullptr ){
        if( should_plays ){
            clip_index = blend_tree->function_(param_value);
            if( clip_index < blend_tree->clips_.size() && blend_tree->clips_[clip_index] != nullptr ){
                if( pclip_index != clip_index ){
                    pclip_index = clip_index;
                    // When the INDEX CHANGES, save the previous animation index
//                    reset();
//                    should_plays = true;
//                    is_playing = true;
                }

                AnimationClip* clip = blend_tree->clips_[clip_index];
                play_back += dt;

                index = clip->get_frame( play_back.asMilliseconds() );
                if( index >= 0 && index < clip->keyframes.size() ){
                    if( pindex != index ){
                        pindex = index;

                        clip->keyframes[index]->fire_event(nullptr);

                        // a change in frame happened
                        // Engage in a new frame & change sprite
                        sf::IntRect rect;
                        gdf::kernel::tracker_ptr< gdf::graphic::SpriteSheet > ssheet = clip->tiles[ clip->keyframes[index]->sprite_id ];
                        rect = ssheet.get()->sheet_boundaries[ clip->keyframes[index]->frame_id ];

                        currently_playing_sprite->setTexture2D( clip->tiles[ clip->keyframes[index]->sprite_id ].get()->texutre2d );
                        currently_playing_sprite->setTextureRect( rect );
                        currently_playing_sprite->setOrigin( clip->tiles[ clip->keyframes[index]->sprite_id ].get()->pivot_ );

                        //std::cout << "Playing: " << blend_tree->clips_[clip_index]->name() << ", clip: " << clip_index << ", frame: " << index << ", playback: " << play_back << std::endl;

                        return currently_playing_sprite;

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
                        }else if( wrap_mode == WrapMode::ClampForever ){
                            sf::Time goto_time = sf::milliseconds( clip->keyframes[clamp_index]->frame_rate_cumulative - clip->keyframes[clamp_index]->frame_rate );
                            play_back = goto_time;
                        }

                    }
                }
            }else{
                std::cout << "else:  clip_index < blend_tree->clips_.size() && blend_tree->clips_[clip_index] != nullptr" << std::endl;
            }
        }
        return currently_playing_sprite;
    }else{
        return nullptr;
    }
}

void Animation2::play(){
    if( !is_playing ){
        is_playing = true;
        should_plays = true;
    }
}

void Animation2::stop(){
    if( is_playing ){
        is_playing = false;
        should_plays = false;

    }
}

void Animation2::reset(){
    // When a new animation starts ( changing between blendTree's clips )
    play_back = sf::Time::Zero;
}

sf::RectangleShape Animation2::get_hitbox(){
    if( blend_tree != nullptr ){
        if( clip_index >= 0 && clip_index < blend_tree->clips_.size() ){
            gdf::animation::AnimationClip* clip = blend_tree->clips_[clip_index];
            if( clip != nullptr ){
                if( index >= 0 && index < clip->keyframes.size() ){
                    if( clip->keyframes[index] != nullptr ){
                        sf::RectangleShape rect = clip->keyframes[ index ]->aabb;
                        rect.move(clip->keyframes[ index ]->offset);
                        rect.setOutlineColor( sf::Color::Blue );
                        rect.setOutlineThickness(2);
                        return rect;
                    }
                }
            }
        }
    }
    return sf::RectangleShape();
}

}}
