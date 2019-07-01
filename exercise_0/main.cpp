
#include <iostream>

#define VOWELS  "aeiou"


bool    is_vowels(char character) {
    char    lower;

    lower = tolower(character);
    for (int i = 0; VOWELS[i] != 0; i++) {
        if (lower == VOWELS[i])
            return true;
    }
    return false;
}

void    count_words(char character, int *vowels, int *consonants, int *others) {
    if (!isalpha(character))
        (*others)++;
    else if (is_vowels(character))
        (*vowels)++;
    else
        (*consonants)++;
}

int     main() {
    std::string program_input;
    int         vowels;
    int         consonants;
    int         others;

    vowels = 0;
    consonants = 0;
    others = 0;
    std::cout << "Enter words (q to quit):" << std::endl;
    while (true) {
        std::cin >> program_input;
        if (!std::cin) {
            perror("Error on reading string");
            return 1;
        }
        if (program_input == "q")
            break;
        count_words(program_input[0], &vowels, &consonants, &others);
    }
    std::cout << vowels << " words beginning with vowels" << std::endl;
    std::cout << consonants << " words beginning with consonants" << std::endl;
    std::cout << others << " others" << std::endl;
    return 0;
}