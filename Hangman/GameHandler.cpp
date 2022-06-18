#include "GameHandler.h"
#include <iostream>
#include <time.h>       //srand
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using std::cout;

void GameHandler::getRandomWordNum(std::ifstream& file) {
    srand(time(NULL));
    long long int randomNum = rand() % wordsInFile(file) + 1;
    phraseToGuess = findWordInFile(randomNum, file);     //extracts one word from file
}

void GameHandler::display() {
    cout <<std::endl<< std::setw(30) << "" << "HANGMAN\n\n";


    int count = phraseToGuess.size();
    cout << std::setw(25) << "";
    for (int i{}; i < count; i++) {
        if (guessed.find(phraseToGuess.at(i)) == std::string::npos)
            (phraseToGuess.at(i) != '-') ? cout << "_ " : cout << phraseToGuess.at(i) << ' ';
        else
            cout << phraseToGuess.at(i) << ' ';
    }
    cout << '\n';
    cout << std::setw(35) << "" << std::setw(20) << " " << "Lives left: " << lives << std::endl;
    cout << std::setw(35) << "" << std::setw(20) << " " << "Missed letters: \n";
    cout << std::setw(35) << "" << std::setw(20) << " " << misses;
}
void GameHandler::check(bool& ok) {
    int num{};
    for (auto p : phraseToGuess) {
        if (guessed.find(p) != std::string::npos)
            num++;
    }
    if (num == static_cast<int>(phraseToGuess.size()))
    {
        ok = false;
        won = true;
    }
    else
    {
        ok = true;
        won = false;
    }
    if (lives == 0)
        ok = false;

}

bool GameHandler::guessAWord(const std::string& a) {
    if (a == phraseToGuess) {
        guessed = a;
        won = true;
        return false;
    }
    else {
        misses += a;
        misses += ", ";
        lives--;
        return true;
    }
}

void GameHandler::guess(bool& keepPlaying) {
    std::string playerGuess;
    cout << "\n\tEnter a letter or a phrase: ";
    std::cin >> playerGuess;
    for (auto& letter : playerGuess) {
        letter = toupper(letter);
    }
    if (playerGuess.size() != 1)
        keepPlaying = guessAWord(playerGuess);
    else {
        if (phraseToGuess.find(playerGuess) == std::string::npos) {
            misses += playerGuess;
            misses += ", ";
            lives--;
        }
        else {
            guessed += playerGuess;
        }
        check(keepPlaying);
    }
}

void GameHandler::printResults() {
    if (won == false) {
        cout << "\n" << std::setw(20) << "" << "Sorry, you just lost, maybe another time?\n";
        cout << "\n" << std::setw(20) << "" << "Btw, the word you were looking for is " << phraseToGuess << std::endl;
    }
    else
        cout << "\n" << std::setw(20) << "" << "Congratulations, you rule!\n";
}

void GameHandler::prepWord(std::string& wordToPrep) {
    for (auto& p : wordToPrep)
        p = toupper(p);
    while (wordToPrep.back() == ',' || wordToPrep.back() == '.' || wordToPrep.back() == '?' || wordToPrep.back() == '!' || wordToPrep.back() == ':' || wordToPrep.back() == '-' || wordToPrep.back() == ')' || wordToPrep.back() == '"');
        wordToPrep.pop_back();
}

long long int GameHandler::wordsInFile(std::ifstream& file) {
    long long int num{};
    std::string tempWord{};
    while (!file.eof()) {
        file >> tempWord;
        if (tempWord.size() > 5)
            num++;
    }
    file.close();
    return num;
}

std::string GameHandler::findWordInFile(const long long int& randomWordNum, std::ifstream& file) {
    file.open("../dictionary.txt");
    if (!file)
        return "0";
    long long int tempWordNum{};
    std::string tempWord{};
    while (tempWordNum != randomWordNum) {
        file >> tempWord;
        if (tempWord.size() > 5)
            tempWordNum++;
    }
    file.close();
    return tempWord;
}

void GameHandler::getWordToGuess(std::ifstream& file)
{
    getRandomWordNum(file);
    prepWord(phraseToGuess);
}