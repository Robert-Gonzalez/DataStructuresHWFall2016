/*
 *  upointer-private.hpp
 *
 *  CS 70 support code.
 *
 *  This code is support code for the ChunkyString assignment.  You do not
 *  need to modify this file, nor understand it.  The coding style in this
 *  file may not meet the usual standards for code in CS 70.
 *
 *  (c) 2007-2009 Melissa O'Neill.
 *
 */

template <typename T>
UnsharedPointer<T>::UnsharedPointer(T* ptr)
    : ptr_(ptr)
{
    // Nothing (else) to do.
}


template <typename T>
UnsharedPointer<T>::~UnsharedPointer()
{
    delete ptr_;
    ptr_ = nullptr;
}


template <typename T>
UnsharedPointer<T>::UnsharedPointer(const UnsharedPointer& uptr)
    : ptr_(uptr.ptr_ == nullptr ? nullptr : uptr.ptr_->heapcopy())
{
    // Nothing (else) to do.
}


template <typename T>
UnsharedPointer<T>& UnsharedPointer<T>::operator=(UnsharedPointer other)
{
    swap(other);
    return *this;
}


template <typename T>
T* UnsharedPointer<T>::operator->() const
{
    return ptr_;
}


template <typename T>
T& UnsharedPointer<T>::operator*() const
{
    return *operator->();
}


template <typename T>
void UnsharedPointer<T>::swap(UnsharedPointer<T>& other)
{
    T* saved = other.ptr_;
    other.ptr_ = ptr_;
    ptr_ = saved;
}



/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
