/* This file contains the member functions of the Bishop class. */

#include "Bishop.h"
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

Bishop::Bishop(Player colour, ChessBoard& board) :
    Piece(colour, board, "Bishop") {}

Bishop::Bishop(Bishop const& otherBishop, ChessBoard& board) :
  Piece(otherBishop.colour, board, otherBishop.name) {}

Bishop::~Bishop() {}

// ---------- Checker functions ------------------------------------------------

bool Bishop::isMovePossible(Square sourceSquare, Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();

  bool isAlongDiagonal = (abs(rankChange) == abs(fileChange) &&
			  !(rankChange == 0 && fileChange == 0));

  bool pathIsClear = true;

  // If it is a move along the diagonal, set the number of squares
  // in the path to the absolute change in rank (could also be set to
  // the absolute change in file as they are equal). If isAlongDiagonal is
  // false then don't need to check path because move is not possible anyway.
  int pathSteps = (isAlongDiagonal) ? abs(rankChange) : 0;

  try {
    for (int i = 1; i < pathSteps; i++) {
      int rankStep =  i * rankChange / abs(rankChange);
      int fileStep =  i * fileChange / abs(fileChange);

      Square squareInPath = Square(sourceSquare.getRank() + rankStep,
				   sourceSquare.getFile() + fileStep);
      
      pathIsClear = (pathIsClear && !board.isPieceThere(squareInPath));
    }
  } catch (OffBoardError const& e) {
    // Path is not clear if move goes off board
    pathIsClear = false;
  }

  
  bool destinationIsFree = !board.isPieceThere(destinationSquare);
  
  bool isTakingOpponent = board.isOpponentPieceThere(destinationSquare,
						     !colour);
  
  return (isAlongDiagonal && pathIsClear &&
	  (destinationIsFree || isTakingOpponent));
}

bool Bishop::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that a Bishop can make and check
  // if any are legal

  // Iterate over (i, j) = (-1, -1), (-1, 1), (1, -1) and (1, 1)
  // These are four directions that the Bishop could move i.e.
  // forward and backward along the two diagonals.
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if ((abs(i) == abs(j)) && (i != 0) && (j != 0)) {

	int rankStep = i;
	int fileStep = j;
	try {
	  Square destination{square.getRank() + rankStep,
			     square.getFile() + fileStep};

	  // While a move along the diagonal is possible, check if
	  // it is legal. If it is not, move out to the next
	  // square along the diagonal and check that. As soon
	  // as a move is not possible or it goes off the board,
	  // move on to the next direction iteration.
	  while (this->isMovePossible(square, destination)) {
	    if (board.isMoveLegal(square, destination)) {
	      return true;
	    }
	    // Move to the next square out
	    destination = Square{destination.getRank() + rankStep,
				 destination.getFile() + fileStep};
	  }
	} catch (OffBoardError const& e) {
	  // If it goes off the board, skip to the next direction
	  // iteration
	}
      }
    }
  }
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* Bishop::copyPiece(ChessBoard& board) {
  return (new Bishop{*this, board});
}
