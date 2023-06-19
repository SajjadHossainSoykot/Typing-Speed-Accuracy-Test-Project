#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
using namespace std;

const int MAX_WORDS = 100;
const int MAX_WORD_LENGTH = 30;

void generateRandomWords(string words[MAX_WORDS], int testWords) {
    string wordList[] = {"apple", "banana", "cherry", "date", "elderberry", 
    "fig", "grape", "honeydew", "imbu", "jackfruit", "sajjad","the", "quick", "brown", 
    "fox", "jumps", "over", "the", "lazy", "dog", "shithy", "shurovi", "sowrove"};
    srand(time(NULL));
    
    for (int i = 0; i < testWords; i++) {
        int index = rand() % (sizeof(wordList) / sizeof(wordList[0]));
        words[i] = wordList[index];
    }
}

double calculateTimeTaken(chrono::steady_clock::time_point startTime, chrono::steady_clock::time_point endTime) {
    double timeTaken = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
    return timeTaken;
}

int main() {
    int testWords;
    char restart='y';
    do {
        cout << "How many words do you want to type? (10-30)" << endl;
        cin >> testWords;
        if (testWords < 10 || testWords > 30) {
            cout << "Invalid number of words. Please try again." << endl;
            continue;
        }
        
        string words[testWords];
        
        chrono::steady_clock::time_point startTime, endTime;
        int totalCharacters = 0;
        int totalWords = 0;
        int correctWords = 0;
        int correctCharacters = 0;

        generateRandomWords(words, testWords); // Word Generation;

        char any;
        cout << "Press any key, then enter to start your test..." << endl;
        cin >> any;
        cout << "***Type the following words:***\n\n";

        for (int i = 0; i < testWords; i++) {
            cout << words[i] << " ";
        }
        cout << endl;

        // Input and time start
        startTime = chrono::steady_clock::now();

        for (int i = 0; i < testWords; i++) {
            string input;
            cin >> input;
            totalCharacters += input.length();
            int match = 0;
            for (int j = 0; j < words[i].length(); j++) {
                if (tolower(input[j]) == tolower(words[i][j])) {
                    correctCharacters++;
                    match++;
                }
            }
            if (match == words[i].length() && match == input.length())
                correctWords++;
            totalWords++;
        }

        endTime = chrono::steady_clock::now();
        // Input and time end

        // Calculation start
        double timeTaken = calculateTimeTaken(startTime, endTime);

        double typingSpeedChar = (totalCharacters / timeTaken) * 60; // Converts seconds to minute
        double typingSpeedWord = (totalWords / timeTaken) * 60; // Converts seconds to minute

        double accuracyChar = (double)correctCharacters / totalCharacters * 100;
        double accuracyWords = (double)correctWords / totalWords * 100;
        // Calculation end

        // Output
        cout << "\nTyping speed: " << typingSpeedChar << " characters per minute" << endl;
        cout << "Typing speed: " << typingSpeedWord << " words per minute" << endl;
        cout << "Character Accuracy: " << accuracyChar << "%" << endl;
        cout << "Word Accuracy: " << accuracyWords << "%" << endl;
        
        cout << "\nDo you want to restart? (Y/N): ";
        cin >> restart;
    } while (tolower(restart) == 'y');
    
    return 0;
}
