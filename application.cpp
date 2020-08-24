#include <iostream>
#include <fstream>
#include <string>
#include <curses.h>

void mainMenu();
void drawMainMenu();
void drawWelcome();
void clearScreen();


class loginManager{
	public:
		loginManager(){
				accessGranted = 0;
		}
		void login(){
			std::cout << "Enter Username:\n> ";
	        std::cin.ignore();
			std::getline(std::cin, userNameAttempt);
            username = getFile("users.dat");
			if(userNameAttempt==username){
				std::cout << "Enter Password:\n> ";
				std::getline(std::cin, passwordAttempt);
                password = getFile("paswds.dat");
				if(passwordAttempt==password){
					std::cout << "Login successful" << std::endl;
                    clearScreen();
	                mainMenu();
				}else {
                    std::cout << "Incorrect Password" << std::endl;
                    clearScreen();
                    login();
                }
			}else {
                std::cout << "Incorrect Username" << std::endl;
                login();
            }
		}
        void registerUser(){
            std::cout << "Select a username:\n> ";
            //std::getline(std::cin, username);
            std::cin >> username;
            std::cout << "Select a password:\n> ";
            //std::getline(std::cin, password);
            std::cin >> password;
            std::cout << "Successfully Registered" << std::endl;
            drawWelcome();
        }

        std::string getFile(const char* p_fileName){
            std::string line;
            std::fstream file;
            file.open(p_fileName, std::ios::in);
            if (file.is_open()){
                std::getline(file, line);
            }
            file.close();
            return line;
        }
        void saveFile(std::string p_line,  const char* p_fileName){
            std::ofstream file;
            file.open(p_fileName, std::ios::app);

        }

	private:
		std::string userNameAttempt;
		std::string passwordAttempt;
		std::string username;
		std::string password;
		bool accessGranted;
};

void clearScreen(){
        #ifdef _WIN32
            system("cls");
        #endif
        #ifdef linux
            system("clear");
        #endif
}


void addBook(){
	std::ofstream testFile("./library.txt", std::ios::app);
	std::string bookTitle;
	std::cout << "Enter a book title\n> ";
	std::cin.ignore();
	std::getline(std::cin, bookTitle);
	testFile << bookTitle << std::endl;
	testFile.close();
	std::cout << "Successfully Added Book: " << bookTitle << std::endl;
}


void listBooks(){
	std::string line;
	std::ifstream testFile;
	testFile.open("./library.txt", std::ios::in);

	if (testFile.is_open()){
		std::cout << std::endl << "List of Books" << std::endl;
		std::cout << "-------------" << std::endl;
		while ( std::getline(testFile, line) ){
			std::cout << line << "\n";
		}
		std::cout << "-------------" << std::endl;
		testFile.close();
	}
	else std::cout << "Unable to open file" << std::endl;
}


void deleteBook() {
	std::cout << "deleted Book" << std::endl;
}


void search4Book(){
	std::string bookTitle, line, word;
	std::ifstream testFile;
	testFile.open("./library.txt", std::ios::in);
	std::cout << "Search book\n> ";
	std::getline(std::cin, bookTitle);
	testFile.seekg(0,std::ios::end);
}


void drawWelcome(){
    int choice;
	loginManager loginManagerObj;
    std::cout << "\n1: Register\n2: Login\n3: Exit" << std::endl;
    std::cout << "> ";
    std::cin >> choice;
    if(choice == 1){
	    loginManagerObj.registerUser();
    }else if(choice == 2){
	    loginManager loginManagerObj;
	    loginManagerObj.login();
    }else if(choice == 3){
		std::exit(0);
    }
}


void drawMainMenu(){
	std::cout << "********Library********" << std::endl;
	std::cout << "Enter choice:" << std::endl;
	std::cout << "1) Add New Book" << std::endl;
    std::cout << "2) Search For Book" << std::endl;
	std::cout << "3) Delete Book" << std::endl;
	std::cout << "4) List All Books" << std::endl;
	std::cout << "5) Exit" << std::endl;
	std::cout << "> ";
}

void mainMenu(){
	int choice;
    do {
        drawMainMenu();
	    std::cin >> choice;
        clearScreen();
        switch(choice){
            case 1:
	    	    addBook();
                break;
            case 2:
	    	    search4Book();
                break;
            case 3:
	    	    deleteBook();
                break;
            case 4:
	    	    listBooks();
                break;
        }
    } while (choice != 5);
}


int main() {
    drawWelcome();
	return 0;
}
