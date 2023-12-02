#include "GameBoard.h"

GameBoard::GameBoard(
    std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap) {

    this->currentHeight = 0;
    this->currentWidth = 0;
    placedTiles = std::make_shared<std::vector<string>>();
    // Initializing the board with 26 x 26 space
    this->board = std::make_shared<std::vector<SharedVector<SharedTile>>>();
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        SharedVector<SharedTile> row =
            std::make_shared<std::vector<SharedTile>>(
                MAX_BOARD_SIZE, nullptr);
        board->push_back(row);
    }
    this->enhancementsToStatusMap = enhancementsToStatusMap;
}

GameBoard::GameBoard(int height, int width,
    std::shared_ptr<std::map<string, bool>> enhancementsToStatusMap) :
    GameBoard(enhancementsToStatusMap) {
    this->currentHeight = height;
    this->currentWidth = width;
}

int GameBoard::mapCharToRow(char target) {
    return (int)target - 'A';
}

char GameBoard::mapRowToChar(int target) {
    return (char)(target + 'A');
}

SharedTile GameBoard::getTile(int row, int col) {
    return this->board->at(row)->at(col);
}

GameBoard::~GameBoard() = default;


void GameBoard::addTilesWithPos(const SharedTile & tile, int row, int col) {
    // Builds a string of the tile at the position in format <colour><shape>@<row><col>
    if (tile != nullptr) {
        placedTiles->push_back(tile->toString(false, true) + "@"
            + this->mapRowToChar(row)
            + std::to_string(col));
    }
}

int GameBoard::placeTile(const SharedTile & tile, char rowChar, int col) {

    int score = -1;
    int row = this->mapCharToRow(rowChar);
    // Checks if the row and col is not out of the board dimensions
    if (row <= MAX_BOARD_SIZE && col <= MAX_BOARD_SIZE) {

        // Checks if there is no tile at row and col, and checks if that tile is legal to place at row and col
        // If the validation is true, then it will place the tile and calculate the score 
        if (this->getTile(row, col) == nullptr &&
            this->isValidTileToPlace(tile, row, col)) {

            this->board->at(row)->at(col) = tile;
            score = this->calculateScore(row, col);
            this->addTilesWithPos(tile, row, col);

            // Change current height and width
            if (row + 1 > this->currentHeight) {
                this->currentHeight = row + 1;
            }
            if (col + 1 > this->currentWidth) {
                this->currentWidth = col + 1;
            }
        }
    }
    return score;
}

void GameBoard::placeTileInLoading(const SharedTile & tile, char rowChar,
    int col) {
    int row = this->mapCharToRow(rowChar);
    this->board->at(row)->at(col) = tile;
    this->addTilesWithPos(tile, row, col);
}

bool GameBoard::isValidTileToPlace(const SharedTile & tile, int row, int col) {
    bool valid = true;
    bool neighbourningTile = false;
    SharedVector<SharedVector<SharedTile>> allTilesIn2Direction =
        this->getAllTilesIn2Direction(row, col);

    // Iterates of all of the directions (left-right and up-down) and until the tile is valid to place
    for (unsigned int i = 0; i < allTilesIn2Direction->size() && valid; i++) {
        SharedVector<SharedTile> tilesIn1Direction =
            allTilesIn2Direction->at(i);

        // Checks the placed tile does not add to the Qwirkle
        if (tilesIn1Direction->size() < QWIRKLE_LENGTH) {

            if (tilesIn1Direction->size() <= 0 && isThereAnyTilePlaced() &&
                !neighbourningTile) {
                neighbourningTile = false;
            } else {
                neighbourningTile = true;
            }
            // Iterates over all the tiles in each directions and until the tile is valid to place
            for (unsigned int j = 0; j < tilesIn1Direction->size() && valid;
                j++) {
                SharedTile currentTile = tilesIn1Direction->at(j);

                // The tile is not valid if the two tiles are same or both the shape and the colour are not different
                if (currentTile->isEqual(*tile) ||
                    (currentTile->getShape() != tile->getShape() &&
                        currentTile->getColour() != tile->getColour())) {
                    valid = false;
                }
            }
        }
    }

    if (!neighbourningTile) {
        valid = false;
    }

    return valid;
}

bool GameBoard::isThereAnyTilePlaced() {

    bool isThereTile = false;

    for (unsigned int row = 0; row < this->board->size() && !isThereTile;
        row++) {
        for (unsigned int col = 0;
            col < this->board->at(row)->size() && !isThereTile; col++) {
            if (this->board->at(row)->at(col) != nullptr) {
                isThereTile = true;
            }
        }
    }

    return isThereTile;
}


int GameBoard::calculateScore(int row, int col) {
    int score = 0;
    SharedVector<SharedVector<SharedTile>> allTilesIn4Direction =
        this->getAllTilesIn2Direction(row, col);

    // Iterates over the 4 directions (left, right, up, down)
    for (auto tilesIn1Direction : *allTilesIn4Direction) {
        unsigned int size = tilesIn1Direction->size();

        // If there is a tile in a direction then increase score by the size
        if (size > 0) {

            // This is Qwirkle! If a direction has 5 tiles, it add 6 points
            if (size == QWIRKLE_LENGTH - 1) {
                score += QWIRKLE_POINTS;
            }
            score += size + 1;
        }
    }

    // This condition is true if there is only tile in the board
    if (score == 0) {
        score += 1;
    }
    return score;
}


SharedVector<SharedVector<SharedTile>>
GameBoard::getAllTilesIn2Direction(int row, int col) {

    SharedVector<SharedVector<SharedTile>> tiles =
        std::make_shared<std::vector<SharedVector<SharedTile>>>();

    // Get tiles from each direction and add it in a vector
    SharedVector<SharedTile> getAllTilesLeft = this->getAllTilesIn1Direction(
        row, col, 0, -1);
    SharedVector<SharedTile> getAllTilesRight = this->getAllTilesIn1Direction(
        row, col, 0, 1);
    SharedVector<SharedTile> getAllTilesUp = this->getAllTilesIn1Direction
    (row, col, -1, 0);
    SharedVector<SharedTile> getAllTilesDown = this->getAllTilesIn1Direction(
        row, col, 1, 0);

    // Merging the left and up vectors with right and down vectors of tiles respectively
    tiles->push_back(addTwoVectors(getAllTilesLeft, getAllTilesRight));
    tiles->push_back(addTwoVectors(getAllTilesUp, getAllTilesDown));


    return tiles;
}


SharedVector<SharedTile>
GameBoard::addTwoVectors(SharedVector<SharedTile> vector1,
    SharedVector<SharedTile> vector2) {

    // Loops and adds all the elements from vector1 into vector2
    for (auto element : *vector1) {
        vector2->push_back(element);
    }
    return vector2;
}

SharedVector<SharedTile>
GameBoard::getAllTilesIn1Direction(int row, int col, int changeInRow,
    int changeInCol) {

    SharedVector<SharedTile> tiles =
        std::make_shared<std::vector<SharedTile>>();

    SharedTile currentTile = nullptr;

    // Loop till the current tile is not a null_ptr (i.e. no more tiles to loop through in one direction)
    do {

        // For the initial iteration of the loop, the condition is always true after the first iteration
        if (currentTile != nullptr) {
            tiles->push_back(currentTile);
        }

        row += changeInRow;
        col += changeInCol;

        // Checks if the new row and col are not out of bound of the board dimensions
        if (row >= 0 && col >= 0 && row <= MAX_BOARD_SIZE - 1 &&
            col <= MAX_BOARD_SIZE - 1) {
            currentTile = this->board->at(row)->at(col);
        } else {
            currentTile = nullptr;
        }

    } while (currentTile != nullptr);
    return tiles;
}

string GameBoard::toString() {
    string result = std::to_string(this->currentHeight) + "," +
        std::to_string(this->currentWidth) + "\n";

    // Gets all the tiles in the board with their positions
    SharedVector<string> tilesWithPos = this->placedTiles;
    // Appends each string from the vector to the result
    for (unsigned int index = 0; index < tilesWithPos->size(); index++) {
        result = result + tilesWithPos->at(index);

        // Ignores a comma after the last tile
        if (index + 1 != tilesWithPos->size()) {
            result = result + ", ";
        }
    }
    return result + "\n";
}

void GameBoard::displayBoard() {
    int boardHeight = board->size();
    int boardWidth = board->size();
    std::map<string, bool>::iterator it =
        enhancementsToStatusMap->find(EXPANDABLE_BOARD_MODE);

    if (it != enhancementsToStatusMap->end() && it->second) {
        if (currentHeight < MIN_BOARD_DISPLAY) {
            boardHeight = MIN_BOARD_DISPLAY;
        } else {
            boardHeight = currentHeight + 1;
        }

        if (currentWidth < MIN_BOARD_DISPLAY) {
            boardWidth = MIN_BOARD_DISPLAY;
        } else {
            boardWidth = currentWidth + 1;
        }
    }

    //printing the numbers
    std::cout << "   ";
    for (int col = 0; col < boardWidth && col < MAX_BOARD_SIZE; col++) {
        std::cout << col;
        if (col >= 10) {
            std::cout << " ";
        } else if (col != boardWidth - 1 && col < 10 && col < MAX_BOARD_SIZE) {
            std::cout << "  ";
        }
    }

    std::cout << std::endl;

    //printing the dashed lines
    std::cout << "  ";
    for (int col = 0; col < boardWidth && col < MAX_BOARD_SIZE; col++) {
        if (col == 0) {
            std::cout << "----";
        } else {
            std::cout << "---";
        }
    }

    std::cout << std::endl;
    //printing the tiles
    for (int row = 0; row < boardHeight && row < MAX_BOARD_SIZE; row++) {

        std::cout << this->mapRowToChar(row) << " |";
        for (int col = 0; col < boardWidth && col < MAX_BOARD_SIZE; col++) {
            if (getTile(row, col) == nullptr) {
                std::cout << "  |";
            } else {
                std::map<string, bool>::iterator it =
                    enhancementsToStatusMap->find(COLOUR_MODE);
                std::cout << getTile(row, col)->toString(it
                    != enhancementsToStatusMap->end() ? it->second
                    : false, false) << "|";
            }
        }
        std::cout << std::endl;
    }
}

