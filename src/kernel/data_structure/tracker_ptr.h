
#ifndef TRACKER_PTR_H
#define TRACKER_PTR_H

#include <memory>
#include <iostream>

namespace gdf {
namespace kernel {

template< typename T > class tracker_ptr;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The manager_object is an object that manages the lifetime of an object throughout a tracker_ptr
///
class manager_object{
    template< class T >
    friend class tracker_ptr;

    private:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        manager_object(){

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~manager_object(){

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// The object managed by the manager object.
        ///
        void* managed_object = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Number of tracker_ptr attached to the managed_object
        ///
        /// Whenever a tracker ptr is attached, increase \a count by one.
        ///
        /// Whenever a tracker ptr is released, decerase \a count by one, if count is equal to zero, delete the
        /// manager object as there is no tracker refering to it.
        ///
        unsigned int count = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Tracker ptr is a smart pointer used to manage the lifetime of an object
///
template< typename T >
class tracker_ptr{
    template< class U >
    friend class tracker_ptr;

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Moves an object from a manager object \a 'from' to an other manager object \a 'to'
        ///
        /// WARNING: TESTING FIRST ( manager object != nullptr )
        ///
        static void move(tracker_ptr<T> &from, tracker_ptr<T> &to);
        ///
        /// Templated version of move(), allowing it to be called with different template of tracker_ptr
        ///
        template< class U >
        static void move(tracker_ptr<T> &from, tracker_ptr<U> &to);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        tracker_ptr();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        tracker_ptr(T *obj);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        tracker_ptr( const tracker_ptr<T>& other);
        ///
        template< class U >
        tracker_ptr( const tracker_ptr<U>& other);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        tracker_ptr<T>& operator =(const tracker_ptr<T> &other);
        ///
        ///
        template< class U >
        tracker_ptr<T>& operator =(const tracker_ptr<U>& other);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
//        tracker_ptr( tracker_ptr<T>&& other );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
//        template< class U >
//        tracker_ptr( tracker_ptr<U>&& other );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
//        tracker_ptr<T>& operator =(tracker_ptr&& other);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
//        template< class U >
//        tracker_ptr<T>& operator =(tracker_ptr<U>&& other);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~tracker_ptr();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator <(const tracker_ptr<T>& rhs) const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //! NOTE: Propagate the CHANGES....
//        T* operator->() const{
//            return static_cast<T*>(manager_object_->managed_object);
//        }

    public:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Detach the tracker from the \a 'manager object' and becomes \b expired, this will decrease the count's manager object by one,
        /// If the count is zero, destroy both the managed object and the manager object
        ///
        void release();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Destroy the managed object (if exist), the manager object and trackers are not affected.
        /// the reset method can be called from any tracker_ptr.
        ///
        void reset();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Retrieve the object held by the manager object
        /// \return Object as type T
        ///
        T* get() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //! Improve it the distinguish between a null managed object and absent manager object.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// A Tracker ptr is expired when it does not point to any manager object.
        bool expired() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Number of tracker ptr sharing, pointing this tracker's manager object.
        /// \return Number of tracker ptr, returns -1 if the tracker is expired.
        ///
        int tracker_count() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

    public:
        bool operator==(tracker_ptr& rhs) const;

        template< class U >
        bool operator==(tracker_ptr<U>& rhs) const;

    protected:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines an ownership policy allowing ONLY one tracker_ptr to be the owner.
        ///
        /// NOTE: ACTUALLY, every single tracker_ptr has an owner rank.
        /// WARNING: Not used yet
        ///
        bool is_owner_ = false;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// The manager object
        manager_object* manager_object_ = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void tracker_ptr<T>::move(tracker_ptr<T> &from, tracker_ptr<T> &to){
    if( from.manager_object_ != nullptr && to.manager_object_ != nullptr ){
        if( from.manager_object_->managed_object != nullptr ){

            // If the host manager object has an object, delete it
            if( to.manager_object_->managed_object != nullptr ){
                to.reset();
            }

            // Move the object
            to.manager_object_->managed_object = from.manager_object_->managed_object;
            from.manager_object_->managed_object = nullptr;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
template< class U >
void tracker_ptr<T>::move(tracker_ptr<T> &from, tracker_ptr<U> &to){
    if( from.manager_object_ != nullptr && to.manager_object_ != nullptr ){
        if( from.manager_object_->managed_object != nullptr ){

            // If the host manager object has an object, delete it
            if( to.manager_object_->managed_object != nullptr ){
                to.reset();
            }

            // Move the object
            to.manager_object_->managed_object = from.manager_object_->managed_object;
            from.manager_object_->managed_object = nullptr;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T>::tracker_ptr(){
//    std::cout << "+tracker_ptr: default EMPTY constructor" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T>::tracker_ptr(T* obj){
    if( obj != nullptr ){
        this->manager_object_ = new manager_object();
        this->manager_object_->managed_object = obj;
        this->manager_object_->count = 1;
//        std::cout << "+tracker_ptr(T*) count:" << manager_object_->count << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T>::tracker_ptr(const tracker_ptr<T> &other){
    if( other.manager_object_ != nullptr ){
        this->manager_object_ = other.manager_object_;
        this->manager_object_->count++;
//        std::cout << "+tracker_ptr(const tracker&), count:" << manager_object_->count << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
template< class U >
tracker_ptr<T>::tracker_ptr( const tracker_ptr<U>& other){
    if( other.manager_object_ != nullptr ){
        this->manager_object_ = other.manager_object_;
        this->manager_object_->count++;
//        std::cout << "+tracker_ptr(const tracker<U>&), count:" << manager_object_->count << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T> &tracker_ptr<T>::operator =(const tracker_ptr<T>& other){
    if( this == &other ){
        return *this;
    }

    // Release when success (other is not invalid )
    this->release();

    if( other.manager_object_ != nullptr ){
        this->manager_object_ = other.manager_object_;
        this->manager_object_->count++;
//        std::cout << "+tracker_ptr::operator=(const tracker<T>&), count:" << manager_object_->count << std::endl;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template < typename T >
template< class U >
tracker_ptr<T>& tracker_ptr<T>::operator =(const tracker_ptr<U>& other){
//    if( this == &other ){
//        return *this;
//    }

    // Release when success (other is not invalid )
    this->release();

    if( other.manager_object_ != nullptr ){
        this->manager_object_ = other.manager_object_;
        this->manager_object_->count++;
//        std::cout << "+tracker_ptr::operator=(const tracker<U>&), count:" << manager_object_->count << std::endl;
    }

    return *this;
}
/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T>::tracker_ptr( tracker_ptr<T>&& other ){
    // Create new manager_object to host the managed_object.
    this->manager_object_ = new manager_object();
    this->manager_object_->count++;

    // Move
    if( other.manager_object_ != nullptr ){
        this->manager_object_->managed_object = other.manager_object_->managed_object;
        other.manager_object_->managed_object = nullptr;
        std::cout << "+tracker_ptr(tracker<T>&&), count:" << manager_object_->count << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
template< class U >
tracker_ptr<T>::tracker_ptr( tracker_ptr<U>&& other ){
    // Create new manager_object to host the managed_object.
    this->manager_object_ = new manager_object();
    this->manager_object_->count++;

    // Move
    if( other.manager_object_ != nullptr ){
        this->manager_object_->managed_object = other.manager_object_->managed_object;
        other.manager_object_->managed_object = nullptr;
        std::cout << "+tracker_ptr(tracker<U>&&), count:" << manager_object_->count << std::endl;
    }
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//template< typename T >
//tracker_ptr<T>& tracker_ptr<T>::operator =(tracker_ptr&& other){

//    // Release when success (other is not invalid )
//    this->release();

//    if( other.manager_object_ != nullptr ){
//        this->manager_object_ = other.manager_object_;
//        this->manager_object_->count++;
//        std::cout << "+tracker_ptr::operator=(tracker<T>&&), count:" << manager_object_->count << std::endl;
//    }
//    return *this;

///*
//    if( this->manager_object_ != nullptr ){
//        if( this->manager_object_->managed_object != nullptr ){
////            this->reset();
//        }
//    }else{
//        this->manager_object_ = new manager_object();
//        this->manager_object_->count++;
//    }

//    if( other.manager_object_ != nullptr ){
//        this->manager_object_->managed_object = other.manager_object_->managed_object;
//        other.manager_object_->managed_object = nullptr;
//    }
//    std::cout << "+tracker_ptr::operator=(tracker<T>&&), count:" << manager_object_->count << std::endl;
//*/
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//template< typename T >
//template< class U >
//tracker_ptr<T>& tracker_ptr<T>::operator =(tracker_ptr<U>&& other){
//    // Release when success (other is not invalid )
//    this->release();

//    if( other.manager_object_ != nullptr ){
//        this->manager_object_ = other.manager_object_;
//        this->manager_object_->count++;
//        std::cout << "+tracker_ptr::operator=(tracker<U>&&), count:" << manager_object_->count << std::endl;
//    }

//    return *this;

///*
//    if( this->manager_object_ != nullptr ){
//        this->reset();
//    }else{
//        this->manager_object_ = new manager_object();
//        this->manager_object_->count++;
//    }

//    if( other.manager_object_ != nullptr ){
//        this->manager_object_->managed_object = other.manager_object_->managed_object;
//        other.manager_object_->managed_object = nullptr;
//    }
//    std::cout << "+tracker_ptr::operator=(tracker<U>&&), count:" << manager_object_->count << std::endl;
//*/
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
tracker_ptr<T>::~tracker_ptr(){
//    std::cout << "~tracker_ptr(): default destructor " << std::endl;
    release();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
bool tracker_ptr<T>::operator <(const tracker_ptr<T>& rhs) const{
    if( this->manager_object_ == rhs.manager_object_ ){
        return true;
    }else{
        return manager_object_ < rhs.manager_object_;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T > void tracker_ptr<T>::release(){
    if( manager_object_ != nullptr ){
//        std::cout << "-tracker released: count=" << (manager_object_->count-1) <<std::endl;
        manager_object_->count--;
//        std::cout << "-release(): count:" << manager_object_->count;
        if( manager_object_->count == 0 ){
            //! NOTE: Force a cast of the managed object to T* in order to call the right dtor, since manager_object is not template class.
            delete static_cast<T*>(manager_object_->managed_object);
            delete manager_object_;
//            std::cout << ",  <managed_object deleted>" ;
        }
        manager_object_ = nullptr;
//        std::cout << std::endl;

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
void tracker_ptr<T>::reset(){
    if( manager_object_ != nullptr ){
//        std::cout << "-reset(): count:" << manager_object_->count << std::endl;
        if( manager_object_->managed_object != nullptr ){
            delete static_cast<T*>(manager_object_->managed_object);
        }
        manager_object_->managed_object = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
T* tracker_ptr<T>::get() const{
    if( manager_object_ != nullptr ){
        return static_cast<T*>(manager_object_->managed_object);
    }else{
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
bool tracker_ptr<T>::expired() const{
    if( manager_object_ == nullptr ){
        return true;
    }else{
        return manager_object_->managed_object == nullptr ? true : false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
int tracker_ptr<T>::tracker_count() const{
    if( manager_object_ != nullptr )
        return manager_object_->count;
    else
        return -1;
}

template< typename T >
bool tracker_ptr<T>::operator==(tracker_ptr<T>& rhs) const{
    if( this->manager_object_ == rhs.manager_object_ ){
        return true;
    }else{
        return false;
    }
}

template< typename T >
template< class U >
bool tracker_ptr<T>::operator==(tracker_ptr<U>& rhs) const{
    if( this->manager_object_ == rhs.manager_object_ ){
        return true;
    }else{
        return false;
    }
}


}}

#endif // TRACKER_PTR_H
