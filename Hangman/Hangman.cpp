// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//attempt

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cctype>

using std::cout;

long long int word_count(std::ifstream& file) {
    long long int num{};
    std::string a{};
    while (!file.eof()) {
        file >> a;
        if (a.size() > 5)
            num++;
    }
    file.close();
    return num;
}

std::string extract_word(const long long int& num, std::ifstream& file) {
    file.open("../poem.txt");
    if (!file)
        return "0";
    long long int num1{};
    std::string word;
    std::string a{};
    while (num1 != num) {
        file >> a;
        if (a.size() > 5)
            num1++;
    }
    word = a;
    file.close();
    return word;
}

class Hangman {
    std::string phrase;
    size_t lives{ 10 };
    std::string misses{};
    std::string guessed{};
    bool won{ false };

public:

    void get_word(std::ifstream& file) {
        srand(time(NULL));
        long long int num = rand() % word_count(file) + 1;
        phrase = extract_word(num, file);     //extracts one word from file
    }

    void display() {
        cout << std::setw(30) << "" << "HANGMAN\n\n";


        int count = phrase.size();
        cout << std::setw(25) << "";
        for (int i{}; i < count; i++) {
            if (guessed.find(phrase.at(i)) == std::string::npos)
                (phrase.at(i) != '-') ? cout << "_ " : cout << phrase.at(i) << ' ';
            else
                cout << phrase.at(i) << ' ';
        }
        cout << '\n';
        cout << std::setw(35) << "" << std::setw(20) << " " << "Lives left: " << lives << std::endl;
        cout << std::setw(35) << "" << std::setw(20) << " " << "Missed letters: \n";
        cout << std::setw(35) << "" << std::setw(20) << " " << misses;
    }
    void check(bool& ok) {
        int num{};
        for (auto p : phrase) {
            if (guessed.find(p) != std::string::npos)
                num++;
        }
        if (num == static_cast<int>(phrase.size()))
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

    bool word_guess(const std::string& a) {
        if (a == phrase) {
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

    void guess(bool& ok) {
        std::string a;
        cout << "\n\tEnter a letter or a phrase: ";
        std::cin >> a;
        for (auto& z : a) {
            z = toupper(z);
        }
        if (a.size() != 1)
            ok = word_guess(a);
        else {
            if (phrase.find(a) == std::string::npos) {
                misses += a;
                misses += ", ";
                lives--;
            }
            else {
                guessed += a;
            }
            check(ok);
        }
    }

    void congrats() {
        if (won == false) {
            cout << "\n" << std::setw(20) << "" << "Sorry, you just lost, maybe another time?\n";
            cout << "\n" << std::setw(20) << "" << "Btw, the word you were looking for is " << phrase << std::endl;
        }
        else
            cout << "\n" << std::setw(20) << "" << "Congratulations, you rule!\n";
    }

    void correct() {
        for (auto& p : phrase)
            p = toupper(p);
        while (phrase.back() == ',' || phrase.back() == '.' || phrase.back() == '?' || phrase.back() == '!' || phrase.back() == ':' || phrase.back() == '-' || phrase.back() == ')')
            phrase.pop_back();
    }
};

int main() {

    Hangman hangman;
    std::ifstream file{ "../poem.txt", std::ios::in };

    if (!file) {
        std::cerr << "File not open.\n";
        return 0;
    }
    //find a word
    hangman.get_word(file);
    hangman.correct();

    bool ok{ true };

    while (ok) {
        //display
        hangman.display();
        //guess
        hangman.guess(ok);
        Sleep(2000);
        system("cls");
    }

    //again
    hangman.display();

    //print congrats and end
    hangman.congrats();
    Sleep(5000);

    cout << std::endl;
    return 0;
}
