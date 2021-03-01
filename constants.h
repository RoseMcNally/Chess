#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <string>

const int ASCII_ONE = 49;
const int ASCII_EIGHT = 56;
const int ASCII_A = 65;
const int ASCII_H = 72;

const int BOARD_LENGTH = 8;
const int BOARD_WIDTH = 8;

const int MAX_RANK = 7;
const int MAX_FILE = 7;
const int MIN_RANK = 0;
const int MIN_FILE = 0;

// Index within a string containing the rank and file e.g. "E2".
const int RANK_INDEX = 1;
const int FILE_INDEX = 0;

// Indices for second and seventh ranks
const int RANK_TWO = 1;
const int RANK_SEVEN = 6;

/* Starting positions for pieces on board*/
const std::string WHITE_KING_START_SQUARE = "E1";
const std::string BLACK_KING_START_SQUARE = "E8";

const std::string WHITE_QUEEN = "D1";
const std::string BLACK_QUEEN = "D8";

const std::string WHITE_KING_ROOK = "H1";
const std::string WHITE_QUEEN_ROOK = "A1";
const std::string BLACK_KING_ROOK = "H8";
const std::string BLACK_QUEEN_ROOK = "A8";

const std::string WHITE_KING_KNIGHT = "G1";
const std::string WHITE_QUEEN_KNIGHT = "B1";
const std::string BLACK_KING_KNIGHT = "G8";
const std::string BLACK_QUEEN_KNIGHT = "B8";

const std::string WHITE_KING_BISHOP = "F1";
const std::string WHITE_QUEEN_BISHOP = "C1";
const std::string BLACK_KING_BISHOP = "F8";
const std::string BLACK_QUEEN_BISHOP = "C8";

#endif
