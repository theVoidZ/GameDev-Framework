#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <list>

#include "component.h"

#include "tracker_ptr.h"

namespace gdf {
namespace kernel {

//////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hierarchy : public gdf::kernel::Component
{
    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// default ctor
        Hierarchy();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// default dtor
        ~Hierarchy();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void init();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void attach_child(tracker_ptr<Hierarchy> child );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// NOTE: erase item from container
        void detach_child(tracker_ptr<Hierarchy> child );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Centralized version
//        void attach_to( tracker_ptr<Hierarchy> h_parent);
//        void detach_from(tracker_ptr<Hierarchy> h_parent);
//        Hierarchy* detach();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        void detach_children();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool is_child_of(tracker_ptr<Hierarchy> parent_ ) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:


        // Getters
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        Hierarchy* parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::list< tracker_ptr<Hierarchy> >& children();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int child_count() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////


    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        char link_checker = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Parent of the Hierarchy.
        Hierarchy* parent_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Children attached to this Hierarchy.
        std::list< tracker_ptr<Hierarchy> > children_;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

}}

#endif // HIERARCHY_H