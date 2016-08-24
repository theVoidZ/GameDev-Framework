#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "kernel/component.h"

namespace gdf {
namespace kernel {

class Hierarchy : public gdf::kernel::Component
{
    Q_OBJECT
    public:
        Hierarchy();
        ~Hierarchy();

    public:

        void attach_child( Hierarchy* child );

        void detach_child( Hierarchy* child );

        void attach_to(Hierarchy* parent_);

        Hierarchy* detach();

        void detach_children();

    public:
        Hierarchy* get_child(int index ) const;

        bool is_child_of( Hierarchy* parent_ ) const;
    public:

//        //! Changes the index to the first ( among children )
//        void set_as_first_sibling();

//        //! Changes the index to the last ( among children )
//        void set_as_sast_sibling();

//        //! Changes the index to 'index' ( among children )
//        void set_sibling_index( int index );

//        //! Returns the index ( among children )
//        int get_sibling_index() const; // ???

        // Getters
        //!
        Hierarchy* parent() const;

        //!
        const std::list<Hierarchy *>& children() const;

        //! Returns the topmost Hierarchy in the hierarchy.
        /*!
         * This methods does return systematically the root of the scene ( hierarchy ).
         * \return Topmost Hierarchy
         */
        Hierarchy* root() const;

        //! Returns the top-most Hierarchy that is connected to this Hierarchy.
        /*!
         * This methods does not return systematically the root of the scene ( hierarchy )
         * but returns the local root of this Hierarchy.
         * \return Topmost Hierarchy
         */
        Hierarchy* topmost_root();

        //! Returns the number of children
        unsigned int child_count() const;


    public:
        //! Parent of the Hierarchy.
        Hierarchy* parent_ = nullptr;

        //! Children attached to this Hierarchy.
        std::list< Hierarchy* > children_;

};

}}

#endif // HIERARCHY_H
