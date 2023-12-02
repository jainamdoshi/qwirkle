#include "input_util.h"


int input_util::getIntInput() {
    string in = getStringInput(std::regex("^\\d+$"),
                               "Given input is not a number");
    int ret = 0;
    auto stream = std::stringstream(in);
    stream >> ret;
    return ret;
}

int input_util::getOptionUserInput(int max) {
    int input = -1;
    bool valid = false;
    while (!valid) {
        input = getIntInput();
        if (input < 1 || input > max) {
            std::cout << "Input must be between 1 and " << max << std::endl;
        } else {
            valid = true;
        }
    }
    return input;
}

string input_util::getStringInput(const std::regex &regex,
                                  const string &error) {
    string input;
    bool valid = false;
    while (!valid) {
        std::cout << "> " << std::flush;
        input_util::getline(std::cin, input);
        if (!std::cin.eof()) {
            // check if input matches given regex
            bool found = std::regex_search(input, regex);
            if (!found) {
                std::cout << error << std::endl;
            } else {
                valid = true;
            }
        } else {
            // if input read is eof, terminate
            QwirkleGameEngine::quit();
        }

    }
    return input;
}


void input_util::getline(std::basic_istream<char> &stream, string &input) {
    std::getline(stream, input);
    // if on windows,
    // lines might have CR (\r) at the end, so remove if its there...
    if (!input.empty() && input[input.size() - 1] == '\r') {
        input.erase(input.size() - 1);
    }
}
