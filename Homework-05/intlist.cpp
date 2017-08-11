/*
 * \file intlist.cpp
 * \authors hmc-cs-dog and hmc-cs-reindeer
 * \brief Implemenation of IntList and its private classes.
*/

#include "intlist.hpp"
#include "testing-logger.hpp"

using namespace std;

IntList::IntList() 
    : back_{nullptr},
      front_{nullptr},
      size_{0}
{
    affirm(consistent() && empty());
}

IntList::~IntList()
{
    // delete the front and back because they are on the heap

    Element* current = front_;
    while (current != nullptr){
        delete current;
        current = current->next_;
    }
    front_  =  nullptr;
    back_ = nullptr;

    //test to make sure destructor worked
    affirm(front_ == nullptr);
    affirm(back_ == nullptr);

}


IntList::IntList(const IntList& orig)
    :   back_{nullptr},
        front_{nullptr},
        size_{0}
{
       
    //make iterators for each lists to iterate through lists
    //  IntList::iterator rhsIterator = rhs.begin();
     for (IntList::iterator i = orig.begin(); i != orig.end(); ++i) {
         push_back(*i);
    }

    affirm(consistent());
}

void IntList::swap(IntList& rhs)
{
    // This is the canonical way to swap arbitrary types; this incantation
    // will call std::swap unless we're swapping a class that provides its
    // own swap function (like we do), in which case that swap is called.
    // Here we end up calling std::swap since the swapped parts are primitives.

    using std::swap;

    swap(back_, rhs.back_);
    swap(front_, rhs.front_);
    swap(size_, rhs.size_);
    affirm(consistent());
}

void swap(IntList& lhs, IntList& rhs) { lhs.swap(rhs); }

IntList& IntList::operator=(const IntList& rhs)
{
    // Assignment is implemented idiomatically for C++, using "the swap trick"
    IntList copy = rhs;
    swap(copy);

    affirm(consistent());
    return *this;
}


size_t IntList::size() const
{ 
    return size_;
}


bool IntList::empty() const
{
    return size_ == 0;
}



bool IntList::operator==(const IntList& rhs) const
{
    //if the size of the two lists aren't
    //equal, the lists certainly aren't equal'
    if (size_ != rhs.size_) {
        return false;
    } else {

        //make iterators for each lists to iterate through lists
        IntList::iterator rhsIterator = rhs.begin();

        for (IntList::iterator i = begin(); i != end(); ++i) {
            if (*i != *rhsIterator) {
                return false;
            }
            ++rhsIterator;
        }
        return true;
    }
}

bool IntList::operator!=(const IntList& rhs) const
{
    // Idiomatic code: leverage == to implement !=
    return !operator==(rhs);
}



void IntList::push_front(int pushee)
{
    // Create a new element with the right value
    front_ = new Element(pushee, front_);

    // If list is originally empty set back equal to front
    if (size_ == 0){
        back_ = front_;
    }

    ++size_;

    affirm(consistent() && !empty());

}



int IntList::pop_front()
{   
    // Store the value to be returned
    int firstVal = front_->value_;

    // Having one element in the list is a special case since back_ and
    // front_ point to the same element
    if (size_ == 1) {
        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        --size_;
    } else {
        // Store the next element
        Element* temp = front_->next_;
        delete front_;
        // Set the new front of the list to be what was after the first element
        front_ = temp;
        --size_;
    }
    
    affirm(consistent());

    return firstVal;
}


void IntList::push_back(int pushee)
{

    // When size is zero, there is no existing back element, so we establish it
    if (size_ == 0) {
        back_ = new Element(pushee, nullptr);
        front_ = back_;
    } else {
        //set next spot to have the new back element and reassign back
        back_->next_ = new Element(pushee, nullptr);
        back_ = back_->next_;
    }
    
    ++size_;

    affirm(consistent());
}


void IntList::insert_after(iterator where, int value)
{
    if(empty()) affirm(false);

    // this inserts a new element after the element that the iterator points to
    where.current_->next_ = new Element(value, where.current_->next_);

    ++size_;
    
    affirm(consistent() && !empty());
}


IntList::iterator IntList::begin() const
{
    return IntList::Iterator(front_);
}



IntList::iterator IntList::end() const
{
    return IntList::Iterator(nullptr);
}


bool IntList::consistent() const
{
    return ((front_ == nullptr) && (back_ == nullptr) && (size_ == 0))
           || ((front_ == back_) && (size_ == 1))
           || ((front_ != back_) && (size_ > 1));
}

// --------------------------------------
// Implementation of IntList::Element
// --------------------------------------

IntList::Element::Element(int value, Element* next) : value_{value}, next_{next}
{
    // Nothing else to do.
}

// --------------------------------------
// Implementation of IntList::Iterator
// --------------------------------------

IntList::Iterator::Iterator(Element* current) : current_{current}
{
    // Nothing else to do.
}

IntList::Iterator& IntList::Iterator::operator++()
{
    // increment the iterator
    current_ = current_->next_;
    return *this;
}



int& IntList::Iterator::operator*() const
{
    affirm(current_ != nullptr);
    return current_->value_;
}


bool IntList::Iterator::operator==(const Iterator& rhs) const
{
    // checks if the values of the elements they point to is the same
    return current_ == rhs.current_;
}
bool IntList::Iterator::operator!=(const Iterator& rhs) const
{
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}

