
/**
 * \file treeset-private.hpp
 *
 * \author hawk & reindeer, make it rein. 
 *
 * \brief Implements TreeSet<T>, a tree-set class template
 *
 * \remark There is no include-guard for this file, because it is
 *         only #included by treeset.hpp, inside treeset.hpp's
 *         own include guard.
 */



// Includes required for your templated code go here
#include <ostream>
#include <algorithm>
using namespace std;





template <typename T>
TreeSet<T>::~TreeSet() 
{
    // Delete the head_ node and 
    // all other nodes will be deleted
    // recursively
    delete head_;
}


template <typename T>
TreeSet<T>::TreeSet() : head_{nullptr}, dis_{0,1} 
{
    // Set seed up for random generation
    seed();
}


template <typename T>
size_t TreeSet<T>::size() const 
{
    // if the head is null we have an empty treeset, so size is zero
    if (head_ == nullptr) {
        return 0;
    } else {
        // size_ is the number of nodes below head_, so we add 1 to size_
        return 1 + head_->size_;
    }
}


// Assume inserting first element is not a reallocation
template <typename T>
void TreeSet<T>::insert(const T& elem) 
{
    // we use a probabilistic insert function, 
    //as we're implementing a randomized tree
    return probInsert(elem, head_);
   
}


template <typename T>
bool TreeSet<T>::exists(const T& elem) const
{
    return existsHelper(elem, head_);
}


template <typename T>
ostream& TreeSet<T>::showStatistics(ostream& out) const 
{
    out << size() << " :nodes, ";
    out << height() << " :height, ";
    out << weightedAvgDepth() << " :weighted avg depth";
    out << endl;

    return out;
}


template <typename T>
ostream& TreeSet<T>::print(ostream& out) const 
{   
     
    if(head_ == nullptr) {
        out << "-";
    } else {
        printHelper(out, head_);
    }
    out << endl;
    return out;
}


template <typename T>
int TreeSet<T>::height() const 
{
    // height of an empty tree is -1
    // heighHelper returns 0 for an empty node
    return -1 + heightHelper(head_);
}



template <typename T>
float TreeSet<T>::weightedAvgDepth() const 
{
    // Start with depth of 0 since we're starting 
    // from the root
    return weightedAvgDepthHelper(head_, 0);
}


//--------------------------
// HELPER FUNCTIONS HERE
//--------------------------


// Templated code for member functions goes here
template <typename T>
void TreeSet<T>::rightRotate(Node*& top) 
{

    // get approapriate size for peices of the
    // tree to adjust sizes of nodes once rotated
    size_t topSize = top->size_;
    size_t leftSize = 0;
    size_t rightSize = 0;
    size_t lrSize = 0;
    size_t llSize = 0;
    
    // Make sure that we aren't trying to acess data members 
    // of nodes that are null pointers before we get the sizes
    if(top->left_ != nullptr){
        leftSize = top->left_->size_;
        if(top->left_->right_ != nullptr){
            lrSize = top->left_->right_->size_;
        } 
        if(top->left_->left_ != nullptr){
            llSize =top->left_->left_->size_;
        }
    }

    if(top->right_ != nullptr){
        rightSize = top->right_->size_;      
    }
    
    Node* newTop = top->left_;

    // Rearrange the nodes actually rotated the nodes
    top->left_ = newTop->right_;
    newTop->right_ = top;
    top = newTop;


    // Calculate new sizes of rotated nodes
    top->right_->size_ = topSize - leftSize + lrSize;
    top->size_ = llSize + top->right_->size_;
}


template <typename T>
void TreeSet<T>::leftRotate(Node*& top) 
{
    // get approapriate size for peices of the
    // tree to adjust sizes of nodes once rotated
    size_t topSize = top->size_;
    size_t leftSize = 0;
    size_t rightSize = 0;
    size_t rlSize = 0;
    size_t rrSize = 0;
    
    // Make sure that we aren't trying to acess data members 
    // of nodes that are null pointers before we get the sizes
    if(top->left_ != nullptr){
        leftSize = top->left_->size_;
    }

    if(top->right_ != nullptr){
        rightSize = top->right_->size_;
        if(top->right_->left_ != nullptr){
            rlSize = top->right_->left_->size_;
        } 
        if(top->right_->right_ != nullptr){
            rlSize = top->right_->right_->size_;
        }
    }

    // Rearrange the nodes actually rotated the nodes
    Node* newTop = top->right_;

    top->right_ = newTop->left_;
    newTop->left_ = top;
    top = newTop;

    // Calculate new sizes of rotated nodes
    top->left_->size_ = topSize - rightSize + rlSize;
    top->size_ = rrSize + top->left_->size_;
}

template <typename T>
int TreeSet<T>::heightHelper(const Node* node) const 
{
    // If the node is empty return 0
    if (node == nullptr) {
        return 0;
    } else {
        // Otherwise add 1 to the height of the deepest subtree of current node
        return 1 + max(heightHelper(node->left_), heightHelper(node->right_));
    }
}


template <typename T>
bool TreeSet<T>::existsHelper(const T& elem, Node* node) const
{
    // if the treeset is empty, the element doesn't exists
    if (node == nullptr) {
        return false;
    } else if (node->data_ == elem) {
        // return true if the node we're looking at hold the element
        return true;
    } else if (node->data_ < elem) {
        // if the element is greater than the current node's data,
        // check the right subtree
        return existsHelper(elem, node->right_);
    } else {
        // Otherwise, check the left subtree
        return existsHelper(elem, node->left_);
    }
}



template <typename T>
void TreeSet<T>::insertAtRoot(const T& value, Node*& node) 
{
    // if the treeset is empty, construct a new node
    if(node == nullptr) {
        node = new Node(value);
    } else if(value < node->data_) {
        // if the element to insert is less than the current node's data,
        // increase the current node's size and insert into the left child
        ++node->size_;
        insertAtRoot(value, node->left_);
        rightRotate(node);
    } else {
        // otherwise, increase the current node's size 
        // and insert into the left child
        ++node->size_;
        insertAtRoot(value, node->right_);
        leftRotate(node);
    }
}

template <typename T>
void TreeSet<T>::probInsert(const T& value, Node*& node) 
{
    float prob = getRandomFloat();

    // if the treeset is empty, construct new node
    if(node == nullptr) {
        node = new Node(value);
    } else if (prob < (1.0/(node->size_ + 2))) {
        // if our float is within 1/(n+1) where n is the number of nodes
        // in the tree rooted at node, insert at the root of node's tree
        insertAtRoot(value, node);
    }  else if(value < node->data_) {
        // Otherwise if the valeue to insert is lees than current node
        // mark the size and insert to the left
        ++node->size_;
        probInsert(value, node->left_);
    } else {
        // Do the same thing as the last if case but 
        //insert on the right
        ++node->size_;
        probInsert(value, node->right_);
        
    }
}



template <typename T>
ostream& TreeSet<T>::printHelper(ostream& out, const Node* node) const 
{   
    // mark empty nodes with "-" 
    if (node == nullptr) {
        out << "-";
        return out;
    }// else if(node->left_ == nullptr && node->right_ == nullptr) {
    //     out << node->data_;
    //     return out;
    // }
    else {
        // print left tree, then the data of current node, 
        // then print the right tree
        out << "(";
        printHelper(out, node->left_);
        out << ", ";
        out << node->data_;
        out << ", ";
        printHelper(out, node->right_);
        out << ")";
        return out;
    }
}

template <typename T>
float TreeSet<T>::weightedAvgDepthHelper(Node* node, int depthOfNode) const 
{
    // Forward definition of variables to be used in the formula
    size_t rightSize = 0;
    size_t leftSize = 0;
    float rightAvgDepth = 0;
    float leftAvgDepth = 0;

    // Assign the variables appropriately here
    // If a subtree is empty, then it's size remains
    // 0. 
    if (node == nullptr) {
        return 0.0;
    }
    if (node->right_ != nullptr) {
        rightSize = node->right_->size_;
        rightAvgDepth = weightedAvgDepthHelper(node->right_, depthOfNode + 1);
    }
    if (node->left_ != nullptr) {
        leftSize = node->left_->size_;
        leftAvgDepth = weightedAvgDepthHelper(node->left_, depthOfNode + 1);
    }

    // Plug our values into the formula layed out in the docstring
    return (rightSize * rightAvgDepth + leftSize * leftAvgDepth + depthOfNode) /
            (rightSize + leftSize + 1.0);
}

//--------------------------
// End helper functions here
//--------------------------


///> We borrowed this code from the noisy-transmission.cpp file
///> from chunky string.
template <typename T>
void TreeSet<T>::seed() {
    std::random_device rd;
    gen_.seed(rd());
}


///> We borrowed this code from the noisy-transmission.cpp file
///> from chunky string.
template <typename T>
float TreeSet<T>::getRandomFloat() {
    return dis_(gen_);
}


//-----------------------------------
// Implementation of TreeSet<T>::Node
//-----------------------------------

template <typename T>
TreeSet<T>::Node::Node(T data, Node* left, Node* right, size_t size) :
    data_{data}, left_{left}, right_{right}, size_{size}
{
    // Do nothing here
} 

template <typename T>
TreeSet<T>::Node::Node(T data) :
    data_{data}, left_{nullptr}, right_{nullptr}, size_{0}
{
    // Do nothing here
}

template <typename T>
TreeSet<T>::Node::~Node() 
{
    // Recursively destroy the node pointers
    delete left_;
    delete right_;
}

