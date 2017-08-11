/*
 *  string-wrapper.cpp
 *
 *  CS 70 support code.
 *
 *  This code is support code for the ChunkyString assignment.  You do not
 *  need to modify this file, nor understand it.  The coding style in this
 *  file may not meet the usual standards for code in CS 70.
 *
 *  (c) 2007-2009 Melissa O'Neill.
 */

#include "string-wrapper.hpp"
#include <stdexcept>
#include <dlfcn.h>

// GenericIterator Implementation ///////////////////////////////////////

// The wrapper class does not expose a default constructor, so our default
// constructor returns end() applied to an empty string.  It's as good as
// anything else.
GenericIterator::GenericIterator()
    : iter_(nullptr)
{
    GenericString().end().iter_.swap(iter_);
}

GenericIterator::GenericIterator(IteratorWrapper* iter)
    : iter_(iter)
{
    // Nothing (else) to do.
}

// Operations
GenericIterator& GenericIterator::operator=(const GenericIterator& rhs)
{
    *iter_ = *(rhs.iter_);
    return *this;
}


GenericIterator& GenericIterator::operator++()
{
    ++(*iter_);
    return *this;
}


GenericIterator& GenericIterator::operator--()
{
    --(*iter_);
    return *this;
}


GenericIterator::reference GenericIterator::operator*() const
{
    return *(*iter_);
}


GenericIterator::pointer GenericIterator::operator->() const
{
    return &(operator*());
}


bool GenericIterator::operator==(const GenericIterator& rhs) const
{
    return *iter_ == *(rhs.iter_);
}


bool GenericIterator::operator!=(const GenericIterator& rhs) const
{
    return *iter_ != *(rhs.iter_);
}


IteratorWrapper* GenericIterator::underlyingIterator() const
{
    return &*iter_;
}


// GenericString Implementation ///////////////////////////////////////


GenericString::factoryPtr GenericString::factory     = nullptr;

// Constructors
GenericString::GenericString()
    : strptr_(factory())
{
    // Nothing (else) to do.
}


GenericString::GenericString(StringWrapper* str)
    : strptr_(str)
{
    // Nothing (else) to do.
}


// Support iteration
GenericString::iterator GenericString::begin() const
{
    return strptr_->begin();
}


GenericString::iterator GenericString::end() const
{
    return strptr_->end();
}


// Inserts a character at the end of the chunky string. Also does *not*
// invalidate iterators.
void GenericString::push_back(char c)
{
    strptr_->push_back(c);
}


// Standard string functions: size, append and equality
size_t GenericString::size() const
{
    return strptr_->size();
}


GenericString& GenericString::operator=(const GenericString& rhs)
{
    *strptr_ = *rhs.strptr_;
    return *this;
}


GenericString& GenericString::operator+=(const GenericString& rhs)
{
    *strptr_ += *rhs.strptr_;
    return *this;
}


bool GenericString::operator==(const GenericString& rhs) const
{
    return *strptr_ == *rhs.strptr_;
}


bool GenericString::operator!=(const GenericString& rhs) const
{
    return *strptr_ != *rhs.strptr_;
}


bool GenericString::operator<(const GenericString& rhs) const
{
    return *strptr_ < *rhs.strptr_;
}


// Inserts character c before the character at *i. Returns an iterator
// pointing to the newly inserted character. This function invalidates
// all iterators except for the one it returns.
GenericString::iterator GenericString::insert(iterator i, char c)
{
    return strptr_->insert(i, c);
}


// Erases the character being pointed to by i.  Returns an iterator
// pointing to the character after the erased character. This function
// invalidates all iterators except for the one it returns.
GenericString::iterator GenericString::erase(iterator i)
{
    return strptr_->erase(i);
}


double GenericString::utilization() const
{
    return strptr_->utilization();
}


// Prints out the string to the passed ostream (which is then returned)
// (used to support operator<<, but sometimes useful in its own right)
std::ostream& GenericString::print(std::ostream& out) const
{
    return strptr_->print(out);
}


void GenericString::setFactory(factoryPtr f)
{
    factory = f;
}


void GenericString::loadImplementation(const char* pluginFile)
{
    void* handle = dlopen(pluginFile, RTLD_NOW | RTLD_LOCAL);

    if (handle == nullptr)
        throw std::runtime_error(dlerror());

    void* sym = dlsym(handle, "stringFactory");

    if (sym == nullptr)
        throw std::runtime_error(dlerror());

    setFactory(*(GenericString::factoryPtr*) sym);
}


/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
