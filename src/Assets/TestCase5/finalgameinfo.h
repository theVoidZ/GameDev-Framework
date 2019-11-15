#ifndef FINALGAMEINFO_H
#define FINALGAMEINFO_H

#include "gameinfo.h"

using namespace gdf::kernel;

class FinalGameInfo : public gdf::kernel::GameInfo
{
    public:
        FinalGameInfo(const sf::Vector2i& size, std::string title);
        ~FinalGameInfo();

    protected:
        void on_init() override;
        void on_event(const sf::Event &event) override;
};

#endif // FINALGAMEINFO_H
