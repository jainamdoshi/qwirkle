
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {
public:

    //Constructor
    Node(SharedTile tile, std::shared_ptr<Node> next);

    //return the tile
    SharedTile &getTile();

    //return the next Node pointer
    std::shared_ptr<Node> &getNext();

    //set the next Node pointer
    void setNext(const std::shared_ptr<Node> &next);

private:
    //Class Variables
    SharedTile tile;
    std::shared_ptr<Node> next;
};

#endif // ASSIGN2_NODE_H
