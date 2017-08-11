#
# Makefile for CS 70 Spell Checking Assignment
# 

###############################################################################
# MAKEFILE VARIABLES
###############################################################################

# CXX is the name of the compiler we are using (clang++)

CXX = clang++


# CXXFLAGS are the flags we will be passing each compile

CXXFLAGS       = -g -std=c++11 -Wall -Wextra -pedantic 

# TARGETS is the list of all programs created when we do "make all"
#   (and which should be deleted when we do "make clean")

TARGETS = treeset-string-test myspell

###############################################################################
# "PHONY" (BUT USEFUL) MAKEFILE TARGETS
###############################################################################


# "make all" brings all programs up-to-date (recursively)
#     and then runs no commands.

all: $(TARGETS)

# "make clean" brings nothing up to date, but always
#      runs commands to delete all created files

clean:
	rm -f $(TARGETS)
	rm -rf *.o

# "make test" brings all the testing programs up-to-date (recursively)
#       and then runs them.
# You should probably use a more realistic number of buckets than 10
#       for stringhash-test, but the exact number is up to you.

test: treeset-string-test
	./treeset-string-test

doxygen: doxygen.config
	doxygen doxygen.config

###############################################################################
# CREATING PROGRAMS
###############################################################################


treeset-string-test: treeset-string-test.o testing-logger.o
	$(CXX) $(CXXFLAGS) -o treeset-string-test $^

# "make myspell" brings all the relevant .o files up-to-date and links them.
myspell: myspell.o spellchecker.o
	$(CXX) $(CXXFLAGS) -o myspell $^

###############################################################################
# GENERATING OBJECT FILES
###############################################################################

# The .o files depend on the corresponding .cpp file and the .hpp
#      files that C++ code includes.
#      In each case, the command to generate the .o file uses
#      our C++ compiler to compile the .cpp file, with the -c flag.

testing-logger.o: testing-logger.cpp testing-logger.hpp
	$(CXX) $(CXXFLAGS) -c testing-logger.cpp

treeset-string-test.o: treeset-string-test.cpp treeset.hpp treeset-private.hpp
	$(CXX) $(CXXFLAGS) -c treeset-string-test.cpp

myspell.o : myspell.cpp
	$(CXX) $(CXXFLAGS) -c myspell.cpp

spellchecker.o: spellchecker.cpp spellchecker.hpp treeset.hpp treeset-private.hpp
	$(CXX) $(CXXFLAGS) -c spellchecker.cpp

# All targets containing "hashset-string-test"
# we copied from provided code 





