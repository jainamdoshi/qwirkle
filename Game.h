#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Player.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "constants.h"
#include "Tile.h"

#include <vector>
#include <string>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>


class Game {
public:
    // Constructor to create a new Game
    explicit Game(const std::vector<SharedPlayer>& players,
        std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap);

    // Constructor to create a loaded Game
    Game(const SharedVector<SharedPlayer>& players, SharedPlayer currentPlayer,
        std::shared_ptr<GameBoard> board, std::shared_ptr<LinkedList> tileBag,
        std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap);

    // Destructor
    ~Game();

    /**
     * Whether the game has finished and there's a winner
     */
    bool isFinished();

    // toString method
    string toString(bool isColour, bool isSaving);

    //initializing the game method
    void initiation(unsigned int seed);

    /**
     * Blocking method which starts the game and doesn't return until the game
     *  is finished.
     */
    void start();

private:
    // Class Variables
    std::shared_ptr<GameBoard> board;
    std::shared_ptr<LinkedList> tileBag;
    SharedVector<SharedPlayer> players;
    SharedPlayer currentPlayer;
    std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap;

    // Helper methods

    /**
     * Moves the game to the next player turn
     * @return the next player
     */
    SharedPlayer nextPlayerTurn();

    //Initialize when creating a new game
    void shuffleTileBag(std::vector<SharedTile> tileVector, unsigned int seed);

    void setUpPlayerHands();

    std::vector<SharedTile> createTileBag();

    void saveCommand(std::stringstream& args);

    void placeCommand(std::stringstream& args);

    void replaceCommand(std::stringstream& args);

    void printPlayerScores();

    void printWinningPlayer();
};

#endif // ASSIGN2_GAME_H