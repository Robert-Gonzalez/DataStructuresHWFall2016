# Question 1

**Answer**: 
THe text file is human readable code that cannot be run on a computer, but the executable is a computer readable file that can be run, 
but we would not be able to understand.
---

# Question 2

**Answer**: 
Compiling happens to the individual files that will make up a larger project, and then linking is the process where if a file needs something
in another file, this is reconciled so that they can all be combined into a single program.
---

# Question 3

**Answer**: 
When the compiler sees to include an hpp file, it uses this file to see what will be used (functions, variables) in the .cpp file, and allocates
space for them.
---

# Question 4

**Answer**: 

* `puppies.hpp`: If you want define the functions declared in a hpp file in your cpp file, you need to #include it. Also, if you want to use a functions 
declared iun an hpp file and defined elsewhere, you can #include that file.
* `puppies.cpp`: Never.
* `puppies.o`: Never.

---

# Quesion 5

**Answer**:
If puppies.cpp does not have a main function, it needs to be compiled into an object file before you compile the main.cpp file and link it to all
related object files.
