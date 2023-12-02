#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"
#include "Tile.h"
#include <memory>

// class LinkedList;
// class Tile;

class Player {

public:

    // Constructor
    explicit Player(string name);

    // Destructor
    ~Player();

    // Adds a Tile to the player's hand with the given tile
    void addTile(const SharedTile& tile);

    // Getter methods
    string getName();

    int getScore();

    // Whether the player has the given tile on hand
    SharedTile hasTile(Colour color, Shape shape);

    //Return a player's hand
    std::shared_ptr<LinkedList> getHand();

    //Set a player's hand
    void setHand(std::shared_ptr<LinkedList> hand);

    //Remove the given tile from the player
    bool removeTile(const SharedTile& tile);

    // Adds score to the player
    void addScore(int score);

    // Setter method
    void setScore(int score);

    // ToString method
    string toString(bool isColour, bool isSaving);

private:

    // Class Variables
    string name;
    int score;
    std::shared_ptr<LinkedList> hand;

};

#endif // ASSIGN2_PLAYER_H