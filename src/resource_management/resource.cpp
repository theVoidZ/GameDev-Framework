#include "resource.h"

Resource::Resource()
{

}

Resource::Resource(const Resource &res)
    :gdf::kernel::Object(res)
{
    this->id_ = res.id_;
    this->is_shared_ = res.is_shared_;
    this->filename_ = res.filename_;
}

Resource::~Resource(){

}

void Resource::verbose(){
//    std::cout << BOLD << "id="<<std::left <<std::setw(9) << id_ << RESET_BOLD << "name: " << std::left << std::setw(24) << name_ << "shared: " << std::boolalpha << std::setw(10) << is_shared_ << "use count: " << std::left << std::setw(4) << use_count << std::endl;
//    if( !filename_.empty() )
//        std::cout << "\tfilename: " << std::left << std::setw(30) << filename_ << std::endl;
}
