/*
 *  upointer.hpp
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

#ifndef UNSHARED_POINTER_HPP
#define UNSHARED_POINTER_HPP 1

#include <new>
#include <cstddef>

template <typename T>
class UnsharedPointer {
public:
    explicit UnsharedPointer(T* ptr = nullptr);
    ~UnsharedPointer();
    UnsharedPointer(const UnsharedPointer& uptr);
    UnsharedPointer& operator=(UnsharedPointer uptr);
    T* operator->() const;
    T& operator*() const;
    void swap(UnsharedPointer<T>& other);

private:
    T* ptr_;
};

#include "upointer-private.hpp"

#endif // UNSHARED_POINTER_HPP


/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
