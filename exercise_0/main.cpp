
#include <iostream>
#include <fstream>

constexpr char VOWELS[] = "aeiou";


bool    is_vowels(char character) {
    auto    lower = std::tolower(character);
    for (int i = 0; VOWELS[i] != 0; ++i) {
        if (lower == VOWELS[i])
            return true;
    }
    return false;
}

void    count_words(char character, int &vowels, int &consonants, int &others) {
    if (!isalpha(character))
        others++;
    else if (is_vowels(character))
        vowels++;
    else
        consonants++;
}

int     check_words(std::istream &read_file, const std::string &stop = {}) {
    std::string program_input;
    int         vowels;
    int         consonants;
    int         others;

    vowels = 0;
    consonants = 0;
    others = 0;
    while (read_file >> program_input) {
        if (!stop.empty() && program_input == stop)
            break;
        count_words(program_input[0], vowels, consonants, others);
    }
    if (read_file.bad()) {
        perror("Error on reading string");
        return EXIT_FAILURE;
    }
    std::cout << vowels << " words beginning with vowels" << std::endl;
    std::cout << consonants << " words beginning with consonants" << std::endl;
    std::cout << others << " others" << std::endl;
    return EXIT_SUCCESS;
}

int     read_from_file(const std::string &file_name) {
    std::ifstream   input_file(file_name);

    if (!input_file) {
        perror("Error on reading file");
        return EXIT_FAILURE;
    }
    check_words(input_file);
    return EXIT_SUCCESS;
}

int     main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Enter words (q to quit):" << std::endl;
        return check_words(std::cin, "q");
    }
    else if (argc == 2) {
        return read_from_file(argv[1]);
    }
    std::cout << "Usage: " << argv[0] << " [FILE_NAME]" << std::endl;
    return EXIT_SUCCESS;
}
