#include "bounds.h"

Bounds::Bounds(sf::Vector2f center, sf::Vector2f half_size)
{
    this->center_ = center;
    this->size_ = half_size+half_size;
    this->extent_ = half_size;
    this->max_ = center + this->extent_;
    this->min_ = center - this->extent_;

}

Bounds Bounds::from_min_max(sf::Vector2f min, sf::Vector2f max){
    Bounds b;
    if( min.x > max.x || min.y > max.y ){
        std::cout  << "Invalid args: " << " min > max " << std::endl;
        return b;
    }

    b.min_ = min;
    b.max_ = max;

    b.size_ = max - min;
    b.extent_ = sf::Vector2f( b.size_.x/2, b.size_.y/2 );
    b.center_ = b.min_ + b.extent_;
    return b;
}

Bounds Bounds::from_center_extent(sf::Vector2f center, sf::Vector2f extent){
    Bounds b;
    b.center_ = center;
    b.size_ = extent+extent;
    b.extent_ = extent;
    b.max_ = center + b.extent_;
    b.min_ = center - b.extent_;
    return b;
}

Bounds Bounds::from_center_size(sf::Vector2f center, sf::Vector2f size){
    Bounds b;
    b.center_ = center;
    b.size_ = size;
    b.extent_ = {b.size().x/2, b.size().y/2};
    b.max_ = center + b.extent_;
    b.min_ = center - b.extent_;
    return b;
}

Bounds Bounds::from_min_size(sf::Vector2f min, sf::Vector2f size){
    Bounds b;
    b.min_ = min;
    b.max_ = b.min() + size;

    b.size_ = size;
    b.extent_ = sf::Vector2f( b.size_.x/2, b.size_.y/2 );
    b.center_ = b.min_ + b.extent_;
    return b;
}


void Bounds::set_min_max(sf::Vector2f min, sf::Vector2f max ){
    if( min.x > max.x || min.y > max.y ){
        std::cout  << "Invalid args: " << " min > max " << std::endl;
        return;
    }

    this->min_ = min;
    this->max_ = max;

    this->size_ = max - min;
    this->extent_ = sf::Vector2f( this->size_.x/2, this->size_.y/2 );
    this->center_ = this->min_ + this->extent_;
}

void Bounds::encapsulate( sf::Vector2f point ){
    sf::Vector2f new_size = gdf::system::Algorithm::max( center_+extent_, point) - gdf::system::Algorithm::min( center_-extent_, point );
    sf::Vector2f new_extent = sf::Vector2f( new_size.x/2, new_size.y/2);

    // Locate the direction of the extent...
    if( point.x > center_.x + extent_.x ){
        this->center_.x += new_extent.x - this->extent_.x;
    }else if( point.x < center_.x - extent_.x){
        this->center_.x += -( (new_size.x - this->size_.x) + this->center_.x) + new_extent.x;
    }

    if( point.y > center_.y + extent_.y ){
        this->center_.y += new_extent.y - this->extent_.y;
    }else if( point.y < center_.y - extent_.y){
        this->center_.y += -( (new_size.y - this->size_.y) + this->center_.y) + new_extent.y;
    }

    this->size_ = new_size;
    this->extent_ = sf::Vector2f( this->size_.x/2, this->size_.y/2 );
    this->min_ = this->center_ - this->extent_;
    this->max_ = this->center_ + this->extent_;

}

void Bounds::expand( float amount ){
    // Center remains the same
    this->size_ += sf::Vector2f(amount*2, amount*2 );
    this->extent_ = sf::Vector2f( this->size_.x/2, this->size_.y/2 );
    this->min_ = this->center_ - this->extent_;
    this->max_ = this->center_ + this->extent_;

}

void Bounds::expand( sf::Vector2f camount ){
    // Center remains the same
    this->size_ += sf::Vector2f(camount.x*2, camount.y*2 );
    this->extent_ = sf::Vector2f( this->size_.x/2, this->size_.y/2 );
    this->min_ = this->center_ - this->extent_;
    this->max_ = this->center_ + this->extent_;
}

sf::Vector2f Bounds::closestPoint( sf::Vector2f point ){
    if( this->contains(point) ){
        return point;
    }else{
        if( point.x < center_.x - extent_.x ){
            if( point.y < center_.y - extent_.y ){
                // on the top-left
                return sf::Vector2f( center_.x - extent_.x, center_.y - extent_.y);
            }else if( point.y > center_.y + extent_.y ){
                // on the bottom-left
                return sf::Vector2f( center_.x - extent_.x, center_.y + extent_.y);
            }
        }else if( point.x > center_.x + extent_.x ){
            if( point.y < center_.y - extent_.y ){
                // on the top-right
                return sf::Vector2f( center_.x + extent_.x, center_.y - extent_.y);
            }else if( point.y > center_.y + extent_.y ){
                // on the bottom-right
                return sf::Vector2f( center_.x + extent_.x, center_.y + extent_.y);
            }
        }
    }
}

bool Bounds::contains( sf::Vector2f point ){
    if( ( point.x >= center_.x - extent_.x && point.x <= center_.x + extent_.x) &&
        ( point.y >= center_.y - extent_.y && point.y <= center_.y + extent_.y) ){
        return true;
    }else{
        return false;
    }
}

//bool Bounds::intersectRay( Ray ray ){
//    //! NOTE: ray not completed
//}

bool Bounds::intersects(Bounds other)
{
    //this right > that left                                          this left < that right
    if(center_.x + extent_.x > other.center_.x - other.extent_.x || center_.x - extent_.x < other.center_.x + other.extent_.x)
    {
    // This bottom > that top
        if(center_.y + extent_.y > other.center_.y - other.extent_.y || center_.y - extent_.y < other.center_.y + other.extent_.y)
        {
            return true;
        }
    }
    return false;
}

bool Bounds::intersects2(Bounds bounds ){
    //! NOTE: intersect not completed
    // Focus is 'this'
    // -x side
    if( this->max_.x < bounds.min_.x ){
        return false;
    }else

    // +x side
    if( this->min_.x > bounds.max_.x ){
        return false;
    }else

    // -y side
    if( this->max_.y < bounds.min_.y ){
        return false;
    }else

    // +y side
    if( this->min_.y > bounds.max_.y ){
        return false;
    }else{
        // not on the SIDES
        return true;
    }

}

float Bounds::sqrDistance( sf::Vector2f point ){
    sf::Vector2f closest_point = closestPoint(point);
    return sqrt( pow(point.y - closest_point.y,2) + pow(point.x - closest_point.x,2) );
}

sf::Vector2f Bounds::size() const{
    return this->size_;
}

sf::Vector2f Bounds::extent() const{
    return this->extent_;
}

sf::Vector2f Bounds::center() const{
    return this->center_;
}

sf::Vector2f Bounds::min() const{
    return this->min_;
}

sf::Vector2f Bounds::max() const{
    return this->max_;
}

//std::ostream &operator<<(std::ostream &os, Bounds const &b) {
//    return os << ITALIC << "min: {" << b.min.x << "," << b.min.y << "}, max: {" << b.max.x << "," << b.max.y << "}, size: {" << b.size.x << "," << b.size.y << "}." ;
//}
