#include "animation.h"

#include "Core/Graphic/Animation/animationclip.h"
#include "Core/Graphic/Animation/blendtree.h"
#include "Core/Graphic/Animation/keyframe.h"
#include "Core/Graphic/spriterenderer.h"

#include "time_management/eventanimationstatechanged.h"
#include "time_management/timekeeper.h"

#include "resource_management/spritetile.h"

#include "time_management/chrono.h"

Animation::Animation()
{
    index = 0;
    clamp_index = 0;
    play_back = sf::Time::Zero;
    elapsed_frame_time = sf::Time::Zero;
    should_plays = false;
    reverse_play = false;

    clip = new AnimationClip();
    blend_tree = new BlendTree();
    wrap_mode = WrapMode::Once;
}

void Animation::update(sf::Time dt){
    //! NOTE: by default, when used as behaviour
    animate_clip(dt);
}

void Animation::animate_clip(sf::Time dt){

    if( clip != nullptr ){
        if( should_plays ){
            if( index >= 0 && index < clip->keyframes.size() ){
                if( elapsed_frame_time.asSeconds() < clip->keyframes[index]->frame_rate ){
                    //Waiting time to timeout
                    elapsed_frame_time += dt;
                }else{
                    //Engaging in a new frame
                    //**********Change the SpriteRenderer HERE!
                    SpriteRenderer* sprt_rend = this->getComponent< SpriteRenderer >();
                    if( sprt_rend != nullptr ){
                        sprt_rend->sfsprite.setTexture( *clip->tiles[ clip->keyframes[index]->sprite_id ]->tex_tile[ clip->keyframes[index]->frame_id ] );
                    }

                    //std::cout << "Playing, frame.index=" << index << std::endl;

                    //Add extra time to 'elapsed_frame_time' of the next frame. and move onto the next frame.
                    elapsed_frame_time = elapsed_frame_time - sf::seconds(clip->keyframes[index]->frame_rate);
                    if( reverse_play ){ // used for pingpong ?
                        index--;
                    }else{
                        index++;
                    }
                }
                play_back += dt;
            }else{
                if( wrap_mode == WrapMode::Once ){
                    stop();
                }else if( wrap_mode == WrapMode::Loop ){
                    should_plays = true;
                    index = 0;
                    play_back = sf::Time::Zero;
                    //elapsed time is kept from the previous iteration.
                }else if( wrap_mode == WrapMode::PingPong ){
                    if( reverse_play == false && index == clip->keyframes.size() ){
                        //Forward play
                        reverse_play = true;
                        index--;
                    }else if( reverse_play == true && index < 0){
                        //Backward play
                        //Stop
                        reverse_play = false;
                        stop();
                        elapsed_frame_time = sf::Time::Zero;
                    }
                }else if( wrap_mode == WrapMode::ClampForever ){
                    should_plays = true;
                    index = clamp_index;
                    play_back = sf::Time::Zero;
                    //elapsed time is kept from the previous iteration.
                }
            }
        }
    }
}

void Animation::animate_blend_tree(sf::Time dt){
    if( blend_tree != nullptr ){

    }
}

void Animation::play(){
    play_back = sf::Time::Zero;
    index = 0;
    elapsed_frame_time = sf::Time::Zero;
    should_plays = true;
    //Set the first Sprite to the Sprite Renderer.
}

void Animation::play_reverse(){
    play_back = sf::Time::Zero;
    index = clip->keyframes.size()-1;
    elapsed_frame_time = sf::Time::Zero;
    should_plays = true;
    reverse_play = true;
    //Set the first Sprite to the Sprite Renderer.

}



void Animation::stop(){
    should_plays = false;
    index = 0;
    play_back = sf::Time::Zero;

    Chrono* ch = game_object()->getComponent<Chrono>();
    if( ch != nullptr ){
        //! Callback for timekeeper
        foreach (TimeKeeper* tk, game_object()->getComponentsOfType<TimeKeeper>() ) {
            tk->onAnimationStateChanged(this, 1, 0, ch->lifetime.asMilliseconds() );
        }
    }

}
