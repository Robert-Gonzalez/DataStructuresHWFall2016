## ChunkyString Pseudocode

### `ChunkyString::Iterator` Operations

#### `operator++()`

```
   operator++ should return an iterator that point to the next character
   in the ChunkyString. We can do tis by incrementing the value of the 
   current_ attribute since it is an character array. An edge case would
   be if the iterator is at the end of the chunk such as the first chunkin the
   example. we would then go to the next chunk and set the current_ attribute
   to th beginning of that array. operator++ shoud not be called on end(), 
   which is undefined behavior.

   if at end of Chunk :
        go to start of next chunk
        return the new iterator
   else:
        go to next element on current chunk
        return the new iterator

```

#### `operator==(rhs)`

```
    operator== should return true if the iterators point to the same thing in 
    memory

    return current_ == rhs.current_
    
```


### `ChunkyString` Operations

#### `operator+=(rhs)`

```
    operator+= should loop through the rhs chunks_ and put it in the chunks_
    array of our ChunkyString.

    for (chunk : rhs.chunks_) {
        chunks.push_back(chunk);
    } 
    size += rhs.chunks_.size()

```


#### `iterator begin()`

```
    begin() returns an iterator pointing to the front of the ChunkyString
    which is the first element in the first chunk

    if size_ == 0 :
        return ChunkyString::iterator(nullptr)
    else:
        return ChunkyString::iterator(chunks_.front().chars_)

```


#### `iterator end()`

```
    end() returns an iterator pointing to past the end of the ChunkyString
    whcih is a nullptr

    return ChunkyString::iterator(nullptr)
```

#### `push_back(char c)`

```
    push_back() takes a character c and places it at the end of the ChunkyString

    if chunk.back.length_ + 1 > chunkSize/2 || size_ == 0{
        newChars = c;
        newChunk = new Chunk(1, c);
        chunks_ oush_back(newchunk);
        
    } else {
        char[chunk_.back.length_ + 1] = c;
    }
```


#### `insert(char c, iterator i)`

```
    insert() places a character c in the spot where an iterator points to,
    moving the old char forward and returns an iterator that 
    points to the new char c

    if size_ == 0 {
        push_back(c);
    } else if the chunck the iterator points to has length of char array such that len+1 > chunkSize {
        create new chunk;
        create new variable that holds second half of chars of the current chunk;
        remove second half of chars from current chunk;

        construct iterator that points to the index of the char the original iterator pointed to

        insert new chunk into list of chunks

        if the current index member of the iterator is >= len/2 (len is the old len) {
            insert the c into the char array of the new chunk
            return new iterator
        } else {
            insert the c into the char array of the original chunk
            return new iterator
        }

    } else {
        insert the c into the char array of the original chunk
        return new iterator
    }
```


#### `erase(iterator i)`

```
    erase() removes a character in the spot where an iterator points to,
    moving the next char backwards and returns an iterator that 
    points to the char after the removed char
    
    remove the char the iterator points to from the char array

    --length of char array

    create new Iterator

    if size_ == 0 {
        remove chunk from list of chunks;
        create new Iterator point is to big.nextchunk
        return new iterator
    } else {
        create new iterator that points to where original iterator pointed to 
        remove char that the original iterator pointed to 
        return new iterator
    }
```
