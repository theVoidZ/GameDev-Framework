# GameDev-Framework
GameDev Framework (GDF) is a C++ / SFML modular framework for 2D game development.

It provides a small kernel to be used as a core-engine for any kind of application, due to its high flexibility achieved using GameObject/Component architecture, it can integrate any type of user-modules ( Components ), without changing the kernel code at all. 

In any case the GameLogic does not fit to your applciation-logic, it can be overridden (See. GameInfo.cpp ) in order to implement your own game-logic. i.e: Your own way of Intializing, Updating and Drawing stuffs. However, the architecture is preserved.


# Built-in modules
The framework does provide some built-in modules ( a Module is a set of Component ), such as:
+ Renderers
+ State machine based system of Animation ( Multi layer Animator )
+ Audio & Audio Listener
+ Resource management
+ Cameras 
+ Time management
+  etc .

# User-Modules 
Any created user component must inherit from Component class in order to be fully functioning.
MonoBehavior is also an alternative (high level use ). ( As MonoBehavior provides a lot of callbacks )

# Building
The framework is built cross platform c++, extending the following labraires

1. Requirement

+ C++14
+ SFML 2.3.2
+ Box2D 2.3.1 ( not used yet, physics module is not implemented )
+ Qt 5.7.0

2. Compiling

I am compiling under Ubuntu 16.04 using Qt-Creator. ( the pro file can be found in master branch 'src' ).

Sorry,but i had little problems when trying to compile the project using qt command-line (qmake),

I will fix this sooner and provide more informations on how to compile under windows, including a project file.

# About default branches
There is actually two default branches, 

1. kernel branch
Contains imporved and refined code regarding the kernel. But not completed yet as i am still working on its refining.

2. master branch
Contains all the code of the framework, including the kernel code and some built-in modules.

If you need to get started, use the master branch.

[Not completed yet] If you need to start coding your app from scratch, and building your own modules, use the kernel branch

# Getting started - sample 
In order to create an minimal example, you must overrid both GameInfo class and Scene class.
Then, start creating you component.

An existing example of custom GameInfo and Scene can be found in master/src/Assets/. TestCaseGameInfo.cpp and TestCaseScene.cpp

#### TestCaseGameInfo.h
```C++
#include "kernel/gameinfo.h"

using namespace gdf::kernel;

class TestCaseGameInfo : public gdf::kernel::GameInfo
{
    public:
        TestCaseGameInfo(const sf::Vector2i& size, std::string title);
        ~TestCaseGameInfo();

    protected:
        void on_init() override;
        void on_event(const sf::Event &event) override;
};
```
#### TestCaseGameInfo.cpp
```C++
#include "testcasegameinfo.h"

#include "Assets/TestCases/testcasescene.h"

#include "resource_management/resourcemanager.h"
#include "kernel/garbagecollector.h"
#include "time_management/chrono.h"

TestCaseGameInfo::TestCaseGameInfo(const sf::Vector2i& size, std::string title)
    :GameInfo(size, title)
{

}

TestCaseGameInfo::~TestCaseGameInfo(){

}

void TestCaseGameInfo::on_init(){
    // Adding resources to GameInfo
    addComponent<Chrono>();
    addComponent<ResourceManager>();
    addComponent<GarbageCollector>();

    // Creating a scene
    scenes_["TSpawn"] = new TestCaseScene();;
    
    // Setting 'TSpawn' as default scene
    set_active_scene( "TSpawn" );

}

void TestCaseGameInfo::on_event(const sf::Event &event){

}
```

#### TestCaseScene.h
```C++
// user-includes
#include "kernel/scene.h"

class Camera;

class TestCaseScene : public gdf::kernel::Scene
{
    public:
        TestCaseScene();
        ~TestCaseScene();

    public:
        void on_init();
        void load_resources();
        void build();
        void on_event(const sf::Event& event);

};

```

#### TestCaseScene.cpp
```C++
#include "testcasescene.h"
#include "kernel/gameinfo.h"

#include "kernel/gameobject.h"
#include "Core/System/camera.h"
#include "Core/System/monobehavior.h"
#include "Core/System/transform.h"
#include "Core/Graphic/spriterenderer.h"

#include "resource_management/resourcemanager.h"
#include "resource_management/texture2d.h"
#include "resource_management/spritetile.h"

#include "time_management/timewinder.h"
#include "time_management/chrono.h"

TestCaseScene::TestCaseScene()
{

}

TestCaseScene::~TestCaseScene(){

}

void TestCaseScene::on_init(){
    // Adding components for the Scene 
    // A Chrono, and a TimeWinder
    addComponent<Chrono>();
    addComponent<TimeWinder>();
}

void TestCaseScene::load_resources(){
    // Loading & initialising resources
    Texture2D* a = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<Texture2D>(4, true, "Cockatrice");
    a->init("./Cockatrice.png");

    Texture2D* a2 = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<Texture2D>(2, true, "Cockatrice2");
    a2->init("./Cockatrice.png");

    SpriteTile* s = gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->load_resource<SpriteTile>(3, true, "Flash");
    s->init("Flash_2.png", 3, 5 );
}

void TestCaseScene::build(){
    // Each scene has pre-created gameobject called 'root_'
    
    //Create a Camera on root gameobject
    Camera* c1 = root_->addComponent<Camera>(&cameras_);
    // c1->move( sf::Vector2f( 10, 0) );
    
    // Create a GameObject g1
    gdf::kernel::GameObject* g1 = gdf::kernel::GameObject::instantiate("g1"); // auto attached to 'root'
    
    // Create and initialize a Chrono componenet for g1
    Chrono* ch = g0->addComponent<Chrono>();
    ch->init();
    
    // Create a SpriteRenderer for g1
    SpriteRenderer* sa = g1->addComponent< SpriteRenderer >();
    sa->sprite.setTexture2D( gdf::kernel::GameInfo::game_info.get()->getComponent<ResourceManager>()->get<Texture2D>(4) );
    
    // translate g1 by 160, 120
    g1->transform()->translate( sf::Vector2f( 160 ,120) ); // -64


}

void TestCaseScene::on_event(const sf::Event& event){
    if( event.type == sf::Event::Closed ){
        gdf::kernel::GameInfo::game_info.get()->close();
    }
}

```

#### Then create you own Component
#### MoveObject.h 
```C++
// MoveObject allows to move a GameObject using arrow keys
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Core/System/monobehavior.h"

class MoveObject : public MonoBehavior
{
    Q_OBJECT
    public:
        MoveObject();
        ~MoveObject();
        void init();
        void update(sf::Time dt);

};
```
#### MoveObject.cpp
```C++
#include "moveobject.h"

#include "Core/System/transform.h"

MoveObject::MoveObject()
{

}

MoveObject::~MoveObject(){

}

void MoveObject::update(sf::Time dt){
    if( game_object() == nullptr )
        return;

    float speed_per_sec = 300.f;
    sf::Vector2f velocity;

    // while there are pending events...
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
        velocity.x = (-speed_per_sec/1000.f/1000.f) * dt.asMicroseconds();
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
        velocity.x = (+speed_per_sec/1000/1000) * dt.asMicroseconds();
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ){
        velocity.y = (-speed_per_sec/1000/1000) * dt.asMicroseconds();
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
        velocity.y = (+speed_per_sec/1000/1000) * dt.asMicroseconds();
    }

    game_object()->transform()->translate( sf::Vector2f( velocity.x , velocity.y ) );

}

```

And to add it for a Given GameObject, use:
```C++
// Inside a scene having a GameObject called g1 ( From the previous example )
  g1->addComponent<MoveObject>();

```

### Video Example ( Time Reversal )
<a href="https://www.youtube.com/watch?feature=player_embedded&v=EdxZK8fgfcg
" target="_blank"><img src="http://img.youtube.com/vi/EdxZK8fgfcg/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

# Contribution
The framework is designed to be fully open-source and community repo,

You are welcome to:

+ Suggest Code improvements ( as i'm writing very basic things right now to get a global architecture, then i'll refine every class ) [Note that kernel is refined but incomplete (still in progress) ]
+ Suggest modifications about the kernel or an existing module.
+ Suggest your own modules. even if there is an already existing one, 
There is no better code. but one can fit better than the other, depending on the problem+
+ Platform portability, { as it is currently tested only under Ubuntu 16.04. }
But since Qt & SFML & Box2D are multi-platform, there should not be a problem.(not tested on other platforms )

# Links
Currently there is no available website or forum. [incoming]

You can follow a topic on sfml forum which explain more things about the framework.
[GDF-Topic in SFML Forum](http://en.sfml-dev.org/forums/index.php?topic=20730.0)
