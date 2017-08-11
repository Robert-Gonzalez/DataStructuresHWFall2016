# The `ChunkyString` Class
This section contains the specification for the `ChunkyString` class. We will provide the interface and the encoding (i.e., private data members); it will ultimately be up to you to
use the private data members to implement the interface. A good understanding of the specification is required for this assignment, in order to write good tests and pseudocode.

For any data structure, we can describe the _space overhead_ needed to store information in the structure. The space overhead is any space in memory that's used by the data structure but is not directly used to hold data. For example, in your IntList encodings, the `next`  pointer of each Element was be part of the space overhead, since it wasn't directly part of storing the `int`s. In addition to comparing two data structures based on the *time* they require for different operations, we can compare them based on the amount of extra *space* that they require. The `ChunkyString` representation is a compromise between storing the string as an array or vector (which makes inserting characters in the middle expensive) and storing it as a linked list of single characters (which requires a lot of space overhead). 

## Encoding

`ChunkyString` represents a string (i.e., a sequence of characters) as a linked list of fixed-size "chunks". Each chunk is a static array of CHUNKSIZE characters. A chunk may be empty (in
which case it contains no valid characters), or full (in which case it contains `CHUNKSIZE` valid characters), or anywhere in between.

The following image is a _conceptual_ picture of a `ChunkyString` with its list of chunks; in memory, the chunks aren't inside the
list object, but stored separatedly on the heap (in a doubly-linked list of nodes).

![chunky_string](https://cloud.githubusercontent.com/assets/8798975/10673520/2a93c814-78ab-11e5-89b2-f76a09a0abda.png)

Part of the challenge of implementing `ChunkyString` is maintaining a good _utilization_, i.e., a good ratio of used space to unused space. If a `ChunkyString` object has only been used by *adding* characters to it, it should always be in a state where at least 1/2 of the space in the character arrays of its `Chunks` is being used to hold characters in the string. If it has been used for any combination of *adding* and *removing* characters, at least 1/4 of the space should be used to hold characters in the string. Naturally, exceptions are made for very small strings; depending on the number of characters in each `Chunk`, it might not be possible to have utilization of 1/2 for a single-character string! We've provided a `checkUtilization` helper function in the `stringtest.cpp` file that handles the edge cases of small `ChunkyString`s for you. 

In C++, `ChunkyString` is a class that defines two private data members. The first data member is an integer that holds the number of characters in the entire string. The second data member is of type
`list<Chunk>`, where `list` is the templated linked list data structure from the C++ standard library (specified in the `<list>` header file), and `Chunk` is a private class or struct.   In this assignment, you won't write C++ code for the private data members, but you'll need to know their structure so that you can write pseudocode for the data structure's operations.

If you choose to have "smart" `Chunk` objects that have their own member functions, you might use the following:

```
class Chunk {
...
private:
  size_t length_;
  char chars_[CHUNKSIZE];
};
```

If you want your chunks to be "dumb data" (i.e, no member functions) managed by the `ChunkString` class, you might use the following:

```
struct Chunk {
  size_t length_;
  char chars_[CHUNKSIZE];
};
```

## Interface

To the outside world, your class will just be a restricted version of the C++ `string` class. (C++'s specification for the `string` type includes a myriad of
useful member functions---thankfully, you won't be implementing all of them.)  With one exception (the `utilization` operation) a user should not be able to deduce from the public interface that you are using chunks.

The following operations are required:
* A default constructor
* Operations that provide information about `ChunkyString`s
  * `size`
  * `operator==`
  * `operator!=`
  * `operator<`
  * `utilization`
* Operations that modify `ChunkyString`s
  * `push_back`
  * `insert`
  * `erase`
  * `operator+=`
* A _nonmember_ function `operator<<` for displaying a `ChunkyString` on an output stream.
* A type, `iterator`, whose interface is described below
* Operations that provide iterators
  * `begin`
  * `end`
* An iterator class with that supports at least the following operations: 
  * equality and inequality tests
  * preincrement and predecrement
  * dereferencing
  * the necessary type definitions to make the iterator compatible with the C++ standard library (We have provided these type definitions; they should not be changed.)

We have provided a header file (`chunkystring.hpp`) that declares all these operations. The doxygen documentation contains much more information about these operations, including some required constraints on their behavior. To learn more about the operations (and to practice generating and reading doxygen), you should **stop now**, generate the doxygen documentation, and read the documentation for the `ChunkyString` and `ChunkyString::Iterator` classes.
