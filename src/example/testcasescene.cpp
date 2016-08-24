#include "testcasescene.h"

#include "kernel/gameinfo.h"
#include "kernel/gameobject.h"
#include "Core/System/camera.h"

#include "example/mycomponent.h"


TestCaseScene::TestCaseScene()
{

}

TestCaseScene::~TestCaseScene(){

}

void TestCaseScene::on_init(){
	// There is no Scene-dedicated Component to add yet
}

void TestCaseScene::load_resources(){
	// W're not using a ResourceManager yet
}

void TestCaseScene::build(){
	// Construct the scene here ( GameObjects )
	// note that, root_ is the topmost game object of the scene.
	
	// Create a Camera on root object ( and add it to the conatiner 'cameras' of scene, to keep track of it )
    root_->addComponent<Camera>(&cameras_);

    //------------------------------------------------------------------------------------
    // Create a GameObject [g0] on Scene[0]
    // instantiate<n> : where n is the id of the scene to use for instantiation.
    gdf::kernel::GameObject* g0 = gdf::kernel::GameObject::instantiate<0>("g0", sf::Vector2f(160, 120) );
    g0->addComponent<MyComponent>();

    //------------------------------------------------------------------------------------
    // Create a GameObject [g1] on Scene[0] as a child of g0
    gdf::kernel::GameObject* g1 = gdf::kernel::GameObject::instantiate<0>("g1"); // auto attached to root
    
    // Change linkage:
    g1->hierarchy()->attach_to(g0->hierarchy());


}

void TestCaseScene::on_event(const sf::Event& event){

}
