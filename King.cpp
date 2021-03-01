/* This file contains the member functions of the King class. */

#include "King.h"
#include "Piece.h"
#include "Player.h"
#include "ChessBoard.h"
#include "constants.h"
#include "errors.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// ---------- Contructors, destructors and operator overloads ------------------

King::King(Player colour, ChessBoard& board) :
  Piece(colour, board, "King") {}

King::King(King const& otherKing, ChessBoard& board) :
  Piece(otherKing.colour, board, otherKing.name) {}

King::~King() {}

// ---------- Checker functions ------------------------------------------------

bool King::isMovePossible(Square sourceSquare, Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();

  bool isMovingOneSquare = ((abs(rankChange) == 1 || abs(rankChange) == 0) &&
			    (abs(fileChange) == 1 || abs(fileChange) == 0) &&
			    !(rankChange == 0 && fileChange == 0));
  
  bool destinationIsFree = !board.isPieceThere(destinationSquare);

  bool isTakingOpponent = board.isOpponentPieceThere(destinationSquare,
						     !colour);

  return (isMovingOneSquare && (destinationIsFree || isTakingOpponent));
}

bool King::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that a King can make and check
  // if any are legal

  // Iterate over (abs(i), abs(j)) = (1, 0), (0, 1) and (1, 1) - eight possible
  // moves in total. i and j represent the rank and file changes which
  // result in a possible King move.
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (!(i == 0 && j == 0)) {
	
	int destinationRank = square.getRank() + i;
	int destinationFile = square.getFile() + j;
	
	try {
	  Square destination{destinationRank, destinationFile};
	  
	  if (this->isMovePossible(square, destination) &&
	      board.isMoveLegal(square, destination)) {
	    return true;
	  }
	  
	} catch (OffBoardError const& e) {
	  // If the move goes off the board, skip to the next possible move.
	}
      }
    }
  }
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* King::copyPiece(ChessBoard& board) {
  return (new King{*this, board});
}
