#ifndef ASSIGN2_FILE_UTIL_H
#define ASSIGN2_FILE_UTIL_H

#include "Game.h"
#include "LinkedList.h"
#include "constants.h"
#include "GameBoard.h"
#include "typedefs.h"
#include "input_util.h"

#include <memory>
#include <fstream>
#include <regex>

class FileUtil {

public:

    // Loads the game details from the given fileName
    // Returns a game instance if read successfully
    // Returns a nullptr if read unsuccessfully
    static std::shared_ptr<Game> loadGame(const string& fileName,
        std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap);

    // Saves the game's data in the file in the given file name
    static void saveGame(const string& fileName, Game* game);

private:
    // Method to get all the data of the player passed.
    static bool
        getPlayerData(const SharedPlayer& player, std::fstream& inputFile);

    // Method to input tiles from the file and store in the linked list passed as params.
    static std::shared_ptr<LinkedList> giveTilesList(string tileList);

    // Method to check if the current tile is in correct format or not.
    static bool isTileCorrect(string tile);

    // Method to check if the player name passed as param is in correct format or not.
    static bool isNameCorrect(const string& name);

    // Method to get all the data of the Game board including board size and the current state.
    static std::shared_ptr<GameBoard> getBoard(std::fstream& inputFile,
        std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap);

    static bool enhancementsCheck(std::fstream& inputFile,
        std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap);
};

#endif // ASSIGN2_FILE_UTIL_H
