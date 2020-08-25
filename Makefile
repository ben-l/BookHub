all: curses

curses: curses.cpp
	g++ -lncurses curses.cpp -o curses
