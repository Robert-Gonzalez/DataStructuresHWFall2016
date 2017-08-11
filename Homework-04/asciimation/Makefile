#
# Makefile for CS 70 Asciimation Assignment

our-movie: our-movie.o asciimation.o sprite.o ncurses-helper.o
	clang++ -o our-movie our-movie.o asciimation.o sprite.o ncurses-helper.o -lncurses

ncurses-helper.o: ncurses-helper.cpp ncurses-helper.hpp
	clang++ -c -g -std=c++11 -pedantic -Wall -Wextra ncurses-helper.cpp

asciimation.o: asciimation.cpp asciimation.hpp
	clang++ -c -g -std=c++11 -pedantic -Wall -Wextra asciimation.cpp

sprite.o: sprite.cpp sprite.hpp
	clang++ -c -g -std=c++11 -pedantic -Wall -Wextra sprite.cpp

our-movie.o: our-movie.cpp 
	clang++ -c -g -std=c++11 -pedantic -Wall -Wextra our-movie.cpp

clean: 
	rm *.o our-movie