// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     //printing to console
#include <stdlib.h>     //system(cls)
#include <fstream>      //file ops
#include <string>       //string ops
#include <windows.h>    //sleep
#include "GameHandler.h"

using std::cout;

int main() {

    GameHandler game;
    std::ifstream file{ "../dictionary.txt", std::ios::in };

    if (!file) {
        std::cerr << "File not open.\n";
        return 0;
    }
    game.getWordToGuess(file);
    
    bool keepPlaying{ true };
    while (keepPlaying) {

        game.display();
        game.guess(keepPlaying);
        Sleep(2000);
        system("cls");
    }

    //display for the final time
    game.display();
    game.printResults();
    Sleep(5000);

    cout << std::endl;
    return 0;
}
