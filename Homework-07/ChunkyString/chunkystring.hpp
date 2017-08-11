/**
 * \file chunkystring.hpp
 *
 * \authors CS 70 given code, with additions by ... your aliases here ...
 *
 * \brief Declares the ChunkyString class.
 */

#ifndef CHUNKYSTRING_HPP_INCLUDED
#define CHUNKYSTRING_HPP_INCLUDED 1

#include <cstddef>
#include <string>
#include <list>
#include <iterator>
#include <iostream>
#include <type_traits>

/**
 * \class ChunkyString
 * \brief Efficiently represents strings where insert and erase are
 *    constant-time operations.
 *
 * \details This class is comparable to a linked-list of characters,
 *   but more space efficient.
 *
 * \remarks
 *   reverse_iterator and const_reverse_iterator aren't
 *   supported. Other than that, we use the STL container typedefs
 *   such that STL functions are compatible with ChunkyString.
 */
class ChunkyString {
    // Forward declaration of private class.
    template <typename Element, typename ChunklistIterator>
    class Iterator;
    struct Chunk;  

    // Handy typedefs to make making changes to the implementation code easier
    using chunklist_t            = std::list<Chunk>;
    using chunklist_iter_t       = chunklist_t::iterator;
    using chunklist_const_iter_t = chunklist_t::const_iterator;

public:

    // Standard STL container type definitions
    using value_type      = char;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using iterator        = Iterator<value_type, chunklist_iter_t>;
    using const_iterator  = Iterator<const value_type, chunklist_const_iter_t>;

    // reverse_iterator and const_reverse_iterator aren't supported

    /**
     * \brief Default constructor
     *
     * \note constant time
     */
    ChunkyString();
    // TODO: Are the synthesized copy constructor, assignment operator, and
    //       destructor okay, or should we define our own?

    /// Return an iterator to the first character in the ChunkyString.
    iterator begin();
    /// Return an iterator to "one past the end"
    iterator end();

    /// Return a const iterator to the first character in the ChunkyString.
    const_iterator begin() const;
    /// Return a const iterator to "one past the end"
    const_iterator end() const;

    /**
     * \brief Inserts a character at the end of the ChunkyString.
     *
     * \param c     Character to insert
     * 
     * \note constant time
     */
    void push_back(char c);

    // Standard string functions: size, append, equality, less than    
    size_t size() const;    ///< String size \note constant time

    ChunkyString& operator+=(const ChunkyString& rhs); ///< String concatenation

    bool operator==(const ChunkyString& rhs) const;    ///< Equality
    bool operator!=(const ChunkyString& rhs) const;    ///< Inequality
    bool operator<(const ChunkyString& rhs) const;      ///< Comparison

    std::ostream& print(std::ostream& out) const; ///< Printing

    /**
     * \brief Insert a character before the character at i.
     * \details
     *   What makes ChunkyString special is its ability to insert and
     *   erase characters quickly while remaining space efficient.
     *
     * \param i     iterator to specify insertion point
     * \param c     character to insert
     *
     * \returns an iterator pointing to the newly inserted character.
     *
     * \note constant time
     *
     * \warning invalidates all iterators except the returned iterator
     */
    iterator insert(iterator i, char c);

    /**
     * \brief Erase a character at i
     * \details
     *   What makes ChunkyString special is its ability to insert and
     *   erase characters quickly while remaining space efficient.
     *
     * \param i     iterator pointing to the character to erase
     *
     * \returns an iterator pointing to the character after the one
     *   that was deleted.
     *
     * \note constant time
     *
     * \warning invalidates all iterators except the returned iterator
     */
    iterator erase(iterator i);

    /**
     * \brief Average capacity of each chunk, as a percentage
     * \details 
     *   This function computes the fraction of the ChunkyString's character
     *   cells that are in use. It is defined as 
     *
     *   \f[\frac{\mbox{number of characters in the string}}
     *           {\mbox{number of chunks}\times\mbox{CHUNKSIZE}}  \f] 
     *   
     *   For reasonably sized strings (i.e., those with more than one or two 
     *   characters), utilization should never fall to near one character per 
     *   chunk; otherwise the data structure would be wasting too much space.
     *
     *   The utilization for an empty string is undefined (i.e., any value is
     *   acceptable).
     */
    double utilization() const;

private:
    // TODO: Add declaration and documentation for Chunk.

    // TODO: Add private data members for ChunkyString

    /**
     * \class Iterator
     * \brief STL-style iterator for ChunkyString.
     *
     * \details Synthesized copy constructor, destructor, and assignment
     *          operator are okay.
     *
     *          The five typedefs and the member functions are such that
     *          the iterator works properly with STL functions (e.g., copy).
     *
     *          Since this is a bidirectional_iterator, `operator--`
     *          is provided and meaningful for all iterators except
     *          ChunkyString::begin.
     *
     *  \remarks The design of the templated iterator was inspired by these
     *           two sources:
     *  www.drdobbs.com/the-standard-librarian-defining-iterato/184401331
     *  www.sj-vs.net/c-implementing-const_iterator-and-non-const-iterator-without-code-duplication
     */
    template <typename Element, typename ChunklistIterator>
    class Iterator {
    public:
        
        ///< Default constructor
        Iterator();

        ///< Convert a non-const iterator to a const-iterator, if necessary
        Iterator(const Iterator<value_type,chunklist_iter_t>& i);  
   
        // TODO: Do we need more constuctors? A destructor? 
        //       An assignment operator?

        // Make Iterator STL-friendly with these typedefs:
        using value_type = char;
        using reference  = Element&;
        using pointer    = Element*;

        using difference_type   = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using const_reference   = const value_type&;

        // Operations
        Iterator& operator++();
        Iterator& operator--();
        reference operator*() const;
        bool operator==(const Iterator& rhs) const;

    private:
        friend class ChunkyString;
      
        // TODO: Private constructor, called by begin() and end() ... ?
        // TODO: Private data ...?
    };
    
    // these functions help us implement the relational operators (see below)
    template <typename Element, typename ChunklistIterator>
    friend bool operator==(const ChunkyString::Iterator<Element, ChunklistIterator>& lhs,
                           const ChunkyString::Iterator<Element, ChunklistIterator>& rhs);
    
    template <typename Element, typename ChunklistIterator>
    friend bool operator!=(const ChunkyString::Iterator<Element, ChunklistIterator>& lhs,
                           const ChunkyString::Iterator<Element, ChunklistIterator>& rhs);

};


/**
 * \brief Print operator.
 * \remarks
 *   Like the ones above, it's just a wrapper around a member function
 *   that does the actual work, and we don't mind if people know that.
 */

inline std::ostream& operator<<(std::ostream& out, const ChunkyString& text)
{
    return text.print(out);
}

#include "iterator-private.hpp"

#endif // CHUNKYSTRING_HPP_INCLUDED
