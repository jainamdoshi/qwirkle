
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>
#include <memory>

typedef SharedTile SharedTile;

class LinkedList {
public:

    //Constructor
    LinkedList();

    //Destructor
    ~LinkedList();

    // Return length of LinkedList
    int size();

    // return Tile at index i
    SharedTile getTile(int i);

    SharedTile getTile(const Tile& searchTile);

    // Add tile
    void addTile(const SharedTile& tile);

    //Check if LinkedList is empty or not.
    bool isEmpty();

    // delete tile at index i
    SharedTile deleteTile(const SharedTile& toRemove);

    // To String method
    string toString(bool isColour, bool isSaving);

private:
    // Point at the head of Linked List
    std::shared_ptr<Node> head;
    //Point at the tail of the Linked List
    std::shared_ptr<Node> tail;

    //Length of the Linked List
    int length;
};

#endif // ASSIGN2_LINKEDLIST_H
