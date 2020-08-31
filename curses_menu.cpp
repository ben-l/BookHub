#include <iostream>
#include <ncurses.h>
#include <string>


int main(){
    initscr();
    // ctrl-c to quit
    noecho();
    cbreak();
    // hide cursor
    curs_set(0);

    //create window
    int height, width, start_y, start_x;
    height = 10;
    width = 30;
    start_y = start_x = 10;
    WINDOW* win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

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

    // endwin terminates ncursors and restores terminal settings
    endwin();
    return 0;
}
