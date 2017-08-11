# Analysis of code using `IntList`

## `exercise01.cpp`
* **Cost Metric**: Calls to `new`
* **Precise Formula**: sum 1, i = 0 to (N/2 - 1) 
* **Closed Form**: N/2
* **Approximation**: f(n) = n/2
* **Asymptotic Complexity**: O(N)
* **Justification**: Calls to `new` (in the form for calls to push_back()) only occur 
in the for loop that iterates from zero to n-1, 
but iterates with steps of 2. Thus, we only call `new` n/2 times. When we do an asymtotic 
analysis, we ignore constansts and only worry about the largest degree of N, which yields O(N).
* **Ideal Fuzziness**: If you wanted to know what would happen if you
  squared the input, the right level of precision would be the function approximation, because 
  function approximation can help us analyze runtimes for different inputs, where asymtotic complexity 
  could help us find difference in runtime due to fundamental differences in the function.
* **Benchmarking**: 
N = 5, time = 0.004
N = 10, time = 0.004
N = 100, time = 0.003


## `exercise02.cpp`
* **Cost Metric**: Calls to `new`
* **Precise Formula**: sum (sum 1, j = 0 to N-1), i = 0 to N-1
* **Closed Form**: N^2
* **Approximation**: f(n) = n^2
* **Asymptotic Complexity**: O(N^2)
* **Justification**: Calls to `new` (in the form for calls to push_back()) only occur 
in the nested for loop that iterates from zero to N-1, 0 to N-1 times, 
and iterates with steps of 1. Thus, we only call `new` N^2 times.
* **Benchmarking**: 
N = 5, time = 0.004
N = 10, time = 0.003
N = 100, time = 0.014


## `exercise03.cpp`
* **Cost Metric**: Calls to `new`
* **Precise Formula**: (sum 1, i = 0 to N-1) + (sum 1, j = 0 to N-1)
* **Closed Form**: 2N
* **Approximation**: f(n) = 2n
* **Asymptotic Complexity**: O(N)
* **Justification**: Calls to `new` (in the form for calls to push_back()) only occur 
in the two separate for loops that each iterate from zero to n-1, 
and iterates with steps of 1. Thus, we only call `new` 2N times. When we do an asymtotic 
analysis, we ignore constansts and only worry about the largest degree of N, which yields O(N).
* **Ideal Fuzziness**: If you wanted to compare this algorithm to
  another one that completed the same task, the right level of
  precision would be aymptotic complexity because big-O is used to compare large-scale 
  runtimes between different algorithms, where approximations can compare runtimes of different 
  sized inputs.
* **Benchmarking**: 
N = 5, time = 0.003
N = 10, time = 0.003
N = 100, time = 0.003


## `exercise04.cpp`
* **Cost Metric**: Calls to `new`
* **Precise Formula**: sum (sum (sum 1, k = 0 to j*i-1), j = 1 to i-1), i=2 to N
* **Closed Form**: 1/24 (3N^4-2N^3-3N^2+2N-24)
* **Asymptotic Complexity**: N^4
* **Justification**: 

Calls to `new` (in the form for calls to push_back()) only occur within our 
triply-nested for loop. The number of iterations in the innermost loop corresponds 
to that total calls to `new`:

      -The innermost loop will iterate from 0 to ji - 1.
      
      -The middle loop will iterate from 1 to i-1. We don't count when j=0, 
      because i*j will be zero in the next loop, so `new` will never be called.

      -The outer loop will iterate from 2 to N-1. We don't count i = 1, because 
      when i = 0, j can only be 0 before ending the middle for loops, which means 
      i*j can only be zero in the innermost loop, so `new` will never be called.

Thus, we only iterate 1/24 (3N^4-2N^3-3N^2+2N-24) times (solved using Wolfram.)


When we do an asymtotic analysis, we ignore constansts in terms and only 
worry about the largest degree of N, which yields O(N^4).

* **Ideal Fuzziness**: If you wanted to compare this algorithm to
  another one that completed the same task, the right level of
  precision would be aymptotic complexity because big-O is used to compare large-scale 
  runtimes between different algorithms, where approximations can compare runtimes of different 
  sized inputs.
* **Benchmarking**: 
N = 5, time = 0.004
N = 10, time = 0.004
N = 100, time = 11.667


## `exercise05.cpp`
* **Explanation of Code**: 
* **Cost Metric**: Additions
* **Assumptions**: For this problem, you can assume that we get random
  numbers "for free" and they don't count in the complexity
  computation (although, in reality, we know that nothing can
  *actually* be free!)
* **Precise Formula**: 
(sum 1, i = 0 to N-1) + 1 + (sum 1, i = 0 to Array_Size-1) + N + (sum 1, i = 0 to Array_Size)
  = N + 1 + Array_Size + N + Array_Size - 1
* **Closed Form**: 4N + 3Array_Size
* **Approximation**: f(n) = 4n
* **Asymptotic Complexity**: O(N)
* **Justification**: Additions occur in 5 different places:
    1) The random-generation of IntList elements via for loop. The initialization 
    of the count array via for loop: The for loop iterate (adds to i) starting 
    from zero to N-1, and iterates with steps of 1. Thus, we add N times.

    2) The definition of Array_Size is a single addition to biggestNumberAllowed.
    Thus, we add 1 time.

    3) The initialization of the count array via for loop: For each iteration we 
    add to i and re-compute count+Array_Size for the loop comparison (2 additions 
    per iteration). The for loops iterates starting from count to when i is equal 
    to count + Array_Size - 1, and iterates with steps of 1, which is the same as 
    starting at zero and iterating to Array_Size - 1. Thus, we add 2*Array_Size times.

    4) The counting of different ints in the IntList: For each iteration we 
    add to i and add to the count array value for the integer i (2 additions 
    per iteration). The for loops iterates starting from myList.begin() to 
    when i is equal to myList.end(), and iterates with steps of 1, which 
    is the same as starting at zero and iterating to the size of the IntList-1.
    From part 1), where we make our IntList elements, we know the size of 
    IntList is N. Thus, we add 2N times.

    5) Printing the elements of myList in order: For this nested for loop, 
    the number of times j runs for each separate i is dependent on what 
    numbers were randomly placed in the IntList we formed in part 1). What 
    we do know is the total amount of j additions will be equal to the number 
    of elements in the IntList, myList.size_ = N. The total number of 
    additions in the outer loop is simply biggestNumberAllowed - 1 = Array_Size - 2 
    because the only addtions occur when i is increased for each iteration from 
    zero to biggestNumberAllowed - 1. Thus, we add N + Array_Size - 1 times.

    Adding the 5 summations together, we get 4N + 3Array_Size.

Our approximation only needs to focus on terms with N in it, because comparing
f(n) for different n values is independent of constants in f(n). Therefore, 
f(n) = 4N, as Array_Size is constant. 

When we do an asymtotic analysis, we ignore constansts in terms and only 
worry about the largest degree of N, which yields O(N).

* **Ideal Fuzziness**: If you wanted to compare this algorithm to
  other sorting algorithms, the right level of precision would be
  function approximation because it allows us to compare worst-case 
  and best-case scenarios of inputs for different sorting algorithms.
* **Benchmarking**: 
N = 5, time = 0.003
N = 10, time = 0.004
N = 100, time = 0.003
