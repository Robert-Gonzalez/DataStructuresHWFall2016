/**
 * \file treeset.hpp
 *
 * \author Hawk and reindeer
 *
 * \brief Provides TreeSet<T>, a set class template, using hash tables
 */

#ifndef TREESET_HPP_INCLUDED
#define TREESET_HPP_INCLUDED 1


// Any header files that are needed to typecheck the class
// declaration should be #included here.
//=====================
#include <forward_list>
#include <cstddef>
#include <climits>
#include <cassert>
#include <random>



// Templated interfaces (e.g., the HashSet class declarations) go here
/**
* \class TreesSet
* \brief Stores items in a recursive data structure, where each node points to two
* other nodes of which can be null
*
* \details This class is templated, so any primitive, stl, or user-defined types
*    can be stored in this tree.
*
*
* \remarks When including the hpp for this class, if you want to
*    template for non-user-defined types, you must include this
*    hpp before you include that type (i.e. strings).
*
*/


template<typename T>
class TreeSet {

public:

    /**
     * \brief Default constructor
     *
     * \note constant time
     */
    TreeSet();

    /**
     * \brief Destructor
     *
     * \note linear time
     */
    ~TreeSet();


    /**
     * \brief Gets the number of nodes in the tree set
     *
     * \return The number of nodes in the tree set
     * \note constant time
     */
    size_t size() const;

     /**
     * \brief Inserts a element into the tree set
     *
     * \details <b> Here's how insert works for our randomized tree: <\b>
     *
     * <br> We are using a randomzied tree. Therefore, our insert function will use probability to
     * simulate if we took all the values of a tree set, including the value to insert,
     * shuffled them randomly, and inserted them one by one.
     *
     * <br> The probability of an insert at the root of the tree is 1/n+1, where n is the
     * number of nodes in the tree before insertion. To apply this probability, we produce a
     * random floating point value between zero and one. If that value is less than 1/n+1, then
     * we fall into inserting at the root node we are observing.__attribute__
     *
     * <br> If the float is greater than 1/n+1, we fall into the probability that the element
     * is inserted into one of the root node's children. The child we insert into is determined by
     * whether the value to insert is greater than or less than the current root node's value.
     *
     * <br> Once we're in that child, we must now recurse so that we can check the probability of
     * inserting at the root of the child tree.
     *
     * \param elem     Templated object to insert
     *
     * \note log(n) time
     */
    void insert(const T& elem);

    /**
     * \brief Sees if an element exists
     *
     * \param elem    The element to check for existence
     *
     * \return True if elem is in the tree set, false otherwise
     * \note log(n) time
     */
    bool exists(const T& elem) const;



    /**
     * \brief writes various statistics about the tree set to the osteam out
     *
     * \param ostream& out
     *
     *
     * \details will print the number of nodes, height, and weighted avg depth
     * of the tree
     *
     */
    std::ostream& showStatistics(std::ostream& out) const;


    /**
     * \brief recursive prints the tree to the ostream out
     *
     * \param ostream& out
     *
     * \return stream that contains the printed tree elements
     * \note O(n) time
     */
    std::ostream& print(std::ostream& out) const;



    /**
     * \brief Gets the height of the tree
     *
     * \return height of the tree
     * \note O(n)
     */
    int height() const;


    /**
     * \brief Gets the weighted avg depth
     *
     * \details the formula for the average weighted depth of a node is
     * \f[ \frac{s_{r} * avgWD(r) + s_{l} * avgWD(l) +
     *     \textup{depth of current node}}{s_{r} + s_{l} + 1}
     * \f]
     * where \f$s_{r}\f$ and \f$s_{l}\f$ are the sizes of the right and
     * left subnodes of the current node respectively, and avgWD() is the
     * average weighted depth function and \f$ \textup{depth of node}\f$ is the depth of
     * the current node.
     *
     *
     * \note O(n)
     */
    float weightedAvgDepth() const;


private:

    /**
    * \struct Node
    * \brief a data structure that represents a node in a tree.
    *
    * \details This class is templated, so any primitive, stl, or user-defined types
    *    can be stored in this tree.
    *
    *
    * \note This struct stores the data associated with the node as well at the size
    *    of the tree which starts at that node. It also stores pointes to the two children
    *    of the node.
    *
    */
    struct Node {

        ///< Convience constructor for a node
        Node(T data, Node* left, Node* right, size_t size);

        ///< Constructor for a node that is a leaf
        Node(T data);

        ~Node();

        T data_;
        Node* left_;
        Node* right_;
        size_t size_;
    };


    /**
     * \brief pointer to the head node of the tree
     */
    Node* head_;

    ///> Variables for generating random floats
    std::uniform_real_distribution<> dis_;
    std::mt19937 gen_;

    /**
     * \brief takes the top node of a tree and rotates the tree to the right
     *
     * \post a tree that has been rotated to the right
     * \note constant time
     */
    void rightRotate(Node*& top);

    /**
     * \brief takes the top node of a tree and rotates the tree to the left
     *
     * \post a tree that has been rotated to the left
     * \note constant time
     */
    void leftRotate(Node*& top);

    ///> A helper function that does exactly what height() does
    ///> but on a specific node.
    int heightHelper(const Node* node) const;

    ///> A helper function that does exactly what exists() does
    ///> but on a specific node.
    bool existsHelper(const T& elem, Node* node) const;

    /**
     * \brief takes a value and the top node of a tree
     *      and it makes the value the new root
     *
     * \post the inserted element is now the root of the tree
     *
     */
    void insertAtRoot(const T& value, Node*& node);

    ///> A helper function that does exactly what insert() does
    ///> but on a specific node.
    void probInsert(const T& value, Node*& node);

    ///> function that sets up seeding for random float gen
    void seed();

    ///> function that generates random foat
    float getRandomFloat();

    ///> A helper function that does exactly what print() does
    ///> but on a specific node.
    std::ostream& printHelper(std::ostream& out, const Node* node) const;

    ///> calculates the average depth of a node by taking in its
    ///> depth within a tree, and following recursive formula
    ///> layed out in weightedAvgDepth
    float weightedAvgDepthHelper(Node* node, int depth) const;







};


#include "treeset-private.hpp"

#endif
