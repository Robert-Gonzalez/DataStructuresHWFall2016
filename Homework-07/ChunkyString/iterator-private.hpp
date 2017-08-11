/*********************************************************************
 * ChunkyString::Iterator class.
 *********************************************************************
 *
 * Implementation for the templated ChunkyString iterator
 *
 */

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>::Iterator()
{
    throw std::logic_error("Not yet implemented");
}


template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>::Iterator(
            const Iterator<value_type,chunklist_iter_t>& i)
{
    throw std::logic_error("Not yet implemented");
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>& ChunkyString::Iterator<Element, ChunklistIterator>::operator++()
{
    throw std::logic_error("Not yet implemented");
}

template <typename Element, typename ChunklistIterator>
ChunkyString::Iterator<Element, ChunklistIterator>& ChunkyString::Iterator<Element, ChunklistIterator>::operator--()
{
    throw std::logic_error("Not yet implemented");
}


template <typename Element, typename ChunklistIterator>
typename ChunkyString::Iterator<Element, ChunklistIterator>::reference 
    ChunkyString::Iterator<Element, ChunklistIterator>::operator*() const
{
    throw std::logic_error("Not yet implemented");
}

template <typename Element, typename ChunklistIterator>
bool  ChunkyString::Iterator<Element, ChunklistIterator>::operator==(
        const Iterator<Element, ChunklistIterator>& rhs) const
{
    throw std::logic_error("Not yet implemented");
}
