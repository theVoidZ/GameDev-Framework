#ifndef TESTCASEGAMEINFO_H
#define TESTCASEGAMEINFO_H

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

#endif // TESTCASEGAMEINFO_H
