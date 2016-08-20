#include "renderer.h"

#include "Core/System/transform.h"
#include "Core/System/camera.h"
#include "Core/System/monobehavior.h"

Renderer::Renderer()
{
    sortig_layer_id = 0;
    sorting_layer_name = "";
    sorting_order = 0;
    receive_shadows = true;
}

Renderer::~Renderer(){

}

void Renderer::update(sf::Time){
    if( gdf::kernel::GameInfo::game_info->active_scene() == nullptr )
        return;


    //Trigger onBecameXXX here
    bool tmp_visible = false;
    for( Camera* camera : gdf::kernel::GameInfo::game_info->active_scene()->cameras() ){
        //! Renderer visibility policy
        // Renderer isVisible, when it is displayed on at least one camera.
        // Renderer isNotVisible, when it is not displayed on any camera
        tmp_visible = tmp_visible || camera->getBounds().intersects( getBounds() );

        if( tmp_visible ){
            if( is_visible == false ){
                is_visible = true;

                // trigger onBecomeVisible
                //! WARNING: SHOULD BE the local game_object.
                foreach (MonoBehavior* m, getComponentsOfType<MonoBehavior>() ) {
                    if( m->is_enabled() ){
                        //! CLBK: onBecameVisible
                        m->onBecameVisible();
                    }
                }
            }
        }else{
            if( is_visible == true ){
                is_visible = false;
                foreach (MonoBehavior* m, getComponentsOfType<MonoBehavior>() ) {
                    if( m->is_enabled() ){
                        //! CLBK: onBecameInvisible
                        m->onBecameInvisible();
                    }
                }

            }
        }
    }

    is_visible = tmp_visible;

}

Bounds Renderer::getBounds(){
    return Bounds();
}

bool Renderer::isEnabled(){
    return enabled;
}
