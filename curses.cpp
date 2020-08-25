#include <iostream>
#include <ncurses.h>

int main(){
    // initscr routine must be called first
    initscr();

    /* anytime ctrlC keypress program ends
    using raw() instead will not terminate no matter
    what keypress */
    cbreak();

    // noecho does not print keypresses
    // noecho();

    int x, y;
    x = 10;
    y = 10;
    //moves cursor to location in terminal (line numbers)
    move(x, y);

    printw("Hello world");

    // getch() waits for user input
    int c = getch();

    // combines move and printw into one
    mvprintw(11, 10, "%d", c);

    //create window
    int height, width, start_y, start_x;
    height = 10;
    width = 30;
    start_y = start_x = 10;
    WINDOW* win = newwin(height, width, start_y, start_x);
    refresh();


    // draws a box around window
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "this is a box");
    wrefresh(win);

    getch();
    // endwin terminates ncursors and restores terminal settings
    endwin();
    return 0;
}
