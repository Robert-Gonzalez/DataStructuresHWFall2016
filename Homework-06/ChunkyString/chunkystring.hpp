/**
 * \file chunkystring.hpp
 *
 * \authors CS 70 provided code
 *
 * \brief Declares the ChunkyString class.
 */

#ifndef CHUNKYSTRING_HPP_INCLUDED
#define CHUNKYSTRING_HPP_INCLUDED 1

#include <cstddef>
#include <list>
#include <iterator>
#include <iostream>

/**
 * \class ChunkyString
 * \brief Efficiently represents strings where insert and erase are
 *    constant-time operations.
 *
 * \details This class is comparable to a linked-list of characters,
 *   but it is more space-efficient.
 *
 * \remarks
 *   reverse_iterator and const_reverse_iterator aren't
 *   supported. Other than that, we use the STL container type
 *   definitions so that STL functions are compatible with ChunkyString.
 */
class ChunkyString {
    // Forward declaration of private class.
    class Iterator;

public:
    // Standard STL container type definitions
    using value_type      = char;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using iterator = Iterator;
    using const_iterator = Iterator;
    //   - Note that we use the "hack" of just having one kind of iterator
    //     that allows mutation, where we can get this iterator on all
    //     objects even non-const ones.  Programmers should still declare
    //     const_iterator when working on const objects and not modify them
    //     because in the future, we might change things.

    // reverse_iterator and const_reverse_iterator aren't supported

    /**
     * \brief Default constructor
     *
     * \note constant time
     */
    ChunkyString();

    /**
     * \brief Copy constructor
     *
     * \todo Is the synthesized copy constructor okay, or should we
     *       define our own?
     */
    ChunkyString(const ChunkyString& rhs) = default;

    /**
     * \brief Destructor
     *
     * \todo Is the synthesized destructor okay, or should we
     *       define our own?
     */
    ~ChunkyString() = default;

    /**
     * \brief Assignment operator
     *
     * \todo Is the synthesized assignment operator okay, or should we
     *       define our own?
     */
    ChunkyString& operator=(const ChunkyString& rhs) = default;

    /// Return an iterator to the first character in the ChunkyString.
    iterator begin() const;

    /// Return an iterator to "one past the end"
    iterator end() const;

    /**
     * \brief Inserts a character at the end of the ChunkyString.
     *
     * \param c     Character to insert
     *
     * \note Constant time
     */
    void push_back(char c);

    // Standard string functions: size, append, equality, less than
    size_t size() const;    ///< String size \note constant time

    ChunkyString& operator+=(const ChunkyString& rhs); ///< String concatenation

    bool operator==(const ChunkyString& rhs) const;    ///< String equality

    bool operator!=(const ChunkyString& rhs) const;    ///< String inequality

    /// Lexicographical string comparison
    bool operator<(const ChunkyString& rhs) const;

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
     * \warning invalidates all iterators for this string except the
     *          returned iterator
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
    /**
     * \class Iterator
     * \brief STL-style iterator for ChunkyString.
     *
     * \details Synthesized copy constructor, destructor, and assignment
     *          operator are okay.
     *
     *          The five type definitions and the member functions are so that
     *          the iterator works properly with STL functions (e.g., copy).
     *
     *          Since this is a bidirectional_iterator, `operator--`
     *          is provided and meaningful for all iterators except
     *          ChunkyString::begin.
     */
    class Iterator {
    public:
        // Make Iterator STL friendly with these typedefs:
        using value_type        = char;
        using reference         = value_type&;
        using pointer           = value_type*;
        using difference_type   = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        // Operations
        Iterator& operator++();
        Iterator& operator--();
        char& operator*() const;
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;

    private:
        friend class ChunkyString;

        // Private constructor, called by begin() and end() ... ?
        // Private data ...?
    };
};

/**
 * \brief Print operator: displays a ChunkyString on the given stream
 *
 * \param out   the display stream
 * \param text  a ChunkyString to display
 *
 * \returns the display stream
 */
std::ostream& operator<<(std::ostream& out, const ChunkyString& text);

#endif // CHUNKYSTRING_HPP_INCLUDED
