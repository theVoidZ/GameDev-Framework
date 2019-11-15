#include "collisionmanager.h"

#include "gameobject.h"
#include "scene.h"
#include "collider.h"

CollisionManager::CollisionManager()
{

}

void CollisionManager::fixed_update(sf::Time dt){
    gdf::kernel::ComponentContainer* cc = host_object<gdf::kernel::ComponentContainer>();
    if( cc != nullptr ){
        // The component is a gameobject component
        if( dynamic_cast<gdf::kernel::Scene*>(cc) != nullptr ){
            gdf::kernel::Scene* sc = dynamic_cast<gdf::kernel::Scene*>(cc);

            std::list<Collider*> lcolliders = sc->root().get()->get_components_in_children_of_type<Collider>();
            std::list<Collider*>::iterator it1, it2;

            if( !lcolliders.empty() ){

                // clear the refhresh indicator
                std::map< PairCollider*, bool>::iterator it = colliding_objects.begin();

                for( it; it != colliding_objects.end(); it++ ){
                    (*it).second = false;
                }


                for( it1 = lcolliders.begin(); it1 != lcolliders.end(); it1 ++){
                    for( it2 = it1; it2 != lcolliders.end(); it2 ++){
                        if( it1 == it2 ){
                        }else{
                            if ( (*it1)->global_aabb->intersects2( *(*it2)->global_aabb ) ){

                                PairCollider* exist = find( *it1, *it2 );

                                std::list<MonoBehavior*> l = (*it1)->game_object()->get_components_of_type<MonoBehavior>();
                                std::list<MonoBehavior*> l2 = (*it2)->game_object()->get_components_of_type<MonoBehavior>();


                                if( exist != nullptr ){
                                    for (MonoBehavior* mb : l) {
                                        mb->on_stay_collision( *it1, *it2);
                                    }

                                    for (MonoBehavior* mb : l2) {
                                        mb->on_stay_collision( *it2, *it1);
                                    }

                                    //refresh the item as existing in the list
                                    colliding_objects[exist] = true;

                                }else{
                                    for (MonoBehavior* mb : l) {
                                        mb->on_enter_collision( *it1, *it2);
                                    }

                                    for (MonoBehavior* mb : l2) {
                                        mb->on_enter_collision( *it2, *it1);
                                    }

                                    // add the item to the colliding object list
                                    Collider* first, *second;
                                    if( *it1 < *it2 ){
                                        first = *it1;
                                        second = *it2;
                                    }else{
                                        first = *it1;
                                        second = *it2;
                                    }

                                    colliding_objects[ new PairCollider(first, second) ] = true;

                                }


                            }
                        }
                    }
                }



            }

            std::map< PairCollider*, bool>::iterator it = colliding_objects.begin();

            for( it; it != colliding_objects.end(); it++ ){
                // didnt collide anymore
                if( (*it).second == false ){
                    Collider* c1, *c2;
                    c1 = (*it).first->first;
                    c2 = (*it).first->second;

                    std::list<MonoBehavior*> l1 = c1->game_object()->get_components_of_type<MonoBehavior>();
                    for (MonoBehavior* mb : l1) {
                        mb->on_exit_collision( c1, c2);
                    }

                    std::list<MonoBehavior*> l2 = c2->game_object()->get_components_of_type<MonoBehavior>();
                    for (MonoBehavior* mb : l2) {
                        mb->on_exit_collision( c2, c1);
                    }

                    colliding_objects.erase( it );
                }
            }


        }
    }

}

PairCollider* CollisionManager::find(Collider *col1, Collider *col2){
    std::map< PairCollider*, bool>::iterator it = colliding_objects.begin();

    for( it; it != colliding_objects.end(); it++ ){
        Collider* first, *second;
        if( col1 < col2 ){
            first = col1;
            second = col2;
        }else{
            first = col2;
            second = col1;
        }

        if( (*it).first->first == first && (*it).first->second == second ){
            return (*it).first;
        }
    }

    return nullptr;
}
