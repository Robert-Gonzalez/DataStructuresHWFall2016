CXX = clang++

CXX_FLAGS = -g -std=c++11 -pedantic -Wall -Wextra

generateSegfault: generateSegfault.cpp helloSayer.o
	$(CXX) generateSegfault.cpp -o generateSegfault $(CXX_FLAGS) helloSayer.o

helloSayer.o: helloSayer.cpp helloSayer.hpp
	$(CXX) helloSayer.cpp -o helloSayer.o -c $(CXX_FLAGS)

clean:
	rm -rf *.o generateSegfault
