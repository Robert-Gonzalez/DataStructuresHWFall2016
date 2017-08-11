/*********************************************************************
 * ChunkyString::Iterator class.
 *********************************************************************
 *
 * Implementation for the templated ChunkyString iterator
 *
 */

template <typename Element, typename ChunklistIterator>
void ChunkyString::Iterator<Element, ChunklistIterator>::swap(Iterator<Element, ChunklistIterator>& rhs) 
{
    using std::swap;
    swap(index_, rhs.index_);
    swap(chunkIt_, rhs.chunkIt_);
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>::Iterator()
{
    //Do nothing in here
}

//Parameterized construtor for ChunkyString iterator
template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>::Iterator(size_t ind, ChunklistIterator chunkListIt)
    : index_{ind}, chunkIt_{chunkListIt}
{
    //Do nothing in here
}

//Will copy construct iterators OR will convert from non-const to const iterator types
template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>::Iterator(
            const Iterator<value_type,chunklist_iter_t>& i)
            : index_{i.index_}, chunkIt_{i.chunkIt_}
{
    // Do nothing in here
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>& ChunkyString::Iterator<Element, ChunklistIterator>::operator=(
        const Iterator<Element, ChunklistIterator>& rhs)
{
    // Assignment is implemented idiomatically for C++, using "the swap trick"
    Iterator<Element, ChunklistIterator> copy = rhs;
    swap(copy);

    return *this;
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>& ChunkyString::Iterator<Element, ChunklistIterator>::operator++()
{
    //If not pointing to last char in the chunk array
    if (index_ < (chunkIt_->length_)-1) {
        ++index_;
    } else {
        //Move to next chunk
        ++chunkIt_;
        index_ = 0;
    }

    return *this;
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>& ChunkyString::Iterator<Element, ChunklistIterator>::operator--()
{
    //If not pointing to first char in the chunk array
    if (index_ > 0) {
        --index_;
    } else {
        //Move to previous chunk, set index to last char in chunk
        --chunkIt_;
        index_ = (chunkIt_->length_)-1;
    }

    return *this;
}


template <typename Element, typename ChunklistIterator>
typename ChunkyString::Iterator<Element, ChunklistIterator>::reference 
    ChunkyString::Iterator<Element, ChunklistIterator>::operator*() const
{
    return chunkIt_->chars_[index_];
}

template <typename Element, typename ChunklistIterator>
bool  ChunkyString::Iterator<Element, ChunklistIterator>::operator==(
        const Iterator<Element, ChunklistIterator>& rhs) const
{
    //ChunkyString iterators equal if they point to same chunk AND same
    // index in that chunk's array
    return ((this->chunkIt_ == rhs.chunkIt_) && (this->index_ == rhs.index_));
}

template <typename Element, typename ChunklistIterator>
bool  ChunkyString::Iterator<Element, ChunklistIterator>::operator!=(
        const Iterator<Element, ChunklistIterator>& rhs) const
{
    return !(*this == rhs);
}

