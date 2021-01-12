#include <iostream>
#include <string>
#include <sqlite3.h>
#include <sstream>
#include "Core.h"

class Menu {
    public:
        void drawMain() {
            std::cout << "Enter an option:" << std::endl;
            std::cout << "1. List all books" << std::endl;
            std::cout << "2. Add new book" << std::endl;
            std::cout << "3. Delete book" << std::endl;
            std::cout << "4. Find book" << std::endl;
            std::cout << "9. Exit" << std::endl;
        	std::cout << "> ";
        }
        void drawFindOptions() {
            std::cout << "Enter an option:" << std::endl;
            std::cout << "1. Search by Title" << std::endl;
            std::cout << "2. Search by Author" << std::endl;
            std::cout << "3. Search by ISBN" << std::endl;
            std::cout << "4. Search by ID" << std::endl;
            std::cout << "9. Back" << std::endl;
        	std::cout << "> ";
        }
};

class DBLite:Menu {
    // Pointer to SQLite connection
    sqlite3* db;

    char *zErrMsg = 0;

    // Save the connection result
    int exit = 0;

    // Create a callback function
    static int callback(void *NotUsed, int argc, char **argv, char **azColName){
        for(int i = 0; i < argc; i++) {
            // Show column name, value, and newline
            std::cout << azColName[i] << ": " << argv[i] << std::endl;
        }
        // Insert a newline
        std::cout << std::endl;
    
        // Return successful
        return 0;
    }

    // check for errors
    int checkDBErrors(sqlite3 *db){
        std::cout << "DB Open Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        // return an error aka return True if there is an error
        // return(0) similar to exit(0)
        return(1);

    }

    public:
        DBLite(){
            exit = sqlite3_open("example.db", &db);
            // Test if there was an error opening database
            if (exit) {
                checkDBErrors(db);
            } else {
                std::cout << "Opened Database Successfully!" << std::endl;
            }
        }

        void createTable(){
            std::string sql = "CREATE TABLE IF NOT EXISTS BOOKS("
                "ID INTEGER PRIMARY KEY, "
                "TITLE TEXT NOT NULL, "
                "AUTHOR TEXT NOT NULL, "
                "YEAR_PUB INTEGER, "
                "ISBN INTEGER);";
            exit = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
            // Close the connection
            if (exit) {
                checkDBErrors(db);
            } else {
                std::cout << "Created Table Successfully!" << std::endl;
            }
        }

        void queryTable(std::string sql){
            //std::string sql = "SELECT * FROM BOOKS;";
            exit = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
            if (exit) {
                checkDBErrors(db);
            }
        }

		void addbookDetails(){
            std::string u_Title, u_Author;
            int u_YearPub, u_Isbn;

            std::cout << "---------- ADD BOOK----------" << std::endl;
            std::cout << "Enter book title:" << std::endl;
	        std::cin.ignore();
            std::getline(std::cin, u_Title);

            std::cout << "Enter author:" << std::endl;
            std::getline(std::cin, u_Author);

            std::cout << "Enter year published:" << std::endl;
            std::cin >> u_YearPub;
            //std::getline(std::cin, u_YearPub);

            std::cout << "Enter ISBN:" << std::endl;
            std::cin >> u_Isbn;
            //std::getline(std::cin, u_Isbn);

            std::stringstream streamYearPub, streamIsbn;
            std::string sYearPub, sIsbn;

            streamYearPub << u_YearPub;
            streamYearPub >> sYearPub;

            streamIsbn << u_Isbn;
            streamIsbn >> sIsbn;

            // send the user input into the insert data func
            insertData(&u_Title, &u_Author, &sYearPub, &sIsbn);
        }

        void insertData(std::string *Title, std::string *Author, 
                        std::string *YearPub, std::string *Isbn)
            {
            
            
            std::string sql = "INSERT INTO BOOKS ("
                              "TITLE, AUTHOR, YEAR_PUB, ISBN)" 
                              "VALUES ( '" + *Title + "', '" + *Author + \
                              "', '" + *YearPub + "', '" + *Isbn + "');";
            exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
            if (exit) {
                checkDBErrors(db);
            } else {
                std::cout << "Successfully inserted data into Books" \
                    << std::endl;
            }
        }

        void deleteRowById(){
            int u_RowId; 
            std::cout << "---------- DELETE ----------" << std::endl;
            std::cout << "Enter ID: "; 
            std::cin >> u_RowId;

            std::string sRowId;
            std::stringstream streamRowId;
            streamRowId << u_RowId;
            streamRowId >> sRowId;

            std::string sql = "DELETE FROM BOOKS WHERE ID = " + sRowId + ";";
            exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
            if (exit) {
                checkDBErrors(db);
            } else {
                std::cout << "Successfully deleted data from Books" \
                    << std::endl;
            }
            
        }

        void findBook(){
            Menu::drawFindOptions();
        }
        void closeDB(){
            sqlite3_close(db);
        }
};



int main()
{
    DBLite sql3;
    Menu menu;
    sql3.createTable();
    int choice;
    do 
    {
        menu.drawMain();
        std::cin >> choice;
		CLEAR_SCREEN;
        switch(choice)
        {
            // list all
            case 1:
                sql3.queryTable("SELECT * FROM books");
                break;
            // add
            case 2:
                //sql3.insertData("What", "Who", "1992", "9732");
                sql3.addbookDetails();
                break;
            // delete
            case 3:
                sql3.deleteRowById();
                break;
            case 4:
                sql3.findBook();
                break;
        }
    } while (choice != 9);

    sql3.closeDB();

   return (0);
}
