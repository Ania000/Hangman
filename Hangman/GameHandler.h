#pragma once
#include<string>
class GameHandler
{
private:
    std::string phraseToGuess;
    size_t lives{ 10 };
    std::string misses{};
    std::string guessed{};
    bool won{ false };

public:
    void getWordToGuess(std::ifstream& file);
    void getRandomWordNum(std::ifstream& file);
    void display();
    void guess(bool& keepPlaying);
    void printResults();
    void prepWord(std::string& wordToPrep);

private:
    void check(bool& ok);
    bool guessAWord(const std::string& a);
    std::string findWordInFile(const long long int& num, std::ifstream& file);
    long long int wordsInFile(std::ifstream& file);

};

