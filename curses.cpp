#include <iostream>
#include <ncurses.h>
#include <string>

int main(){
    // initscr routine must be called first
    initscr();

    /* colors already defined in curses.h
     *  COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7

        start_color();
        init_pair(id, fg, bg);
        attron(COLOR_PAIR(id));
    */

    /* attributes for manipulating text
    A_NORMAL        Normal display (no highlight)
    A_STANDOUT      Best highlighting mode of the terminal.
    A_UNDERLINE     Underlining
    A_REVERSE       Reverse video
    A_BLINK         Blinking
    A_DIM           Half bright
    A_BOLD          Extra bright or bold
    A_PROTECT       Protected mode
    A_INVIS         Invisible or blank mode
    A_ALTCHARSET    Alternate character set
    A_CHARTEXT      Bit-mask to extract a character
    COLOR_PAIR(n)   Color-pair number n

    atrron(attribute_to_be_called)
    atrroff(attribute_to_be_called)
	*/

    /* anytime ctrlC keypress program ends
    using raw() instead will not terminate no matter
    what keypress */
    cbreak();

    // noecho does not print keypresses
    noecho();

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

    // hides cursor
    curs_set(0);

    //create window
    int height, width, start_y, start_x;
    height = 10;
    width = 30;
    start_y = start_x = 10;
    WINDOW* win = newwin(height, width, start_y, start_x);
    refresh();
    box(win, 0, 0);

    keypad(win, true);
    std::string choices[3] = {"walk", "talk", "bark"};
    int choice;
    int highlight = 0;

    while(1){
        for(int i = 0; i < 3; i++){
            if(i == highlight){
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i+1, 1, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);
        switch(choice){
            case KEY_UP: case 'k':
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN: case 'j':
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                break;
            default:
                break;
        }
        if (choice == 10 || choice == 'l') break;
    }
    mvwprintw(win, 5, 1, "Your choice was %s", choices[highlight].c_str());
    wrefresh(win);
    getch();


    // draws a box around window
    // box(win, 'x', 'y'); example draws x and y chars as border lines
    // 0, 0 default for lines
    // more specific border variables with wborder
    //wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
    // mvwprintw(window_name, x_coord, y_coord, text")
    //
    /*
    mvwprintw(win, 1, 1, "this is a box");
    wrefresh(win);

    int t = wgetch(win);
    if (t == KEY_UP){
        mvwprintw(win, 2, 1, "you pressed UP!");
        wrefresh(win);
    }
    getch();
    */
    // endwin terminates ncursors and restores terminal settings
    endwin();
    return 0;
}
