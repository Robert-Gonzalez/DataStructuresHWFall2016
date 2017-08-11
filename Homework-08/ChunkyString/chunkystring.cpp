#include "chunkystring.hpp"
#include "testing-logger.hpp"
#include <cassert>



ChunkyString::ChunkyString() : size_{0}
{
    //Do nothing here
}

ChunkyString::ChunkyString(std::string str)
{
   for(auto iter = str.cbegin(); iter != str.cend(); ++iter){
        push_back(*iter);
    } 
}

ChunkyString::iterator ChunkyString::begin() 
{
    return iterator{0, chunks_.begin()};
}

ChunkyString::iterator ChunkyString::end() 
{
    return iterator{0, chunks_.end()};
}

ChunkyString::const_iterator ChunkyString::begin() const 
{
    return const_iterator{0, chunks_.cbegin()};
}

ChunkyString::const_iterator ChunkyString::end() const 
{
    return const_iterator{0, chunks_.cend()};
}

void ChunkyString::push_back(char c)
{
    if (size_ == 0) {
        addNewChunk(c);
    } else {
        Chunk& lastChunk = chunks_.back();
        //If last chunk is full
        if (lastChunk.length_ == CHUNKSIZE) {
            addNewChunk(c);
        } else {
            //Place c one after last char currently in chunk array
            lastChunk.chars_[lastChunk.length_] = c;
            ++lastChunk.length_;
        }
    }
    ++size_; 
}

size_t ChunkyString::size() const
{
   return size_; 
}

ChunkyString& ChunkyString::operator+=(const ChunkyString& rhs) 
{
    //First copy rhs to handle appending to self
    ChunkyString copy{rhs};
    
    //Push each element of copy onto the back of lhs
    for(const_iterator it = copy.begin(); it != copy.end(); ++it) {
        push_back(*it);
    }
    return *this;
}

bool ChunkyString::operator==(const ChunkyString& rhs) const 
{   
    if (size() != rhs.size()) {
        return false;
    } else {
        const_iterator lhsIt = begin();
        const_iterator rhsIt = rhs.begin();
        //Loop through both ChunkyStrings and make sure all characters are same
        for( ; lhsIt != end(); ++lhsIt, ++rhsIt) {
            if (*lhsIt != *rhsIt) {
                return false;
            }
        }
        return true;
    }
}

bool ChunkyString::operator!=(const ChunkyString& rhs) const 
{
    return !(*this == rhs);
}

bool ChunkyString::operator<(const ChunkyString& rhs) const 
{
    //An STL function to compare sequences of chars between the iterators
    //passed in
    return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
}

std::ostream& ChunkyString::print(std::ostream& out) const 
{
    for(const_iterator it = begin(); it != end(); ++it) {
        out << *it;
    }
    return out;
}


ChunkyString::iterator ChunkyString::redistribute(ChunkyString::iterator i) 
{
    // Maybe try size_t?
    size_t halfway = CHUNKSIZE/2;
    
    //Set up for inserting chunk
    chunklist_iter_t currentChunkIter = i.chunkIt_;
    chunklist_iter_t insertChunkIter = next(currentChunkIter);

    // Actually insert chunk, reset currentIter
    chunklist_iter_t newChunkIter = chunks_.insert(insertChunkIter, Chunk{0});
    currentChunkIter = next(newChunkIter, -1);


    // Copy half the characters in the old chunk into the new chunk array
    // icrement the length of the new chunk array for each char we copy
    // decrement the length of the old chunk array for each char we copy

    // replace this code with copy

    std::copy(currentChunkIter->chars_+halfway, 
        currentChunkIter->chars_+CHUNKSIZE, newChunkIter->chars_);
    currentChunkIter->length_ = halfway;
    newChunkIter->length_ = halfway;

    chunklist_iter_t newChunkPointer;
    
    // Return an iterator that points to the character
    // we we're originally planning to insert at 
    // before we split chunks
    if (i.index_ >= halfway) {
        return iterator{i.index_ - halfway, newChunkIter};

    } else {
        return iterator{i.index_, currentChunkIter};
    }
}

ChunkyString::iterator ChunkyString::add(char c, ChunkyString::iterator i) 
{
    // Use these to prevent info from being lost
    // while inserting into an array
    char temp1;
    char temp2;

    // Loop through length + 1 for the character we insert
    for (size_t newIndex = 0; newIndex < (i.chunkIt_->length_+1); ++newIndex) {
        // If we're at the insertion point, insert the character
        if (newIndex == i.index_) {
            temp1 = i.chunkIt_->chars_[newIndex];
            i.chunkIt_->chars_[newIndex] = c;
        } else if (newIndex > i.index_) {
            // Otherwise shift the character up on poisition in the array
            temp2 = i.chunkIt_->chars_[newIndex];
            i.chunkIt_->chars_[newIndex] = temp1;
            temp1 = temp2;
        }

    }

    ++(i.chunkIt_->length_);
    ++size_;
    return i;
}



ChunkyString::iterator ChunkyString::insert(ChunkyString::iterator i, char c) 
{
    if (size_ == 0 || i == end()) {
        push_back(c);
        iterator endIt = end();
        --endIt;
        return endIt;
    } else if (i.chunkIt_->length_ == CHUNKSIZE) {
        // If inserting overflows the chunk, redistribute the chunks and try
        // again
        iterator newInsertPoint = redistribute(i);
        return insert(newInsertPoint, c);
    } else {
        // Otherwise insert the character into the current chunk's array
        return add(c, i);
    }
}


ChunkyString::iterator ChunkyString::erase(ChunkyString::iterator i) 
{

    if (size_ == 0) {
        return begin();
    } else {
        // Setup for copying characters from the chunk array
        size_t removeIndex = i.index_;
        size_t chunkLength = i.chunkIt_->length_;
        std::list<char> copy;

        // copy all characters that aren't going to be erased
        // into a linked list
        for(size_t j = 0; j < chunkLength; ++j) {
            if (j != removeIndex) {
                copy.push_front(i.chunkIt_->chars_[j]);
            }
        }

        // erase the chunk where we're erasing the character from
        // and lower the chunkystring's size appropriately
        chunklist_iter_t insertChunkit = chunks_.erase(i.chunkIt_);
        size_ -= chunkLength;
        
        // Create a new iterator in the chunkystring 
        // to insert the copied characters at
        iterator newIt = iterator{0, insertChunkit};
       
        // Copy the characters back into the chunkystring
        for (auto charListIt = copy.begin(); charListIt != copy.end(); 
          ++charListIt) {
            newIt = insert(newIt, *charListIt);
        }
        
        // Move the iterator so it points to the character after the one we 
        // deleted
        advance(newIt, removeIndex);

        return newIt;
    }
}

double ChunkyString::utilization() const 
{
    // Cast the size of the string to double to use double division.
    double stringSize = size_;
    return stringSize/(CHUNKSIZE * chunks_.size());
}

// --------------------------------------
// Helper Methods for ChunkyString
// --------------------------------------


void ChunkyString::addNewChunk(char c) 
{
    Chunk newChunk{1};
    newChunk.chars_[0] = c;
    chunks_.push_back(newChunk);
}
// --------------------------------------
// Implementation of ChunkyString::Chunk
// --------------------------------------

ChunkyString::Chunk::Chunk(size_t len) : length_{len}
{
    //Do nothing here.
}

