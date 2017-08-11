# Overview

One of the most widely used spelling checkers in unix-like environments is`ispell`, written by our own Professor Kuenning. Is Professor Kuenning's fame and glory deserved? Just how hard *is* it to write a spelling checker?  It's time to find out!

In this assignment, you'll write a program almost entirely from scratch. The components of the program include:

* A hash function `myhash`. You won't need to write this from scratch, but your choice should be based on empirical data.
* A `HashSet<T>` class that can store arbitrary elements of type `T` in a hash table.
* A program `myspell` that uses your hash table to implement a spell-checker.

As with any piece of software, you'll need to test and document as you go.
 
# Reading
In addition to reading this assignment, we strongly recommend the following resources:

* The wiki page on [reading input](https://github.com/hmc-cs70-fall2016/Materials/wiki/ReadingInputHowTo)
* The wiki page on [processing command line arguments](https://github.com/hmc-cs70-fall2016/Materials/wiki/CommandLineArgumentHowTo)


# Grading
Your submission will be graded as follows: 
* 15 points: correctness
* 10 points: completeness
* 6 points: style 
* 6 points: elegance
* 6 points: clarity 
* 7 points: peer review

See the [Grading Guidelines](https://github.com/hmc-cs70-fall2016/Materials/wiki/Grading-Guidelines) wiki page for more information about what we're looking for in each of those categories. 

# Footnote

Professor Kuenning's `ispell` implementation is based on the first `ispell` implementation, written by Pace Willisson, and is more properly referred to as *International Ispell*.   
