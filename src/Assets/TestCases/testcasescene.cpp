#include "testcasescene.h"
#include "kernel/gameinfo.h"

#include "kernel/gameobject.h"
#include "Core/System/camera.h"
#include "Core/System/monobehavior.h"
#include "Core/System/transform.h"
#include "Core/Graphic/spriterenderer.h"
#include "Core/Graphic/Animation/animation.h"
#include "Core/Graphic/Animation/animationclip.h"
#include "Core/Graphic/Animation/animator.h"
#include "Core/Graphic/Animation/animatorcontroller.h"
#include "Core/Graphic/Animation/animatorcontrollerlayer.h"
#include "Core/Graphic/Animation/StateMachine/animatorstatemachine.h"
#include "Core/Graphic/Animation/StateMachine/animatorstate.h"
#include "Core/Graphic/Animation/StateMachine/animatortransitionbase.h"
#include "Core/Graphic/Animation/StateMachine/animatorcondition.h"

#include "Assets/TestCases/arduinotest.h"

#include "resource_management/resourcemanager.h"
#include "resource_management/texture2d.h"
#include "resource_management/spritetile.h"


#include "Assets/TestCases/moveobject.h"
#include "Assets/TestCases/velocitydef.h"
#include "Assets/TestCases/simulatorcomponent.h"
#include "time_management/timekeeper.h"
#include "time_management/timewinder.h"
#include "time_management/chrono.h"

#include "kernel/component.h"
#include "kernel/garbagecollector.h"
#include "time_management/chrono.h"

TestCaseScene::TestCaseScene()
{

}

TestCaseScene::~TestCaseScene(){

}

void TestCaseScene::on_init(){
    addComponent<Chrono>();
    addComponent<TimeWinder>();
    gdf::kernel::GarbageCollector* gc = addComponent<gdf::kernel::GarbageCollector>();
    //    gc->bind(&junkyard_); // not used [reported]
}

void TestCaseScene::load_resources(){

    // Loading ( Create a concrete instance of the resource as Texture2D.
    Texture2D* a = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<Texture2D>(4, true, "Cockatrice");
    a->init("./Cockatrice.png");

    Texture2D* a2 = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<Texture2D>(2, true, "Cockatrice2");
    a2->init("./Cockatrice.png");

    SpriteTile* s = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<SpriteTile>(3, true, "Flash");
    s->init("Flash_2.png", 3, 5 );
}

void TestCaseScene::build(){
    //Create camears.
    c1 = root_->addComponent<Camera>(&cameras_);

    root_->set_name("root");
    c1->move( sf::Vector2f( 0, 0) );

//    c1->setViewportPosition( sf::Vector2f(100, 100) );
//    c1->setCameraLocation( sf::Vector2f(20, 10) );

    sf::Vector2f p = c1->screenToViewport( sf::Vector2f(0, 0) );
//    std::cout << "X,Y: " << p.x << ":" << p.y << std::endl;

/*
    c2 = root->addComponent<Camera>( &cameras_ );
    c2->setViewSize( sf::Vector2f(320, 240) );
    c2->setViewPosition( sf::Vector2f(320,0) );
    c2->setViewAspect( sf::Vector2f(1,1) );
    c2->setViewLocation( sf::Vector2f(50,0) );
//    c2->move( sf::Vector2f(500, 500) );
*/

    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------

    // GameObject g0
    gdf::kernel::GameObject* g0 = gdf::kernel::GameObject::instantiate("g0", sf::Vector2f(160, 120) );
    Chrono* ch = g0->addComponent<Chrono>();
    ch->init();

    TimeKeeper* tk = g0->addComponent<TimeKeeper>();
    tk->init();

    g0->addComponent<ArduinoTest>();
    g0->addComponent<MoveObject>(); // make the object move
    g0->addComponent<VelocityDef>(); // Define velocity for the game object
    SimulatorComponent* sc = g0->addComponent<SimulatorComponent>();
    sc->init();

    // Resource Management test
    SpriteRenderer* ssprt = g0->addComponent<SpriteRenderer>();
    ssprt->sprite.setTexture2D( gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->get<Texture2D>( 4 ) );



    //------------------------------------------------------------------------------------

    // GameObject g1
    gdf::kernel::GameObject* g1 = gdf::kernel::GameObject::instantiate("g1"); // auto attached to 'root'
    SpriteRenderer* sa = g1->addComponent< SpriteRenderer >();
    sa->sprite.setTexture2D( gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->get<Texture2D>(4) );
    g1->transform()->translate( sf::Vector2f( 160 ,120) ); // -64


    //------------------------------------------------------------------------------------

//     Animation without an Animator
    Animation* anim = g1->addComponent< Animation >();
    AnimationClip* clip = new AnimationClip();
    clip->addSprite( *gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->get<SpriteTile>(3) );
    clip->addFramesInSequence(0,15, 45.f/1000);

    anim->clip = clip;
    anim->play();

//    gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->unload_unused_resources();
//    gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->verbose();


//    g0->verbose();
//    g1->verbose();

    //------------------------------------------------------------------------------------
/*
    Animator* animator = g1->addComponent<Animator>();
    animator->runtime_animator_controller = new AnimatorController();

    animator->runtime_animator_controller->addParameter<float>( "Level", 2.0f );
    animator->runtime_animator_controller->addParameter<float>( "Stage", 15.0f );

    animator->runtime_animator_controller->setParameter<float>( "Stage", 9.0f );

    animator->runtime_animator_controller->layers.push_back( new AnimatorControllerLayer() );

    AnimatorControllerLayer* layer = animator->runtime_animator_controller->layers[0];

    layer->state_machine = new AnimatorStateMachine();
    AnimatorState* s0 = layer->state_machine->addState("S0");
    AnimatorState* s1 = layer->state_machine->addState("S1");
    s1->speed = {0.7f, "Level", true};
    s1->mirror = {false, "", false};

    AnimatorTransitionBase* trans = layer->state_machine->states[0]->addTransition( layer->state_machine->states[1] );
    trans->has_exit_time = false;
    trans->exit_time = 2000.f/1000.f;
    trans->addCondition("Level", AnimatorConditionMode::Greater, 0.0f );
    trans->addCondition("Stage", AnimatorConditionMode::Less, 10.0f );

    animator->current_state = s0;
    s1->animation = new Animation();
    s1->animation->setGameObject( animator->game_object() );
    s1->animation->wrap_mode = WrapMode::PingPong;
*/
    //------------------------------------------------------------------------------------
    // Add items to watch
    this->getComponent<TimeWinder>()->watch(g0);

    //------------------------------------------------------------------------------------

    // Destroy test
    std::cout << "Request: GameObject::destroy(g0) @ " << ch->lifetime.asMilliseconds() << " ms"<< std::endl;
    gdf::kernel::GameObject::destroy(g1, 2420);



}

void TestCaseScene::on_event(const sf::Event& event){
    if( event.type == sf::Event::Closed ){
        std::cout << FGREEN << BOLD << "You shall pass ! " << RESET << std::endl;
        gdf::kernel::GameInfo::game_info.get()->close();
    }
}
