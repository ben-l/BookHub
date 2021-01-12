#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <string>

void addBook(WINDOW* win);
std::string getstring(WINDOW* win, int x, int y)
{
    std::string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // moves cursor to x, y coords
    wmove(win, x, y);

    // this reads from buffer after <ENTER>, not "raw"
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }

    // restore your cbreak / echo settings here

    return input;
}

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
    std::string choices[] = {"Add Book", "talk", "bark"};
    int choice;
    int highlight = 0;

    while(1){
        for(int i = 0; i < sizeof(choices)/sizeof(choices[0]); i++){
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
        // if enter is pressed or choice is l break
        if (choice == 10 || choice == 'l') break;
    }
    //mvwprintw(win, 5, 1, "Your choice was %s", choices[highlight].c_str());
    if (choices[highlight] == "Add Book"){
        addBook(win);
    }
    wrefresh(win);

    // endwin terminates ncursors and restores terminal settings
    getch();
    endwin();
    return 0;
}
void addBook(WINDOW* win){
	std::ofstream testFile("./library.txt", std::ios::app);
	std::string bookTitle;
	//std::cout << "Enter a book title\n> ";
    mvwprintw(win, 5, 1, "Enter a book title:");
	bookTitle = getstring(win, 6, 1);
    wrefresh(win);
	testFile << bookTitle << std::endl;
	testFile.close();
//	std::cout << "Successfully Added Book: " << bookTitle << std::endl;
    mvwprintw(win, 7, 1, "Successfully Added Book: %s", bookTitle.c_str());
}
