#ifndef TESTCASESCENE_H
#define TESTCASESCENE_H

// c++-includes

// sfml-includes

// box2d-includes

// qt-includes

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

    protected:
        Camera* c1;
        Camera* c2;
        Camera* c3;

};

#endif // TESTCASESCENE_H
