#include "renderer.h"

#include "gameobject.h"
//#include "gameinfo.h"

//#include "gameobject.h"
//#include "transform.h"
//#include "monobehavior.h"
#include "camera.h"

#include "resource.h"

namespace gdf {
namespace graphic {


Renderer::Renderer()
{

}

Renderer::~Renderer(){

}

void Renderer::update(sf::Time){
    //Trigger onBecameXXX here
    std::vector< gdf::kernel::Viewport* >::iterator it;
    for( it = gdf::kernel::GameInfo::game_info.get()->viewports().begin();
         it != gdf::kernel::GameInfo::game_info.get()->viewports().end() ;
         it++ )
    {
        if( *it != nullptr ){
//            gdf::kernel::Viewport* vp = *it;
//            if( vp->is_assigned() ){ // Viewport is valid
//                // If the renderer is a part of the scene.
//                if( this->game_object()->scene() == vp->get_camera_scene() ){
//                    gdf::kernel::Camera* c = static_cast<gdf::kernel::Camera*> ( vp->camera );
//                    c->getBounds().intersects( getBounds() );
//
//                    /// INCOMPLETE
//                    ///
//                    ///
//                    ///
//                }
//            }
        }
    }
/*
    //! FIXME:for each scene and for each active camera
    for( Camera* camera : game_object()->scene()->cameras() ){
        if( camera-> )
        //! Renderer visibility policy
        // Renderer isVisible, when it is displayed on at least one camera.
        // Renderer isNotVisible, when it is not displayed on any camera
        tmp_visible = tmp_visible || camera->getBounds().intersects( getBounds() );

        if( tmp_visible ){
            if( is_visible == false ){
                is_visible = true;

                // trigger onBecomeVisible
                //! WARNING: SHOULD BE the local game_object.
                for (gdf::kernel::MonoBehavior* m : this->game_object()->getComponentsOfType<gdf::kernel::MonoBehavior>() ) {
                    if( m->enabled() ){
                        //! CLBK: onBecameVisible
                        m->on_became_visible();
                    }
                }
            }
        }else{
            if( is_visible == true ){
                is_visible = false;
                for (gdf::kernel::MonoBehavior* m : this->game_object()->get_components_of_type<gdf::kernel::MonoBehavior>() ) {
                    if( m->enabled() ){
                        //! CLBK: onBecameInvisible
                        m->on_became_invisible();
                    }
                }

            }
        }
    }
*/
}

void Renderer::draw(sf::RenderTarget &target, sf::RenderStates states) const{
//----------------------------------------------------------------------------------
//    //! DEBUG: Displaying GO axis
//    //! SUGG: Create a second layer of Renderer for debug purposes.
/// X-Y axis
    sf::RectangleShape r1 = sf::RectangleShape( {100, 1} );
    r1.setOutlineColor(sf::Color::Blue);
    r1.setFillColor(sf::Color::Blue);

    sf::RectangleShape r2 = sf::RectangleShape( {1, 100} );
    r2.setOutlineColor(sf::Color::Red);
    r2.setFillColor(sf::Color::Red);

    //target.draw(r1, states);
    //target.draw(r2, states);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

    gdf::kernel::Hierarchy* h_this = game_object()->get_component<gdf::kernel::Hierarchy>();
    gdf::kernel::Hierarchy* h_parent;
    if( h_this->parent_ != nullptr ){
        h_parent = h_this->parent();
    }

    /// Line to PARENT
    sf::VertexArray va(sf::Lines, 2);
    va[0].position = {0, 0};
    va[1].position = -game_object()->transform().get()->get_position() ;
//    gdf::kernel::Transform* tt = game_object()->transform();
//    va[1].position = - ( sf::Vector2f(tt->get_position().x * tt->get_scale().x, tt->get_position().y * tt->get_scale().y ) );

    //target.draw( va, states);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Draw AABB
    Bounds AABB = this->getBounds();

    sf::VertexArray r_aabb(sf::LinesStrip, 5);
    r_aabb[0].position = AABB.min();
    r_aabb[1].position = {AABB.min().x + AABB.size().x, AABB.min().y };
    r_aabb[2].position = {AABB.min().x + AABB.size().x, AABB.min().y + AABB.size().y };
    r_aabb[3].position = {AABB.min().x , AABB.min().y + AABB.size().y };
    r_aabb[4].position = AABB.min();

    r_aabb[0].color = sf::Color::Blue;
    r_aabb[1].color = sf::Color::Blue;
    r_aabb[2].color = sf::Color::Blue;
    r_aabb[3].color = sf::Color::Blue;

    //target.draw( r_aabb, states);


    if( drawable_ != nullptr)
        target.draw( *drawable_, states );
}

Bounds Renderer::getBounds() const{
    return Bounds();
}

Bounds Renderer::getGlobalBounds() const{
    if( game_object()!= nullptr ){
        if( !game_object()->transform().expired() ){
            sf::Vector2f go_pos = game_object()->transform().get()->get_world_position();
            return Bounds( go_pos, sf::Vector2f() );
        }
    }

    return Bounds();
}

}}
