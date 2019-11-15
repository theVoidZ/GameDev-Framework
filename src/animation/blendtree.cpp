#include "blendtree.h"

namespace gdf {
namespace animation{

BlendTree::BlendTree()
{

}

void BlendTree::update_function(){

    function_ = [this](float val)->int{
        if( clips_.size() > 0 && clips_.size() == threshold_.size()+1 ){
            if( clips_.size() == 1 ){
                // Returns the first clip
                return 0;
            }else{

                for( int i=0; i <= threshold_.size(); i++ ){
                    if( i== 0 ){
                        if( val < threshold_[i] ){
                            return 0;
                        }
                    }else if( i == threshold_.size() ){
                        if( val > threshold_[i-1] ){
                            return i;
                        }
                    }else{
                        if( val >= threshold_[i-1] && val < threshold_[i] ){
                            return i;
                        }
                    }
                }

            }
        }
    };


}

}}
