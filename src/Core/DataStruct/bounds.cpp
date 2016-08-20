#include "bounds.h"

Bounds::Bounds(sf::Vector2f center, sf::Vector2f size)
{
    this->center = center;
    this->size = size;
    this->extent = sf::Vector2f( size.x/2, size.y/2);
    this->max = center + this->extent;
    this->min = center - this->extent;

}

sf::Vector2f Bounds::closestPoint( sf::Vector2f point ){
    if( this->contains(point) ){
        return point;
    }else{
        if( point.x < center.x - extent.x ){
            if( point.y < center.y - extent.y ){
                // on the top-left
                return sf::Vector2f( center.x-extent.x, center.y-extent.y);
            }else if( point.y > center.y + extent.y ){
                // on the bottom-left
                return sf::Vector2f( center.x-extent.x, center.y+extent.y);
            }
        }else if( point.x > center.x + extent.x ){
            if( point.y < center.y - extent.y ){
                // on the top-right
                return sf::Vector2f( center.x+extent.x, center.y-extent.y);
            }else if( point.y > center.y + extent.y ){
                // on the bottom-right
                return sf::Vector2f( center.x+extent.x, center.y+extent.y);
            }
        }
    }
}

bool Bounds::contains( sf::Vector2f point ){
    if( ( point.x >= center.x - extent.x && point.x <= center.x + extent.x) &&
        ( point.y >= center.y - extent.y && point.y <= center.y + extent.y) ){
        return true;
    }else{
        return false;
    }
}

void Bounds::encapsulate( sf::Vector2f point ){
    sf::Vector2f new_size = Algorithm::max( center+extent, point) - Algorithm::min( center-extent, point );
    sf::Vector2f new_extent = sf::Vector2f( new_size.x/2, new_size.y/2);

    // Locate the direction of the extent...
    if( point.x > center.x + extent.x ){
        this->center.x += new_extent.x - this->extent.x;
    }else if( point.x < center.x - extent.x){
        this->center.x += -( (new_size.x - this->size.x) + this->center.x) + new_extent.x;
    }

    if( point.y > center.y + extent.y ){
        this->center.y += new_extent.y - this->extent.y;
    }else if( point.y < center.y - extent.y){
        this->center.y += -( (new_size.y - this->size.y) + this->center.y) + new_extent.y;
    }

    this->size = new_size;
    this->extent = sf::Vector2f( this->size.x/2, this->size.y/2 );
    this->min = this->center - extent;
    this->max = this->center + extent;

}

void Bounds::expand( float amount ){
    // Center remains the same
    this->size += sf::Vector2f(amount*2, amount*2 );
    this->extent = sf::Vector2f( this->size.x/2, this->size.y/2 );
    this->min = this->center - extent;
    this->max = this->center + extent;

}

void Bounds::expand( sf::Vector2f camount ){
    // Center remains the same
    this->size += sf::Vector2f(camount.x*2, camount.y*2 );
    this->extent = sf::Vector2f( this->size.x/2, this->size.y/2 );
    this->min = this->center - extent;
    this->max = this->center + extent;
}

bool Bounds::intersectRay( Ray ray ){
    //! NOTE: ray not completed
}


bool Bounds::intersects(Bounds bounds ){
    //! NOTE: intersect not completed
    // Focus is 'this'
    // -x side
    if( this->max.x < bounds.min.x ){
        return false;
    }else

    // +x side
    if( this->min.x > bounds.max.x ){
        return false;
    }else

    // -y side
    if( this->max.y < bounds.min.y ){
        return false;
    }else

    // +y side
    if( this->min.y > bounds.max.y ){
        return false;
    }else{
        // not on the SIDES
        return true;
    }

}

void Bounds::setMinMax(sf::Vector2f min, sf::Vector2f max ){
    if( min.x > max.x || min.y > max.y ){
        std::cout  << "Invalid args: " << " min > max " << std::endl;
        return;
    }

    this->min = min;
    this->max = max;

    this->size = max - min;
    this->extent = sf::Vector2f( this->size.x/2, this->size.y/2 );
    this->center = this->min + this->extent;
}

float Bounds::sqrDistance( sf::Vector2f point ){
    sf::Vector2f closest_point = closestPoint(point);
    return sqrt( pow(point.y - closest_point.y,2) + pow(point.x - closest_point.x,2) );
}

