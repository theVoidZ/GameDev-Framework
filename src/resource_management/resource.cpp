#include "resource.h"

Resource::Resource()
{

}

Resource::Resource(const Resource &res){
    this->id_ = res.id_;
    this->is_shared = res.is_shared;

    std::cout << "Resource::copy ctor " << std::endl;
}
