# Makefile for ChunkySting Tester

CXXFLAGS = -g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX      = clang++

TARGETS 	    =	stringtest
STRINGTEST_OBJS     =	string-wrapper.o stringtest.o testing-logger.o
ALL_OBJS	    =   $(STRINGTEST_OBJS)

LIBS        =   -ldl -rdynamic -stdlib=libc++

# ----- Make Rules -----

all:	$(TARGETS)

stringtest:	$(STRINGTEST_OBJS) 
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(STRINGTEST_OBJS) 

clean:
	rm -f $(TARGETS) $(ALL_OBJS)

string-wrapper.o: string-wrapper.cpp string-wrapper.hpp upointer.hpp \
  upointer-private.hpp
	$(CXX) -c $(CXXFLAGS) testing-logger.cpp
stringtest.o: stringtest.cpp string-wrapper.hpp upointer.hpp \
  upointer-private.hpp
	$(CXX) -c $(CXXFLAGS) testing-logger.cpp
testing-logger.o: testing-logger.cpp testing-logger.hpp
	$(CXX) -c $(CXXFLAGS) testing-logger.cpp

