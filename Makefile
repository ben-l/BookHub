all: curses

curses: curses_menu.cpp
	g++ -lncurses curses_menu.cpp -o curses && ./curses
