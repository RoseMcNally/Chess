/* This file contains the member functions of the Rook class. */

#include "Rook.h"
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

Rook::Rook(Player colour, ChessBoard& board) :
  Piece(colour, board, "Rook") {}

Rook::Rook(Rook const& otherRook, ChessBoard& board) :
  Piece(otherRook.colour, board, otherRook.name) {}

Rook::~Rook() {}

// ---------- Checker functions ------------------------------------------------

bool Rook::isMovePossible(Square sourceSquare, Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();

  bool isAlongRankOrFile = (((abs(rankChange) == 0) ||
			     (abs(fileChange) == 0)) &&
			    !(rankChange == 0 && fileChange == 0));
  
  bool pathIsClear = true;

  // If the move is along a rank or file, set the number of squares in the
  // path to the number of squares the Rook moves (summing rankChange and
  // fileChange is fine because one of them will be always 0). Don't bother
  // checking path if isAlongRankOrFile is false because the move is not
  // allowed.
  int pathSteps = (isAlongRankOrFile) ? abs(rankChange + fileChange) : 0;

  try {
    for (int i = 1; i < pathSteps; i++) {
      int rankStep = (rankChange == 0) ? 0 : i * rankChange / abs(rankChange);
      int fileStep = (fileChange == 0) ? 0 : i * fileChange / abs(fileChange);
      
      Square squareInPath = Square(sourceSquare.getRank() + rankStep,
				   sourceSquare.getFile() + fileStep);
      
      pathIsClear = (pathIsClear && !board.isPieceThere(squareInPath));    
    }
  } catch (OffBoardError const& e) {
    // Path is not clear if move goes off board
    pathIsClear = false;
  }

  bool destinationIsFree = !board.isPieceThere(destinationSquare);

  bool isTakingOpponent = board.isOpponentPieceThere(destinationSquare, !colour);
  
  return (isAlongRankOrFile && pathIsClear &&
	  (destinationIsFree || isTakingOpponent));
}

bool Rook::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that a Rook can make and check
  // if any are legal

  // Iterate over (i, j) = (-1, 0), (1, 0), (0, -1) and (0, 1) 
  // These are the four directions that a Rook can move i.e.
  // forward and backward along rank or file.
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (abs(i) != abs(j)) {
	
	int rankStep = i;
	int fileStep = j;
	try {
	  Square destination{square.getRank() + rankStep,
			     square.getFile() + fileStep};

	  // While a move along one direction is possible, check if it
	  // is legal. If it is not, move further along that direction
	  // and check again. As soon as the next move along the direction
	  // is either not possible, or goes off the board, skip to the
	  // next direction iteration.
	  while (this->isMovePossible(square, destination)) {
	    if (board.isMoveLegal(square, destination)) {
	      return true;
	    }
	    // Move to next square out
	    destination = Square{destination.getRank() + rankStep,
				 destination.getFile() + fileStep};
	  }
	} catch (OffBoardError const& e) {
	  // If the move goes off the board, skip to the next direction
	  // iteration
	}
      }
    }
  }
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* Rook::copyPiece(ChessBoard& board) {
  return (new Rook{*this, board});
}
