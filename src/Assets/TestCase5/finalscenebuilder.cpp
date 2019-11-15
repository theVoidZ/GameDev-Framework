#include "finalscenebuilder.h"


#include "gameinfo.h"

#include "gameobject.h"
//#include "scene.h"
//#include "transform.h"
#include "tracker_ptr.h"

#include "spriterenderer.h"

#include "camera.h"
#include "animation.h"
#include "animationclip.h"


#include "texture2d.h"
#include "spritesheet.h"

#include "chrono.h"

//#include "garbagecollector.h"
#include "resourcemanager.h"

#include "camfollower.h"


#include "componentfactory.h"
#include "Biome.h"

#include "universecenter.h"
#include "SoG/sog.h"
#include "SoG/debuggeritem.h"

#include "collider.h"


FinalSceneBuilder::FinalSceneBuilder()
{

}

void FinalSceneBuilder::init(){
	load_resources();

}

void FinalSceneBuilder::post_init(){
	build();

}

void FinalSceneBuilder::load_resources(){
	// Loading ( Create a concrete instance of the resource as Texture2D.
	ResourceManager* rm = gdf::kernel::GameInfo::game_info.get()->get_component<ResourceManager>();

    gdf::graphic::Texture2D* ping_guo = rm->load_resource<gdf::graphic::Texture2D>("t2d:ping_guo", true);
	if( ping_guo != nullptr ){
        ping_guo->init("../media/pingguo.png");
//        ping_guo->pivot_ = sf::Vector2f(62, 82);
	}

    gdf::graphic::Texture2D* world = rm->load_resource<gdf::graphic::Texture2D>("t2d:terrain");
	if( world != nullptr )
		world->init("../media/terrain.jpg");

    gdf::graphic::Texture2D* belltower = rm->load_resource<gdf::graphic::Texture2D>("t2d:belltower");
    if( belltower != nullptr )
        belltower->init("../media/belltower.png");

    gdf::graphic::Texture2D* wildgoosepagoda = rm->load_resource<gdf::graphic::Texture2D>("t2d:wildgoosepagoda");
    if( wildgoosepagoda != nullptr )
        wildgoosepagoda->init("../media/wild goose pagoda.png");

	//-------------------------------------------------------------------------
    gdf::graphic::Texture2D* flame_t2d = rm->load_resource<gdf::graphic::Texture2D>("t2d:flame");
	if( flame_t2d != nullptr ){
		flame_t2d->init("../media/flame_2.png");
        flame_t2d->pivot_ = sf::Vector2f(62, 87);
	}

    gdf::graphic::SpriteSheet* flame_sheet = rm->load_resource<gdf::graphic::SpriteSheet>("ssh:flame");
	if( flame_sheet != nullptr ){
		flame_sheet->init( rm->get<gdf::graphic::Texture2D>("t2d:flame"), 1, 6, 6);
        flame_sheet->pivot_ = sf::Vector2f(62, 87);
	}

    gdf::animation::AnimationClip* flame_animc = rm->load_resource<gdf::animation::AnimationClip>("animc:flame");
    flame_animc->add_sprite( rm->get<gdf::graphic::SpriteSheet>("ssh:flame") );
	flame_animc->addFramesInSequence(0, 6, 65);

}

//! ALL GAMEOBJECT & COMPONENTS CREATED HERE ARE NOT INITED
void FinalSceneBuilder::build(){
	//! WARNING: NO COMPONENT OF GAMEOBJECT IS INITED DURING THE BUILD ( ALL ARE INITED AFTER THE BUILD )

	if( static_cast<gdf::kernel::Scene*>( host_object_ )->root().expired() ){
		std::cout << BOLD << FRED << "Cannot build scene, no root GameObject available" << RESET << std::endl;
		return;
	}

	ResourceManager* rm = gdf::kernel::GameInfo::game_info.get()->get_component<ResourceManager>();
	gdf::kernel::Scene* scene = static_cast<gdf::kernel::Scene*>( host_object_ );

    rm->verbose();

    gdf::kernel::GameObject* root = static_cast<gdf::kernel::Scene*>( host_object_ )->root().get();
    root->add_component<gdf::temporal::Chrono>();
    root->add_component<gdf::graphic::SpriteRenderer>();
    root->add_component<UniverseCenter>();
    root->add_component<Collider>();

    gdf::kernel::Camera* c1 = root->add_component<gdf::kernel::Camera>(&scene->cameras());

    //! OBSOLETE: Should be managed by an outer object. ( User-script ? )
    //! SUGG: PASS A CAMERA INSTEAD OF sf::View.
    gdf::kernel::GameInfo::game_info->bind( 0, root->get_component_tracker<gdf::kernel::Camera>(c1) );

    c1->set_aspect_ratio( {1.0, 1.0 } );
    c1->set_viewport( sf::FloatRect(0, 0, 1 , 1) );
    c1->move( {-250, -250});


//	------------------------------------------------------------------------------------

    gdf::kernel::GameObject* sog = scene->instantiate(root->hierarchy().get(), sf::Vector2f(200,200), 0, "SoG");
    sog->add_component<gdf::temporal::Chrono>();
    sog->add_component<gdf::graphic::SpriteRenderer>();
    sog->add_component<SoG>();
    sog->add_component<DebuggerItem>();
    sog->add_component<UniverseCenter>();

    gdf::kernel::GameObject* xfire = scene->instantiate("xfire");
    {
        Biome* biome = xfire->add_component<Biome>();

        gdf::kernel::Hierarchy* fire_h = xfire->add_component<gdf::kernel::Hierarchy>();
        root->hierarchy().get()->attach_child(xfire->hierarchy());

        gdf::kernel::Transform* fire_t = xfire->add_component<gdf::kernel::Transform>();
        fire_t->set_position({220, 200});
        fire_t->set_rotation(0);


        xfire->add_component<gdf::temporal::Chrono>();

        gdf::graphic::Sprite2D* sprt2d(new gdf::graphic::Sprite2D());
        sprt2d->setTexture2D( rm->get<gdf::graphic::Texture2D>("t2d:belltower") );
        gdf::graphic::SpriteRenderer* sprt2 = xfire->add_component<gdf::graphic::SpriteRenderer>();
        sprt2->setSprite2D(sprt2d);



        xfire->add_component<UniverseCenter>();
        xfire->add_component<Collider>();
        //------------------------------------------------------------------------------------
    }

    {
        gdf::kernel::GameObject* fire2 = scene->instantiate(xfire->hierarchy().get(), sf::Vector2f(200, -100), 0, "fire2");
            fire2->add_component<gdf::temporal::Chrono>();

            fire2->add_component<gdf::graphic::SpriteRenderer>();
            gdf::graphic::Sprite2D* sprt2d(new gdf::graphic::Sprite2D());
            sprt2d->setTexture2D( rm->get<gdf::graphic::Texture2D>("t2d:wildgoosepagoda") );
            gdf::graphic::SpriteRenderer* sprt2 = fire2->add_component<gdf::graphic::SpriteRenderer>();
            sprt2->setSprite2D(sprt2d);
/*
            // Animation - LEGACY MODE
            gdf::animation::Animation* anim2 = fire2->add_component<gdf::animation::Animation>();
            anim2->wrap_mode = gdf::animation::WrapMode::Loop;
            anim2->clip = rm->get<gdf::animation::AnimationClip>("animc:flame").get(); // already instantiated inside Animation
            anim2->play();
*/
            fire2->add_component<UniverseCenter>();
            fire2->add_component<Collider>();
    }

//    gdf::kernel::GameInfo::game_info.get()->backup_manager().get()->save("../media/scene0_root2.json");


/*
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::temporal::Chrono", &gdf::kernel::ComponentFactory::generic_ctor<gdf::temporal::Chrono>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::kernel::Transform", &gdf::kernel::ComponentFactory::generic_ctor<gdf::kernel::Transform>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::kernel::Hierarchy", &gdf::kernel::ComponentFactory::generic_ctor<gdf::kernel::Hierarchy>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::kernel::Camera", &gdf::kernel::ComponentFactory::generic_ctor<gdf::kernel::Camera>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("Biome", &gdf::kernel::ComponentFactory::generic_ctor<Biome>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("Spam", &gdf::kernel::ComponentFactory::generic_ctor<Spam>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::graphic::SpriteRenderer", &gdf::kernel::ComponentFactory::generic_ctor<gdf::graphic::SpriteRenderer>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("gdf::animation::Animation", &gdf::kernel::ComponentFactory::generic_ctor<gdf::animation::Animation>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("UniverseCenter", &gdf::kernel::ComponentFactory::generic_ctor<UniverseCenter>);
    gdf::kernel::GameInfo::game_info.get()->component_factory()->register_component("SoG", &gdf::kernel::ComponentFactory::generic_ctor<SoG>);

    gdf::kernel::GameInfo::game_info.get()->component_factory()->verbose();

    gdf::kernel::GameInfo::game_info.get()->backup_manager().get()->load("../media/scene0_root2.json");

    rm->verbose();
*/
}
