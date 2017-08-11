#
# Makefile for CS 70 IntList Assignment
# 
# As usual, you can build this software by typing
#
#     make
#

# ----- Make Variables -----

CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic
CXX = clang++

EXERCISES = exercise01 exercise02 exercise03 exercise04 exercise05
TARGETS = intlist-test $(EXERCISES)

TEST_OBJECTS = intlist-test.o intlist.o testing-logger.o
EXERCISE_OBJECTS = intlist.o testing-logger.o

# ----- Make Rules -----

all: $(TARGETS)

exercise01: exercise01.cpp $(EXERCISE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o exercise01 exercise01.cpp $(EXERCISE_OBJECTS)

exercise02: exercise02.cpp $(EXERCISE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o exercise02 exercise02.cpp $(EXERCISE_OBJECTS)

exercise03: exercise03.cpp $(EXERCISE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o exercise03 exercise03.cpp $(EXERCISE_OBJECTS)

exercise04: exercise04.cpp $(EXERCISE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o exercise04 exercise04.cpp $(EXERCISE_OBJECTS)

exercise05: exercise05.cpp $(EXERCISE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o exercise05 exercise05.cpp $(EXERCISE_OBJECTS)

intlist-test: $(TEST_OBJECTS)
	$(CXX) -o intlist-test $(TEST_OBJECTS)

intlist.o: intlist.cpp intlist.hpp testing-logger.hpp
	$(CXX) -c $(CXXFLAGS) intlist.cpp

testing-logger.o: testing-logger.cpp testing-logger.hpp
	$(CXX) -c $(CXXFLAGS) testing-logger.cpp

intlist-test.o: intlist-test.cpp intlist.hpp testing-logger.hpp
	$(CXX) -c $(CXXFLAGS) intlist-test.cpp

clean:
	rm -rf $(TARGETS) *.o documentation

doxygen:
	doxygen doxygen.config
