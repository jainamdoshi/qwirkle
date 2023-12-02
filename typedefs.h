#ifndef ASSIGN2_TYPEDEFS_H
#define ASSIGN2_TYPEDEFS_H

#include <vector>
#include <memory>
#include <string>
#include <map>
class Tile;

class Player;

// Define a Colour type (Tile)
typedef char Colour;

// Define a Shape type (Tile)
typedef int Shape;

//Define a shared Tile pointer
typedef std::shared_ptr<Tile> SharedTile;

//Define a shared Player pointer
typedef std::shared_ptr<Player> SharedPlayer;

//Define a string type
typedef std::string string;

//Define a shared vector
template<typename T> using SharedVector = std::shared_ptr<std::vector<T>>;

#endif //ASSIGN2_TYPEDEFS_H
