# Overview
If you were to read up on `basic_string<char>` (the actual templated type for which `string` is a synonym), you would discover that the C++ standard is quite vague about the asymptotic complexity of various string operations. In particular, the complexity of the `insert` and `erase` operations are unspecified, but the documentation claims that these operations may be linear in the length of the string. This performance may not be sufficient for situations where `insert` and `erase` happen often. For example, a program that allows editing of character input (e.g., `emacs` or `vim`) might need very efficient code for insertion and deletion of characters in the middle of strings. This is not possible if the string is represented using, for example, a primitive array of characters (even if the array is stored on the heap). On the other hand, a doubly-linked list of characters could have as much as 31 bytes of overhead for each 1-byte character, meaning that a machine with 4 GB memory couldn't handle a file larger than 128MB.

Your task over the next few assignments is to develop your own variant of `string` that can efficiently insert and remove characters anywhere in the string. The variant is called `ChunkyString`. This week, you’ll write tests and sketch the implementation for `ChunkyString`. The goal of this assignment is to understand what operations `ChunkyString` should support and how they should work. To do so, you will write **tests** and **pseudocode** for `ChunkyString`. In future assignments, you'll use the tests and pseudocode to help you implement `ChunkyString` in C++.

# Reading

In addition to reading this assignment and reading the doxygen documentation, we strongly recommend the following resources:

* _Code Complete_ chapter 22, for testing. This chapter has a lot of good tips, though not all of them are applicable to this assignment. The checklist on page 532 is an excellent place to start.
* _Code Complete_ chapter 9, for writing good pseudocode. Section 9.3, in particular, describes a good process for writing pseudocode. The book recommends that pseudocode be in exclusively in English, but we are less dogmatic about that particular point, prefering to emphasize *clarity*. Your pseudocode should be clear and detailed enough that someone else in the class could implement your ideas without making any significant design decisions. As with all work, you should strive for elegance and clarity.  Helper "functions" are also appropriate when  writing pseudocode. Remember that pictures can be a great way to plan, and may constitute a large portion of your pseudo"code"!
* The [Homework 6 Hints and Tips](https://github.com/hmc-cs70-fall2016/Materials/wiki/HW6-Hints-Tips) wiki page, where we will collectively accumulate suggestions, fixes, and useful advice for the homework. You should definitely check this before you start the assignment, and may want to check back periodically (especially if you're having trouble with something in the assignment). 
* The [Specifications](Specifications.md) file, which describes the interface and encoding of the `ChunkyString` class. 

# Steps
There are 3 issues to complete for this assignment. We suggest that you budget your time for the issues as follows:

1. Read the specification (5% of your time). 
1. Write tests (50% of your time). 
1. Write pseudocode (45% of your time). 

Though a separate planning component is not strictly required, we **highly** recommend that you carefully plan `ChunkyString` operations on whiteboards or on paper before you start writing pseudocode.

# Grading
Your submission will be graded as follows: 
* 15 points: correctness
* 10 points: completeness
* 6 points: style 
* 6 points: elegance
* 6 points: clarity 
* 7 points: peer review

See the [Grading Guidelines](https://github.com/hmc-cs70-fall2016/Materials/wiki/Grading-Guidelines) wiki page for more information about what we're looking for in each of those categories. 

# A Final Note on the "Chunky String" Concept

Although it has evolved considerably over time, a "chunky string" assignment has existed in CS 70 for many years. It was first conceived by Prof. Kuenning when he taught the class, and it was he who named it "chunky string". This name is CS70-specific. (Dividing a sequence of items into a collection of fixed-size chunks isn't that unusual, but it does not seem to have a widely-used name.) Do not expect anyone who has not taken CS 70 to automatically know what a "chunky string" is.

In particular, if you go to a job interview or grad school, or talk to a visiting CS speaker, and mention your implementation of "chunky strings" (without any further explanation), you'll just get blank or confused looks.

If, on the other hand, you talk about it with a someone who took CS70 seventeen years ago, you'll get an immediate sense of camaraderie. Hopefully you'll be able to say "but mine worked" - perhaps more nicely than that, though!
