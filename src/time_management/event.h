#ifndef EVENT_H
#define EVENT_H

namespace gdf {
namespace kernel{
class Object;

}}

class Event
{
    public:
        Event();
        ~Event();

    public:
        virtual void verbose() const = 0;

    public:
        virtual bool exec() = 0;
        virtual bool reverse_exec() = 0;

        unsigned long int timestamp = 0;
        gdf::kernel::Object* target; // ???

};

#endif // EVENT_H
