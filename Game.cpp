#include "Game.h"
#include "input_util.h"
#include "FileUtil.h"
#include "QwirkleGameEngine.h"

#include <utility>
#include <iostream>
#include <sstream>

Game::Game(const std::vector<SharedPlayer>& players,
    std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap) {
    this->players = std::make_shared<std::vector<SharedPlayer>>(players);
    this->board = std::make_shared<GameBoard>(enhancementsToStatusMap);
    this->tileBag = std::make_shared<LinkedList>();
    this->currentPlayer = players.at(0);
    this->enhancementsToStatusMap = enhancementsToStatusMap;
}

Game::~Game() = default;

Game::Game(const SharedVector<SharedPlayer> &players,
    SharedPlayer currentPlayer, std::shared_ptr<GameBoard> board,
    std::shared_ptr<LinkedList> tileBag,
    std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap) {

    this->players = players;
    this->currentPlayer = std::move(currentPlayer);
    this->board = std::move(board);
    this->tileBag = std::move(tileBag);
    this->enhancementsToStatusMap = enhancementsToStatusMap;
}

void Game::initiation(unsigned int seed) {
    std::vector<SharedTile> tileVector = createTileBag();
    shuffleTileBag(tileVector, seed);
    setUpPlayerHands();
}

void Game::start() {
    while (!isFinished()) {
        auto lastPlayer = currentPlayer;
        std::cout << std::endl << currentPlayer->getName()
            << ", it's your turn" << std::endl;
        printPlayerScores();
        board->displayBoard();
        std::cout << "Your hand is" << std::endl;
        auto hand = currentPlayer->getHand();
        if (hand->isEmpty()) {
            std::cout << "<no items>" << std::endl;
        } else {
            std::map<string, bool>::iterator it =
                enhancementsToStatusMap->find(COLOUR_MODE);
            std::cout << hand->toString(it != enhancementsToStatusMap->end()
                ? it->second : false, false) << std::endl;
        }
        // While player hasn't finished their turn
        while (lastPlayer == currentPlayer) {
            string input = input_util::getStringInput(
                std::regex(COMMAND_REGEX));
            std::stringstream args = std::stringstream(input);
            string command;
            args >> command;
            if (command == "save") {
                saveCommand(args);
            } else if (command == "place") {
                placeCommand(args);

            } else if (command == "replace") {
                replaceCommand(args);
            }
        }
    }
    std::cout << "Game over" << std::endl;
    printPlayerScores();
    printWinningPlayer();
    std::cout << std::endl;
    QwirkleGameEngine::quit();

}

void Game::printWinningPlayer() {
    SharedPlayer maxPlayer = nullptr;
    for (SharedPlayer& player : *players) {
        if (maxPlayer == nullptr ||
            player->getScore() > maxPlayer->getScore()) {
            maxPlayer = player;
        }
    }
    std::vector<SharedPlayer> tiedPlayers;
    for (SharedPlayer& player : *players) {
        if (player->getScore() == maxPlayer->getScore() &&
            player != maxPlayer) {
            tiedPlayers.push_back(player);
        }
    }
    if (tiedPlayers.empty()) {
        std::cout << "Player " << maxPlayer->getName() << " won!" << std::endl;
    } else {
        tiedPlayers.push_back(maxPlayer);
        std::cout << "Players ";
        for (unsigned int i = 0; i < tiedPlayers.size(); i++) {
            SharedPlayer tiedPlayer = tiedPlayers.at(i);
            std::cout << tiedPlayer->getName();
            if (i != tiedPlayers.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " tied with a score of " << maxPlayer->getScore() << "!"
            << std::endl;
    }
}

void Game::printPlayerScores() {
    for (SharedPlayer& player : *players) {
        std::cout << "Score for " + player->getName() << ": "
            << player->getScore() << std::endl;
    }
}

string Game::toString(bool isColour, bool isSaving) {
    string results = "";
    for (std::map<string, bool>::iterator it =
        enhancementsToStatusMap->begin();
        it != enhancementsToStatusMap->end(); it++) {

        if (it->second) {
            results += it->first + "\n";
        }
    }

    std::map<string, bool>::iterator it =
        enhancementsToStatusMap->find(MULTI_PLAYERS_MODE);

    if (it != enhancementsToStatusMap->end() && it->second) {
        std::stringstream ss;
        string size;
        ss << (int)players->size();
        ss >> size;
        results += size + "\n";

    }

    // Getting a string format of all the players in the game
    for (SharedPlayer& player : *players) {
        results += player->toString(isColour, isSaving);
    }

    // Getting a string format of the board, tileBag and the current player's name
    results += this->board->toString();
    results += this->tileBag->toString(false, true);
    results += this->currentPlayer->getName();

    return results;
}

std::vector<SharedTile> Game::createTileBag() {
    std::vector<SharedTile> tileVector;

    //First we would have to create the tile bag
    for (const Colour& colour : constants::COLOURS) {
        for (const Shape& shape : constants::SHAPES) {
            //Create two tiles that are the same since there are 72 tiles (2 of each) in the tile bag.
            SharedTile currentTile = std::make_shared<Tile>(colour, shape);
            SharedTile currentTile2 = std::make_shared<Tile>(colour, shape);
            tileVector.push_back(currentTile);
            tileVector.push_back(currentTile2);
        }
    }
    return tileVector;
}

void
Game::shuffleTileBag(std::vector<SharedTile> tileVector, unsigned int seed) {
    //Proceed to shuffle these this tile vector with the seed generated from the system clock
    std::shuffle(std::begin(tileVector), std::end(tileVector),
        std::default_random_engine(seed));

    //convert vector into tileBag Linked List
    for (auto& tile : tileVector) {
        tileBag->addTile(tile);
    }

}

void Game::setUpPlayerHands() {
    //Go through every player
    for (SharedPlayer& player : *players) {
        //pick out 6 tiles for the player
        for (int tiles = 0; tiles < HAND_SIZE; tiles++) {
            //select the tile
            SharedTile tilePicked = tileBag->deleteTile(tileBag->getTile(
                0)); //will perhaps change into a shared pointer
        //add the tile to the persons hand.
            player->addTile(tilePicked);
        }
    }
}

bool Game::isFinished() {
    // if tilebag is empty and at least one player has no tiles left.
    bool isAnyPlayerHandEmpty = false;
    for (SharedPlayer& player : *players) {
        if (player->getHand()->isEmpty()) {
            isAnyPlayerHandEmpty = true;
        }
    }
    bool ret = false;
    if (tileBag->isEmpty() && isAnyPlayerHandEmpty) {
        ret = true;
    }
    return ret;
}


SharedPlayer Game::nextPlayerTurn() {
    SharedPlayer newCurrentPlayer = nullptr;
    for (unsigned int i = 0; i < players->size() &&
        newCurrentPlayer == nullptr; i++) {
        auto player = players->at(i);
        if (player == currentPlayer) {
            currentPlayer = players->at((i + 1) % players->size());
            newCurrentPlayer = currentPlayer;
        }
    }
    return newCurrentPlayer;
}

void Game::replaceCommand(std::stringstream & args) {
    string tileStr;
    args >> tileStr;
    SharedTile playerTile = currentPlayer->hasTile(tileStr[0],
        std::stoi(
            tileStr.substr(1)));
    if (playerTile != nullptr) {
        currentPlayer->removeTile(playerTile);
        tileBag->addTile(playerTile);
        SharedTile newTile = tileBag->deleteTile(tileBag->getTile(0));
        currentPlayer->addTile(newTile);

        std::map<string, bool>::iterator it =
            enhancementsToStatusMap->find(COLOUR_MODE);
        std::cout << std::endl << "Added "
            << newTile->toString(it != enhancementsToStatusMap->end()
                ? it->second : false, false)
            << " to your hand" << std::endl;
        nextPlayerTurn();
    } else {
        std::cout << "Tile given isn't in your hand" << std::endl;
    }
}

void Game::placeCommand(std::stringstream & args) {
    string tileStr;
    string pos;
    args >> tileStr;
    // do it twice to filter out the 'at'
    args >> pos;
    args >> pos;
    SharedTile playerTile = currentPlayer->hasTile(tileStr[0],
        std::stoi(
            tileStr.substr(1)));
    if (playerTile != nullptr) {
        int points = board->placeTile(playerTile, pos[0],
            std::stoi(pos.substr(1)));
        if (points == -1) {
            std::cout << "Cannot place a tile here" << std::endl;
        } else {
            if (points >= 12) {
                std::cout << "QWIRKLE!" << std::endl;
            }
            currentPlayer->removeTile(playerTile);
            currentPlayer->addScore(points);
            SharedTile next = tileBag->deleteTile(tileBag->getTile(0));
            if (next != nullptr) {
                currentPlayer->addTile(next);
            }
            nextPlayerTurn();
        }
    } else {
        std::cout << "Tile given isn't in your hand" << std::endl;
    }
}

void Game::saveCommand(std::stringstream & args) {
    string filename;
    args >> filename;
    try {
        FileUtil::saveGame(filename, this);
        std::cout << "Game saved successfully" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to save: " << ex.what() << std::endl;
    }
}