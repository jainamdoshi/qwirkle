#include "QwirkleGameEngine.h"
#include <iostream>
#include <string>

QwirkleGameEngine::~QwirkleGameEngine() = default;

QwirkleGameEngine::QwirkleGameEngine() : QwirkleGameEngine(
    std::chrono::system_clock::now().time_since_epoch().count()) {
}

QwirkleGameEngine::QwirkleGameEngine(unsigned int seed) {
    this->seed = seed;

    intToEnhancementsMap = std::make_shared<std::map<int, string>>();
    enhancementsToStatusMap = std::make_shared<std::map<string, bool>>();

    intToEnhancementsMap->insert(std::pair<int,
        string>(1, MULTI_PLAYERS_MODE));

    enhancementsToStatusMap->insert(std::pair<string,
        bool>(MULTI_PLAYERS_MODE, false));

    intToEnhancementsMap->insert(std::pair<int, string>(2,
        EXPANDABLE_BOARD_MODE));

    enhancementsToStatusMap->insert(std::pair<string,
        bool>(EXPANDABLE_BOARD_MODE, false));

    intToEnhancementsMap->insert(std::pair<int, string>(3,
        COLOUR_MODE));

    enhancementsToStatusMap->insert(std::pair<string,
        bool>(COLOUR_MODE, false));
}

void QwirkleGameEngine::start() {
    int selection = 0;
    std::cout << std::endl;
    std::cout << std::endl;
    do {
        selection = mainMenu();
        if (selection == NEW_GAME) {
            newGame();
        } else if (selection == LOAD_GAME) {
            loadGame();
        } else if (selection == CREDITS) {
            credits();
        } else if (selection == QUIT) {
            quit();
        } else if (selection == ENHANCEMENTS) {
            enhancement();
        }
    } while (selection != QUIT);
}

void QwirkleGameEngine::enhancement() {
    std::cout << "Game Enhancement Configuration" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::map<int, string>::iterator it;

    for (it = intToEnhancementsMap->begin();
        it != intToEnhancementsMap->end(); it++) {

        std::cout << std::endl << it->first << ". " << it->second
            << (enhancementsToStatusMap->at(it->second) ? ": On" : ": Off");
    }
    std::cout << std::endl << std::endl <<
        "Enter a number to toggle the enhancement" << std::endl;

    int selection = input_util::getOptionUserInput
    (intToEnhancementsMap->size());

    enhancementsToStatusMap->at(intToEnhancementsMap->at(selection)) =
        !enhancementsToStatusMap->at(intToEnhancementsMap->at(selection));

    std::cout << std::endl;
}

int QwirkleGameEngine::mainMenu() {
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;

    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << "5. Game Enhancement Config" << std::endl;
    std::cout << std::endl;
    int selection = input_util::getOptionUserInput(5);

    return selection;
}

void QwirkleGameEngine::newGame() {
    std::cout << "Starting a New Game" << std::endl;
    //New Game Functionality - will leave it for those who have do it.
    //Make Players
    std::cout << std::endl;
    std::vector<SharedPlayer> players;

    int playerSize = DEFAULT_MAX_PLAYERS;

    if (enhancementsToStatusMap->at(MULTI_PLAYERS_MODE)) {

        do {
            std::cout << "Enter the number of player (between 3 and 4)"
                << std::endl;
            playerSize = input_util::getIntInput();

            if (playerSize < 3 || playerSize > 4) {
                std::cout << std::endl << "Not valid number of player"
                    << std::endl << std::endl;
            }

        } while (playerSize < 2 || playerSize > 4);
    }

    for (int player = 0; player < playerSize; player++) {
        std::cout << "Enter a name for player " << player + 1
            << " (uppercase characters only)" << std::endl;

        string creatingPlayerInput =
            input_util::getStringInput(std::regex("^[A-Z]+$"));

        SharedPlayer creatingPlayer =
            std::make_shared<Player>(creatingPlayerInput);

        players.push_back(creatingPlayer);
        std::cout << std::endl;
    }
    std::cout << "Let's Play" << std::endl << std::endl;

    //Initialize the game (calling the first constructor of the game)
    std::shared_ptr<Game> newGame =
        std::make_shared<Game>(players, this->enhancementsToStatusMap);
    newGame->initiation(seed);
    newGame->start();
}

void QwirkleGameEngine::loadGame() {
    std::cout << "Enter file path:" << std::endl;
    string fileInput = input_util::getStringInput(std::regex(".+"));
    std::shared_ptr<Game> newGame;
    try {
        newGame = FileUtil::loadGame(fileInput, this->enhancementsToStatusMap);
    }
    catch (const std::exception& ex) {
        // in the future, custom exceptions
        // can be thrown if there's an error while loading
        // for now, we set the newGame to nullptr with no error message
        std::cout << "An error occured while loading: " << ex.what()
            << std::endl;
    }
    if (newGame != nullptr) {
        std::cout << "Qwirkle game successfully loaded" << std::endl;
        newGame->start();
    } else {
        std::cout << "Failed to load game" << std::endl;
    }
}

void QwirkleGameEngine::credits() {
    string team_members[TEAM_SIZE] = { "Jainam Doshi", "Adhiraj Jain",
                                      "Ryan Samarakoon", "Muhib Hasan" };
    string student_id[TEAM_SIZE] = { "s3825891", "s3821245", "s3844545",
                                    "s3850034" };
    string email_address[TEAM_SIZE] = { "s3825891@student.rmit.edu.au",
                                       "s3821245@student.rmit.edu.au",
                                       "s3844545@student.rmit.edu.au",
                                       "s3850034@student.rmit.edu.au" };

    std::cout << "----------------------------------------" << std::endl;

    for (int member = 0; member < TEAM_SIZE; member++) {
        std::cout << "Name: " << team_members[member] << std::endl;
        std::cout << "Student ID: " << student_id[member] << std::endl;
        std::cout << "Email:  " << email_address[member] << std::endl;
        if (member != TEAM_SIZE - 1) {
            std::cout << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::endl;
}

void QwirkleGameEngine::quit() {
    std::cout << "Goodbye" << std::endl;
    exit(0);
}
