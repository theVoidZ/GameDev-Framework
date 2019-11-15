#ifndef FINALKERNEL_H
#define FINALKERNEL_H

#include <iostream>

#include "kernelrules.h"

class FinalKernel : public gdf::kernel::KernelRules
{
    public:
        FinalKernel();

    public:
        void on_init();
};

#endif // FINALRKERNEL_H
