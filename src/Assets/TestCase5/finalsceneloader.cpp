#include "finalsceneloader.h"

#include "gameinfo.h"

#include "chrono.h"
#include "garbagecollector.h"

#include "finalscenebuilder.h"
#include "collisionmanager.h"

FinalSceneLoader::FinalSceneLoader()
{

}

void FinalSceneLoader::init(){
    //! NOTE: Use external file to skip generating new class for this.
    int id1 = gdf::kernel::GameInfo::game_info->add_scene/*<Scene>*/( "Rupture Farm", true);
    gdf::kernel::Scene* sc1 = gdf::kernel::GameInfo::game_info->scenes()[id1];

	sc1->add_component<gdf::temporal::Chrono>(); // Already added

	sc1->add_component<FinalSceneBuilder>();

    sc1->add_component<CollisionManager>();

    GarbageCollector* gc = sc1->add_component<GarbageCollector>();
    gc->bind( &sc1->go_junkyard(), &sc1->c_junkyard() );

}
