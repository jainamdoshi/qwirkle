#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include <memory>
#include "typedefs.h"
#include "constants.h"


class Tile {

public:

    // Constructor
    Tile(Colour colour, Shape shape);

    //Checks for Tile equality
    bool isEqual(const Tile& tile);

    // Getter methods
    Colour getColour();

    Shape getShape();

    // ToString method
    string toString(bool isColour, bool isSaving);

private:

    // Class variables
    Colour colour;
    Shape shape;


};

#endif // ASSIGN2_TILE_H