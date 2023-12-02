#ifndef ASSIGN2_CONSTANTS_H
#define ASSIGN2_CONSTANTS_H

#include "typedefs.h"

// Colours

#define COLOURS_SIZE 6
#define RED    'R'
#define ORANGE 'O'
#define YELLOW 'Y'
#define GREEN  'G'
#define BLUE   'B'
#define PURPLE 'P'


// Shapes

#define SHAPES_SIZE 6
#define CIRCLE  1
#define STAR_4  2
#define DIAMOND 3
#define SQUARE  4
#define STAR_6  5
#define CLOVER  6

// Assumes a board of 26x26. This regex represents all possible commands supported by the program
#define COMMAND_REGEX "^(save .+|place [ROYGBP][1-6] at [A-Z](2[0-5]|[0-9]|1[0-9])|replace [ROYGBP][1-6])$"
#define DEFAULT_MAX_PLAYERS 2
#define ENHANCED_MAX_PLAYERS 3
#define ENHANCED_MIN_PLAYERS 4
#define HAND_SIZE 6
#define TEAM_SIZE 4
#define MIN_TILES_PLACEING 1
#define MAX_TILES_PLACEING 6

#define MAX_BOARD_SIZE 26
#define MIN_BOARD_DISPLAY 3
#define QWIRKLE_LENGTH 6
#define QWIRKLE_POINTS 6

#define MULTI_PLAYERS_MODE "3-4 Player mode"
#define EXPANDABLE_BOARD_MODE "Expandable Board"
#define COLOUR_MODE "Colour"

#define RESET "\033[0m"
#define RED_COLOUR "\033[31m"
#define GREEN_COLOUR "\033[32m"
#define YELLOW_COLOUR "\033[1m\033[33m"
#define BLUE_COLOUR "\033[34m"
#define PURPLE_COLOUR "\033[35m"
#define ORANGE_COLOUR "\033[38;5;202m"

namespace constants {
    // const static is a hint to the compiler to define these only once.
    const static Colour COLOURS[COLOURS_SIZE] = { RED, ORANGE, YELLOW, GREEN,
                                                 BLUE, PURPLE };
    const static Shape SHAPES[SHAPES_SIZE] = { CIRCLE, STAR_4, DIAMOND, SQUARE,
                                              STAR_6, CLOVER };
}

#endif // ASSIGN2_CONSTANTS_H
