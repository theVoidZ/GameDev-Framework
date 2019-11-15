#include "sog.h"

#include "gameinfo.h"
#include "gameobject.h"
#include "tracker_ptr.h"
#include "hierarchy.h"
#include "resourcemanager.h"
#include "texture2d.h"
#include "spritesheet.h"
#include "spriterenderer.h"
#include "sprite2d.h"

#include "animation.h"
#include "animation2.h"
#include "animationclip.h"
#include "animator.h"
#include "animatorcontroller.h"
#include "animatorcontrollerlayer.h"
#include "animatorstatemachine.h"
#include "animatorstate.h"
#include "animatortransitionbase.h"
#include "animatorcondition.h"
#include "blendtree.h"
#include "transform.h"

#include "operators.h"

#include "chrono.h"
#include "keyframe.h"

#include "collider.h"

SoG::SoG()
{

}

void SoG::init_res(){
    // Loading ( Create a concrete instance of the resource as Texture2D.
    ResourceManager* rm = gdf::kernel::GameInfo::game_info.get()->get_component<ResourceManager>();

    gdf::graphic::Texture2D* hero_image = rm->load_resource<gdf::graphic::Texture2D>("hero_image");
    if( hero_image != nullptr )
        hero_image->init("../media/sog_spritesheet.png");

    gdf::graphic::SpriteSheet* hero_sprite_sheet =rm->load_resource<gdf::graphic::SpriteSheet>("hero_sprite_sheet");
    if( hero_sprite_sheet != nullptr ){
        hero_sprite_sheet->init( rm->get<gdf::graphic::Texture2D>("hero_image"), 4, 24, 24*4);
        hero_sprite_sheet->pivot_ = sf::Vector2f(62, 108);
    }

    //RIGHT
    gdf::animation::AnimationClip* clip_stand_right= rm->load_resource<gdf::animation::AnimationClip>("animc:stand_right");
    clip_stand_right->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_stand_right->add_frame(0, 0, 100);
    clip_stand_right->add_frame(0, 0, 100);

    gdf::animation::AnimationClip* clip_move_right= rm->load_resource<gdf::animation::AnimationClip>("animc:move_right");
    clip_move_right->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_move_right->addFramesInRange(0, 1, 11, 65);

    gdf::animation::AnimationClip* clip_slide_right= rm->load_resource<gdf::animation::AnimationClip>("animc:slide_right");
    clip_slide_right->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_slide_right->addFramesInRange(0, 11, 16, 65);

    gdf::animation::AnimationClip* clip_attack_right= rm->load_resource<gdf::animation::AnimationClip>("animc:attack_right");
    clip_attack_right->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_attack_right->addFramesInRange(0, 16, 24, 45);

    //LEFT
    gdf::animation::AnimationClip* clip_stand_left= rm->load_resource<gdf::animation::AnimationClip>("animc:stand_left");
    clip_stand_left->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_stand_left->add_frame(0, 24+0, 100);
    clip_stand_left->add_frame(0, 24+0, 100);

    gdf::animation::AnimationClip* clip_move_left= rm->load_resource<gdf::animation::AnimationClip>("animc:move_left");
    clip_move_left->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_move_left->addFramesInRange(0, 24+1, 24+10, 65);

    gdf::animation::AnimationClip* clip_slide_left= rm->load_resource<gdf::animation::AnimationClip>("animc:slide_left");
    clip_slide_left->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_slide_left->addFramesInRange(0, 24+11, 24+16, 45);

    gdf::animation::AnimationClip* clip_attack_left= rm->load_resource<gdf::animation::AnimationClip>("animc:attack_left");
    clip_attack_left->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_attack_left->addFramesInRange(0, 24+16, 24+24, 45);

    //UP
    gdf::animation::AnimationClip* clip_stand_up= rm->load_resource<gdf::animation::AnimationClip>("animc:stand_up");
    clip_stand_up->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_stand_up->add_frame(0, 2*24+0, 100);
    clip_stand_up->add_frame(0, 2*24+0, 100);

    gdf::animation::AnimationClip* clip_move_up= rm->load_resource<gdf::animation::AnimationClip>("animc:move_up");
    clip_move_up->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_move_up->addFramesInRange(0, 2*24+1, 2*24+10, 65);

    gdf::animation::AnimationClip* clip_slide_up= rm->load_resource<gdf::animation::AnimationClip>("animc:slide_up");
    clip_slide_up->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_slide_up->addFramesInRange(0, 2*24+11, 2*24+16, 45);

    gdf::animation::AnimationClip* clip_attack_up= rm->load_resource<gdf::animation::AnimationClip>("animc:attack_up");
    clip_attack_up->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_attack_up->addFramesInRange(0, 2*24+16, 2*24+24, 45);

    //DOWN
    gdf::animation::AnimationClip* clip_stand_down= rm->load_resource<gdf::animation::AnimationClip>("animc:stand_down");
    clip_stand_down->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_stand_down->add_frame(0, 3*24+0, 100);
    clip_stand_down->add_frame(0, 3*24+0, 100);

    gdf::animation::AnimationClip* clip_move_down= rm->load_resource<gdf::animation::AnimationClip>("animc:move_down");
    clip_move_down->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_move_down->addFramesInRange(0, 3*24+1, 3*24+10, 65);

    gdf::animation::AnimationClip* clip_slide_down= rm->load_resource<gdf::animation::AnimationClip>("animc:slide_down");
    clip_slide_down->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_slide_down->addFramesInRange(0, 3*24+11, 3*24+16, 45);

    gdf::animation::AnimationClip* clip_attack_down= rm->load_resource<gdf::animation::AnimationClip>("animc:attack_down");
    clip_attack_down->add_sprite( rm->get<gdf::graphic::SpriteSheet>("hero_sprite_sheet") );
    clip_attack_down->addFramesInRange(0, 3*24+16, 3*24+24, 45);

}

void SoG::flowchart_2(){

    ResourceManager* rm = gdf::kernel::GameInfo::game_info.get()->get_component<ResourceManager>();

    // ANIMATOR based animation
    animator = game_object()->add_component<gdf::animation::Animator>();
    animator->runtime_animator_controller = new gdf::animation::AnimatorController();
    animator->runtime_animator_controller->addParameter<float>( "HeroSpeed", gdf::system::Algorithm::length(velocity) );
    animator->runtime_animator_controller->addParameter<float>( "Direction", direction );
    animator->runtime_animator_controller->addParameter<float>( "Attacking", is_attacking );

    gdf::animation::AnimatorControllerLayer* layer = new gdf::animation::AnimatorControllerLayer();

    animator->runtime_animator_controller->layers.push_back( layer );


    ////////////////////////////////////////////////////////////////////////////////////////
    /// Common state STAND
    ////////////////////////////////////////////////////////////////////////////////////////
    gdf::animation::AnimatorState* s0 = layer->state_machine->add_state("S0");
    s0->animation_ = new gdf::animation::Animation2();
    s0->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    s0->animation_->blend_tree = new gdf::animation::BlendTree();
    s0->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:stand_up").get() );
    s0->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:stand_right").get() );
    s0->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:stand_down").get() );
    s0->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:stand_left").get() );
    s0->animation_->blend_tree->parameter_ = "Direction";
    s0->animation_->blend_tree->threshold_.push_back(1.1f);
    s0->animation_->blend_tree->threshold_.push_back(2.1f);
    s0->animation_->blend_tree->threshold_.push_back(3.1f);
    s0->animation_->blend_tree->update_function();

    ////////////////////////////////////////////////////////////////////////////////////////
    /// Right SIDE
    ////////////////////////////////////////////////////////////////////////////////////////
    //States
    gdf::animation::AnimatorState* rs1 = layer->state_machine->add_state("RS1");
    rs1->animation_ = new gdf::animation::Animation2();
    rs1->animation_->wrap_mode = gdf::animation::WrapMode::Loop;
    rs1->animation_->blend_tree = new gdf::animation::BlendTree();
    rs1->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:move_right").get() );
    rs1->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* rs2 = layer->state_machine->add_state("RS2");
    rs2->animation_ = new gdf::animation::Animation2();
    rs2->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    rs2->animation_->blend_tree = new gdf::animation::BlendTree();
    rs2->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_right").get() );
    rs2->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* rs22 = layer->state_machine->add_state("RS22");
    rs22->animation_ = new gdf::animation::Animation2();
    rs22->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    rs22->animation_->blend_tree = new gdf::animation::BlendTree();
    rs22->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_right").get() );
    rs22->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* rs3 = layer->state_machine->add_state("RS3");
    rs3->animation_ = new gdf::animation::Animation2();
    rs3->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    rs3->animation_->blend_tree = new gdf::animation::BlendTree();
    rs3->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:attack_right").get() );
    rs3->animation_->blend_tree->update_function();

    // transitions
    gdf::animation::AnimatorTransitionBase* s0_rs1 = layer->state_machine->add_transition(s0, rs1 );
    s0_rs1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    s0_rs1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );

    gdf::animation::AnimatorTransitionBase* rs1_rs2 = layer->state_machine->add_transition( rs1, rs2 );
    rs1_rs2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Equals, 0.0 );
    rs1_rs2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );

    gdf::animation::AnimatorTransitionBase* rs2_s0 = layer->state_machine->add_transition( rs2, s0 );
    rs2_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* s0_rs3 = layer->state_machine->add_transition( s0, rs3 );
    s0_rs3->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );
    s0_rs3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* rs1_rs3 = layer->state_machine->add_transition( rs1, rs3 );
    rs1_rs3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* rs3_s0 = layer->state_machine->add_transition( rs3, s0 );
    rs3_s0->set_exit_time( sf::milliseconds(8*45) );

    gdf::animation::AnimatorTransitionBase* rs1_rs22 = layer->state_machine->add_transition( rs1, rs22 );
    rs1_rs22->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );
    rs1_rs22->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );


    ////////////////////////////////////////////////////////////////////////////////////////
    /// LEFT SIDE
    ////////////////////////////////////////////////////////////////////////////////////////
    //States
    gdf::animation::AnimatorState* ls1 = layer->state_machine->add_state("LS1");
    ls1->animation_ = new gdf::animation::Animation2();
    ls1->animation_->wrap_mode = gdf::animation::WrapMode::Loop;
    ls1->animation_->blend_tree = new gdf::animation::BlendTree();
    ls1->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:move_left").get() );
    ls1->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ls2 = layer->state_machine->add_state("LS2");
    ls2->animation_ = new gdf::animation::Animation2();
    ls2->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ls2->animation_->blend_tree = new gdf::animation::BlendTree();
    ls2->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_left").get() );
    ls2->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ls22 = layer->state_machine->add_state("LS22");
    ls22->animation_ = new gdf::animation::Animation2();
    ls22->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ls22->animation_->blend_tree = new gdf::animation::BlendTree();
    ls22->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_left").get() );
    ls22->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ls3 = layer->state_machine->add_state("LS3");
    ls3->animation_ = new gdf::animation::Animation2();
    ls3->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ls3->animation_->blend_tree = new gdf::animation::BlendTree();
    ls3->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:attack_left").get() );
    ls3->animation_->blend_tree->update_function();

    // transitions
    gdf::animation::AnimatorTransitionBase* s0_ls1 = layer->state_machine->add_transition( s0, ls1 );
    s0_ls1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    s0_ls1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );

    gdf::animation::AnimatorTransitionBase* ls1_ls2 = layer->state_machine->add_transition( ls1, ls2 );
    ls1_ls2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Equals, 0.0 );
    ls1_ls2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );

    gdf::animation::AnimatorTransitionBase* ls2_s0 = layer->state_machine->add_transition( ls2, s0 );
    ls2_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* s0_ls3 = layer->state_machine->add_transition( s0, ls3 );
    s0_ls3->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );
    s0_ls3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* ls1_ls3 = layer->state_machine->add_transition( ls1, ls3 );
    ls1_ls3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* ls3_s0 = layer->state_machine->add_transition( ls3, s0 );
    ls3_s0->set_exit_time( sf::milliseconds(8*45) );

    gdf::animation::AnimatorTransitionBase* ls1_ls22 = layer->state_machine->add_transition( ls1, ls22 );
    ls1_ls22->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );
    ls1_ls22->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );

    ////////////////////////////////////////////////////////////////////////////////////////
    /// UP SIDE
    ////////////////////////////////////////////////////////////////////////////////////////
    //States
    gdf::animation::AnimatorState* us1 = layer->state_machine->add_state("US1");
    us1->animation_ = new gdf::animation::Animation2();
    us1->animation_->wrap_mode = gdf::animation::WrapMode::Loop;
    us1->animation_->blend_tree = new gdf::animation::BlendTree();
    us1->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:move_up").get() );
    us1->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* us2 = layer->state_machine->add_state("US2");
    us2->animation_ = new gdf::animation::Animation2();
    us2->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    us2->animation_->blend_tree = new gdf::animation::BlendTree();
    us2->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_up").get() );
    us2->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* us22 = layer->state_machine->add_state("US22");
    us22->animation_ = new gdf::animation::Animation2();
    us22->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    us22->animation_->blend_tree = new gdf::animation::BlendTree();
    us22->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_up").get() );
    us22->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* us3 = layer->state_machine->add_state("US3");
    us3->animation_ = new gdf::animation::Animation2();
    us3->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    us3->animation_->blend_tree = new gdf::animation::BlendTree();
    us3->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:attack_up").get() );
    us3->animation_->blend_tree->update_function();

    // transitions
    gdf::animation::AnimatorTransitionBase* s0_us1 = layer->state_machine->add_transition( s0, us1 );
    s0_us1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    s0_us1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );

    gdf::animation::AnimatorTransitionBase* us1_us2 = layer->state_machine->add_transition( us1, us2 );
    us1_us2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Equals, 0.0 );
    us1_us2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );

    gdf::animation::AnimatorTransitionBase* us2_s0 = layer->state_machine->add_transition( us2, s0 );
    us2_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* s0_us3 = layer->state_machine->add_transition( s0, us3 );
    s0_us3->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );
    s0_us3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* us1_us3 = layer->state_machine->add_transition( us1, us3 );
    us1_us3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* us3_s0 = layer->state_machine->add_transition( us3, s0 );
    us3_s0->set_exit_time( sf::milliseconds(8*45) );

    gdf::animation::AnimatorTransitionBase* us1_us22 = layer->state_machine->add_transition( us1, us22 );
    us1_us22->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );
    us1_us22->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );


    ////////////////////////////////////////////////////////////////////////////////////////
    /// DOWN SIDE
    ////////////////////////////////////////////////////////////////////////////////////////
    //States
    gdf::animation::AnimatorState* ds1 = layer->state_machine->add_state("DS1");
    ds1->animation_ = new gdf::animation::Animation2();
    ds1->animation_->wrap_mode = gdf::animation::WrapMode::Loop;
    ds1->animation_->blend_tree = new gdf::animation::BlendTree();
    ds1->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:move_down").get() );
    ds1->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ds2 = layer->state_machine->add_state("DS2");
    ds2->animation_ = new gdf::animation::Animation2();
    ds2->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ds2->animation_->blend_tree = new gdf::animation::BlendTree();
    ds2->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_down").get() );
    ds2->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ds22 = layer->state_machine->add_state("DS22");
    ds22->animation_ = new gdf::animation::Animation2();
    ds22->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ds22->animation_->blend_tree = new gdf::animation::BlendTree();
    ds22->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:slide_down").get() );
    ds22->animation_->blend_tree->update_function();

    gdf::animation::AnimatorState* ds3 = layer->state_machine->add_state("DS3");
    ds3->animation_ = new gdf::animation::Animation2();
    ds3->animation_->wrap_mode = gdf::animation::WrapMode::Once;
    ds3->animation_->blend_tree = new gdf::animation::BlendTree();
    ds3->animation_->blend_tree->clips_.push_back( rm->get<gdf::animation::AnimationClip>("animc:attack_down").get() );
    ds3->animation_->blend_tree->update_function();

    // transitions
    gdf::animation::AnimatorTransitionBase* s0_ds1 = layer->state_machine->add_transition( s0, ds1 );
    s0_ds1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    s0_ds1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );

    gdf::animation::AnimatorTransitionBase* ds1_ds2 = layer->state_machine->add_transition( ds1, ds2 );
    ds1_ds2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Equals, 0.0 );
    ds1_ds2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );

    gdf::animation::AnimatorTransitionBase* ds2_s0 = layer->state_machine->add_transition( ds2, s0 );
    ds2_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* s0_ds3 = layer->state_machine->add_transition( s0, ds3 );
    s0_ds3->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );
    s0_ds3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* ds1_ds3 = layer->state_machine->add_transition( ds1, ds3 );
    ds1_ds3->addCondition("Attacking", gdf::animation::AnimatorConditionMode::Equals, 1 );

    gdf::animation::AnimatorTransitionBase* ds3_s0 = layer->state_machine->add_transition( ds3, s0 );
    ds3_s0->set_exit_time( sf::milliseconds(8*45) );

    gdf::animation::AnimatorTransitionBase* ds1_ds22 = layer->state_machine->add_transition( ds1, ds22 );
    ds1_ds22->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );
    ds1_ds22->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );


    // Direction change

    gdf::animation::AnimatorTransitionBase* ls22_s0 = layer->state_machine->add_transition( ls22, s0 );
    ls22_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* rs22_s0 = layer->state_machine->add_transition( rs22, s0 );
    rs22_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* ds22_s0 = layer->state_machine->add_transition( ds22, s0 );
    ds22_s0->set_exit_time( sf::milliseconds(6*45) );

    gdf::animation::AnimatorTransitionBase* us22_s0 = layer->state_machine->add_transition( us22, s0 );
    us22_s0->set_exit_time( sf::milliseconds(6*45) );

    ////////////////////////////////////////////////////////////////////////////////////////
    /// GLOBAL TRANSITION
    ////////////////////////////////////////////////////////////////////////////////////////
    gdf::animation::AnimatorTransitionBase* rs1_us1 = rs1->add_transition( us1 );
    rs1_us1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    rs1_us1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );

    gdf::animation::AnimatorTransitionBase* rs1_ds1 = rs1->add_transition( ds1 );
    rs1_ds1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    rs1_ds1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );

    gdf::animation::AnimatorTransitionBase* ls1_us1 = ls1->add_transition( us1 );
    ls1_us1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    ls1_us1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 1.0f );

    gdf::animation::AnimatorTransitionBase* ls1_ds1 = ls1->add_transition( ds1 );
    ls1_ds1->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    ls1_ds1->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 3.0f );

    gdf::animation::AnimatorTransitionBase* us1_s0 = us1->add_transition( s0 );
    us1_s0->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    us1_s0->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );

    gdf::animation::AnimatorTransitionBase* us1_s0_2 = us1->add_transition( s0 );
    us1_s0_2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    us1_s0_2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );

    gdf::animation::AnimatorTransitionBase* ds1_s0 = ds1->add_transition( s0 );
    ds1_s0->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    ds1_s0->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 2.0f );

    gdf::animation::AnimatorTransitionBase* ds1_s0_2 = ds1->add_transition( s0 );
    ds1_s0_2->addCondition("HeroSpeed", gdf::animation::AnimatorConditionMode::Greater, 0.0f );
    ds1_s0_2->addCondition("Direction", gdf::animation::AnimatorConditionMode::Equals, 4.0f );


    //
    gdf::animation::AnimationClip* r_sliding_behavior = rm->get<gdf::animation::AnimationClip>("animc:slide_right").get();
    r_sliding_behavior->keyframes[0]->fire_event = [this](void*)
    {
        this->control_frozen = true;
        velocity.x = 50;
    };
    r_sliding_behavior->keyframes[ r_sliding_behavior->keyframes.size()-1]->fire_event = [this](void*)
    {
        this->control_frozen = false;
        velocity.x = 0;
    };

    gdf::animation::AnimationClip* l_sliding_behavior = rm->get<gdf::animation::AnimationClip>("animc:slide_left").get();
    l_sliding_behavior->keyframes[0]->fire_event = [this](void*)
    {
        this->control_frozen = true;
        velocity.x = -50;
    };
    l_sliding_behavior->keyframes[ l_sliding_behavior->keyframes.size()-1]->fire_event = [this](void*)
    {
        this->control_frozen = false;
        velocity.x = 0;
    };

    gdf::animation::AnimationClip* u_sliding_behavior = rm->get<gdf::animation::AnimationClip>("animc:slide_up").get();
    u_sliding_behavior->keyframes[0]->fire_event = [this](void*)
    {
        this->control_frozen = true;
        velocity.y = -50;
    };
    u_sliding_behavior->keyframes[ u_sliding_behavior->keyframes.size()-1]->fire_event = [this](void*)
    {
        this->control_frozen = false;
        velocity.y = 0;
    };

    gdf::animation::AnimationClip* d_sliding_behavior = rm->get<gdf::animation::AnimationClip>("animc:slide_down").get();
    d_sliding_behavior->keyframes[0]->fire_event = [this](void*)
    {
        this->control_frozen = true;
        velocity.y = +50;
    };
    d_sliding_behavior->keyframes[ d_sliding_behavior->keyframes.size()-1]->fire_event = [this](void*)
    {
        this->control_frozen = false;
        velocity.y = 0;
    };

    gdf::animation::AnimationClip* r_attacking_behavior = rm->get<gdf::animation::AnimationClip>("animc:attack_right").get();

//    r_attacking_behavior->keyframes[2]->fire_event = [this](void*)
//    {
//        this->game_object()->transform().get()->translate( sf::Vector2f(150,0) );
//        velocity.x = -50;
//    };
//    r_attacking_behavior->keyframes[ r_attacking_behavior->keyframes.size()-1 ]->fire_event = [this](void*)
//    {
//        this->game_object()->transform().get()->translate( sf::Vector2f(-150,0) );
//        velocity.x = -50;
//    };

    r_attacking_behavior->keyframes[1]->fire_event = [this](void*){
        Collider* col = this->game_object()->add_component<Collider>();
        col->aabb->set_min_max({30+0,-60},{30+35,-30} );
    };


    r_attacking_behavior->keyframes[2]->fire_event = [this](void*){
        Collider* col = this->game_object()->get_component<Collider>();
        col->aabb->set_min_max({30+0,-30},{30+35,0} );
    };
    r_attacking_behavior->keyframes[3]->fire_event = [this](void*){
        Collider* col = this->game_object()->get_component<Collider>();
        col->aabb->set_min_max({-10,0},{40,35} );
    };

    r_attacking_behavior->keyframes[5]->fire_event = [this](void*){
        Collider* col = this->game_object()->get_component<Collider>();
        if( col != nullptr ){
            this->game_object()->destroy( col, 0);
        }
    };


    animator->current_state = s0;
    direction = 1;

}

void SoG::init(){

    init_res();

    flowchart_2();

}

void SoG::update(sf::Time dt){

    if( !control_frozen ){

        if( game_object()->chrono().get()->status_ == gdf::temporal::ChronoPlayStatus::FORWARD ){
            velocity = sf::Vector2f();
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ){
                velocity.x = -200.f;
                direction = 4.0f;
            }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ){
                velocity.x = 200.f;
                direction = 2.0f;
            }
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ){
                velocity.y = -200.f;
                direction = 1.0f;
            }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ){
                velocity.y = 200.f;
                direction = 3.0f;
            }
        }
    }

    pvelocity = velocity;
    pdirection = direction;

    *(float*)animator->runtime_animator_controller->parameters["HeroSpeed"] = gdf::system::Algorithm::length(velocity) ;
    *(float*)animator->runtime_animator_controller->parameters["Direction"] = direction;

    if( !is_attacking )
        game_object()->transform().get()->translate( sf::Vector2f( velocity.x * dt.asMicroseconds()/1000000.f, velocity.y* dt.asMicroseconds()/1000000.f ) );
}

void SoG::on_key_pressed(const sf::Event &event){
    if( control_frozen )
        return;

    if( event.key.code == sf::Keyboard::Q ){

        *(float*)animator->runtime_animator_controller->parameters["Attacking"] = 1.0f;
        is_attacking = true;

    }
}

void SoG::on_key_released(const sf::Event &event){
    if( control_frozen )
        return;

    if( event.key.code == sf::Keyboard::Q ){
        *(float*)animator->runtime_animator_controller->parameters["Attacking"] = 0.0f;
        is_attacking = false;
    }
}

void SoG::on_enter_state(gdf::animation::AnimatorTransitionBase *transition){

}

void SoG::on_exit_state(gdf::animation::AnimatorTransitionBase *transition){

}

void SoG::on_enter_collision(Collider *obj1, Collider *obj2){
    std::cout << "@" << game_object()->name() << " ENTER COLLISION " << obj1->game_object()->name() << " " << obj2->game_object()->name() << std::endl;

}

void SoG::on_stay_collision(Collider *obj1, Collider *obj2){
    //std::cout << "@" << game_object()->name() << "    COLLISION " << obj1->game_object()->name() << " " << obj2->game_object()->name() << std::endl;

}

void SoG::on_exit_collision(Collider *obj1, Collider *obj2){
    std::cout << "@" << game_object()->name() << "EXIT COLLISION " << obj1->game_object()->name() << " " << obj2->game_object()->name() << std::endl;

}
