/* This file contains the member functions and friend functions of the Piece
   class and its derived classes. */

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include "errors.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// ---------- Contructors, destructors and operator overloads ------------------

Piece::Piece(Player colour, ChessBoard& board, string name) :
  colour(colour), board(board), name(name), hasMoved(false) {}

Piece::~Piece() {}

/* Friend function */
ostream& operator<<(ostream& os, Piece const& piece) {
  os << piece.name;
  return os;
}

// ---------- Getter functions -------------------------------------------------

Player Piece::getColour() const {
  return colour;
}

string const& Piece::getName() const {
  return name;
}

// ---------- Setter functions -------------------------------------------------

void Piece::setHasMoved(bool hasMoved) {
  this->hasMoved = hasMoved;
}

// ---------- Checker functions ----------------------------------------------

bool Piece::isFirstMove() const {
  return !hasMoved;
}



