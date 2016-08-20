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
    // init the garbage collector

    // init the resource manager
    addComponent<Chrono>();
    addComponent<ResourceManager>();
    GarbageCollector* gc = addComponent<GarbageCollector>();
//    gc->bind(&junkyard_); // not used [reported]

    // testcase
    Scene* t1 = new TestCaseScene();
    Scene* t2 = new TestCaseScene();
    Scene* t3 = new TestCaseScene();

    t1->set_as_daemon(false);
    t2->set_as_daemon(false);
    t3->set_as_daemon(true);

    //! BUG: Error HERE on multiple-scene
//    scenes["CTSpawn"] = t1;
    scenes_["TSpawn"] = t2;

//    scenes["DoubleDoors"] = t3;

//    active_scene = t2;
    set_active_scene( "TSpawn" );


    //!
    this->setKeyRepeatEnabled(false);
}

void TestCaseGameInfo::on_event(const sf::Event &event){

}
