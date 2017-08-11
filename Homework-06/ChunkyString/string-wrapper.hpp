/*
 *  string-wrapper.hpp
 *
 *  CS 70 support code.
 *
 *  This code is support code for the ChunkyString assignment.  You do not
 *  need to modify this file, nor understand it.  The coding style in this
 *  file may not meet the usual standards for code in CS 70.
 *
 *  (c) 2007-2009 Melissa O'Neill.
 */

#ifndef STRING_WRAPPER_HPP_INCLUDED
#define STRING_WRAPPER_HPP_INCLUDED 1

#include <cstddef>
#include <string>
#include <list>
#include <iterator>
#include <iostream>
#include <typeinfo>

#include "upointer.hpp"


/*
 * IteratorWrapper and StringWrapper are abstract classes that specify an
 * interface.  Typical usage is to use IteratorWrapper* and StringWrapper*
 * referring to heap objects.
 *
 * The interface provided by these classes is *not* (quite) the ChunkyString
 * interface.
 */
class IteratorWrapper {
    // Default copy constructor and assignment operator are okay.

public:
    // Make Iterator STL friendly with these typedefs:
    typedef char                            value_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;
    typedef ptrdiff_t                       difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    virtual ~IteratorWrapper() {
        // Nothing (else) to do.
    }

    // Operations
    virtual IteratorWrapper* heapcopy() = 0;
    virtual void      operator=(const IteratorWrapper& rhs) = 0;
    virtual void      operator++()      = 0;
    virtual void      operator--()      = 0;
    virtual reference operator*() const = 0;
    virtual bool      operator==(const IteratorWrapper& rhs) const = 0;
    virtual bool      operator!=(const IteratorWrapper& rhs) const = 0;
};

class GenericIterator;
class StringWrapper {
public:
    // Standard STL container typedefs
    typedef char                value_type;
    typedef size_t              size_type;
    typedef int                 difference_type;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef GenericIterator     iterator;
    typedef GenericIterator     const_iterator;
    // reverse_iterator and const_reverse_iterator aren't supported

    // Constructors
    // Default copy constructor and assignment operator are okay.
    virtual ~StringWrapper() { }

    virtual StringWrapper* heapcopy() = 0;

    // Support iteration
    virtual iterator begin() const = 0;
    virtual iterator end()   const = 0;

    // Inserts a character at the end of the chunky string.
    virtual void push_back(char c) = 0;

    // Standard string functions: size, append and equality
    virtual size_t size() const = 0;
    virtual void operator=(const StringWrapper& rhs)  = 0;
    virtual void operator+=(const StringWrapper& rhs) = 0;
    virtual bool operator==(const StringWrapper& rhs) const = 0;
    virtual bool operator!=(const StringWrapper& rhs) const = 0;
    virtual bool operator<(const StringWrapper& rhs)  const = 0;

    // Inserts character c before the character at i. Returns an iterator
    // pointing to the newly inserted character.
    virtual iterator insert(iterator i, char c) = 0;

    // Erases the character being pointed to by i.  Returns an iterator
    // pointing to the character after the erased character.
    virtual iterator erase(iterator i) = 0;

    // How much of each chunk is used
    virtual double   utilization() const = 0;

    // Prints out the string to the passed ostream (which is then returned)
    // (used to support operator<<, but sometimes useful in its own right)
    virtual std::ostream& print(std::ostream& out) const = 0;
};


/*
 * GenericIterator and GenericString wrap IteratorWrapper and StringWrapper
 * pointers respectively, allowing them to appear as normal (non-pointer)
 * objects.
 */

class GenericIterator {
public:
    // Make Iterator STL friendly with these typedefs:
    typedef char                            value_type;
    typedef value_type&                     reference;
    typedef value_type*                     pointer;
    typedef ptrdiff_t                       difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    GenericIterator();
    GenericIterator(IteratorWrapper* iter);
    // Default copy constructor, destructor, and assignment operator are fine.

    // Operations
    GenericIterator& operator=(const GenericIterator& rhs);
    GenericIterator& operator++();
    GenericIterator& operator--();
    reference operator*() const;
    pointer   operator->() const;
    bool  operator==(const GenericIterator& rhs) const;
    bool  operator!=(const GenericIterator& rhs) const;

    IteratorWrapper* underlyingIterator() const;

private:
    UnsharedPointer<IteratorWrapper> iter_;

    friend class GenericString;
};


class GenericString {
public:
    // Standard STL container typedefs
    typedef char                value_type;
    typedef size_t              size_type;
    typedef int                 difference_type;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef GenericIterator     iterator;
    typedef GenericIterator     const_iterator;
    // reverse_iterator and const_reverse_iterator aren't supported

    // Constructors
    GenericString();

    // Default copy constructor and assignment operator are okay.
    // Default destructor is okay.

    // Support iteration
    iterator begin() const;
    iterator end() const;

    // Inserts a character at the end of the chunky string.
    void push_back(char c);

    // Standard string functions: size, append and equality
    size_t size() const;
    GenericString& operator=(const GenericString& rhs);
    GenericString& operator+=(const GenericString& rhs);
    bool operator==(const GenericString& rhs) const;
    bool operator!=(const GenericString& rhs) const;
    bool operator<(const GenericString& rhs)  const;

    // Inserts character c before the character at i. Returns an iterator
    // pointing to the newly inserted character.
    iterator insert(iterator i, char c);

    // Erases the character being pointed to by i.  Returns an iterator
    // pointing to the character after the erased character.
    iterator erase(iterator i);

    // How much of each chunk is used
    double   utilization() const;

    // Prints out the string to the passed ostream (which is then returned)
    // (used to support operator<<, but sometimes useful in its own right)
    std::ostream& print(std::ostream& out) const;

    typedef StringWrapper* (*factoryPtr)();

    static void setFactory(factoryPtr f);
    static void loadImplementation(const char* pluginFile);

private:
    static factoryPtr factory;
    GenericString(StringWrapper* str);

    UnsharedPointer<StringWrapper> strptr_;
};


inline std::ostream& operator<<(std::ostream& out, const GenericString& text)
{
    return text.print(out);
}

#endif // STRING_WRAPPER_HPP_INCLUDED


/* (Junk to make emacs use Stroustrup-style indentation)
 * Local Variables:
 * c-file-style: "stroustrup"
 * End:
 */
