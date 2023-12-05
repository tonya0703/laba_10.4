#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void createFile() {
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    ofstream outFile(fileName.c_str());
    outFile.close();
    cout << "File created successfully." << endl;
}

void generateSymbols() {
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    ofstream outFile(fileName.c_str());

    const string symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(static_cast<unsigned int>(time(nullptr)));
    int numLines = rand() % 6 + 5;

    for (int lineNum = 0; lineNum < numLines; ++lineNum) {
        int numNumbers = rand() % 5 + 1;
        int numWords = rand() % 5 + 1;
        for (int i = 0; i < numNumbers; ++i) {
            int num = rand() % 201 - 100;
            outFile << num << " ";
        }
        for (int i = 0; i < numWords; ++i) {
            int wordLength = rand() % 10 + 1;
            for (int j = 0; j < wordLength; ++j) {
                char symbol = symbols[rand() % symbols.length()];
                outFile << symbol;
            }
            outFile << " ";
        }
        outFile << endl;
    }
    outFile.close();
    cout << "Symbols generated in the file." << endl;
}

void countNumbers() {
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    ifstream inFile(fileName.c_str());

    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    int positiveCount = 0, negativeCount = 0, zeroCount = 0;
    string line;

    while (getline(inFile, line)) {
        char* token = strtok(&line[0], " \t");

        while (token != nullptr) {
            char* end;
            int num = strtol(token, &end, 10);

            if (*end == '\0' && (num > 0 || num < 0)) {
                if (num > 0) {
                    positiveCount++;
                }
                else if (num < 0) {
                    negativeCount++;
                }
                else {
                    zeroCount++;
                }
            }

            token = strtok(nullptr, " \t");
        }
    }

    cout << "Positive numbers: " << positiveCount << endl;
    cout << "Negative numbers: " << negativeCount << endl;
    cout << "Zeroes: " << zeroCount << endl;

    inFile.close();
}

bool isNumeric(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

void countWords() {
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    ifstream inFile(fileName.c_str());

    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    int wordCount = 0;
    string word;

    while (inFile >> word) {
        if (!isNumeric(word)) {
            ++wordCount;
        }
    }

    cout << "Total words: " << wordCount << endl;

    inFile.close();
}

int main() {
    int menuItem;

    do {
        cout << endl << endl << endl;
        cout << "Choose an extension: " << endl << endl;
        cout << " [1] - entering file name and creating it" << endl;
        cout << " [2] - generate symbols in file" << endl;
        cout << " [3] - count amount of positive, negative numbers and zeros" << endl;
        cout << " [4] - count amount of words" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: ";
        cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            createFile();
            break;
        case 2:
            generateSymbols();
            break;
        case 3:
            countNumbers();
            break;
        case 4:
            countWords();
            break;
        }
    } while (menuItem != 0);

    return 0;
}