#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

Shape Tile::getShape() {
    return shape;
}

Colour Tile::getColour() {
    return colour;
}

string Tile::toString(bool isColour, bool isSaving) {
    string result = "";

    if (isColour && !isSaving) {

        if (colour == RED) {
            result += RED_COLOUR;
        } else if (colour == GREEN) {
            result += GREEN_COLOUR;
        } else if (colour == YELLOW) {
            result += YELLOW_COLOUR;
        } else if (colour == BLUE) {
            result += BLUE_COLOUR;
        } else if (colour == PURPLE) {
            result += PURPLE_COLOUR;
        } else if (colour == ORANGE) {
            result += ORANGE_COLOUR;
        }
    }
    result += this->colour + std::to_string(this->shape);

    if (isColour && !isSaving) {
        result += RESET;
    }

    return result;
}


bool Tile::isEqual(const Tile& tile) {
    return this->shape == tile.shape && this->colour == tile.colour;
}
