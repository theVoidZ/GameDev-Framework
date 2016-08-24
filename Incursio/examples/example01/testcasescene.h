#ifndef TESTCASESCENE_H
#define TESTCASESCENE_H

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

#endif // TESTCASESCENE_H