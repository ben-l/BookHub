#pragma once

#ifdef __linux__
    //linux code goes here
    #define CLEAR_SCREEN system("clear")
#elif _WIN32
    // windows code goes here
	#define CLEAR_SCREEN system("cls")
#else
#error cannot detect operating system in use
#endif

