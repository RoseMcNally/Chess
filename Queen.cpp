/* This file contains the member functions of the Queen class. */

#include "Queen.h"
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

Queen::Queen(Player colour, ChessBoard& board) :
  Piece(colour, board, "Queen") {}

Queen::Queen(Queen const& otherQueen, ChessBoard& board) :
  Piece(otherQueen.colour, board, otherQueen.name) {}

Queen::~Queen() {}

// ---------- Checker functions ------------------------------------------------

bool Queen::isMovePossible(Square sourceSquare, Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();

  bool isAlongDiagonal = (abs(rankChange) == abs(fileChange) &&
			  !(rankChange == 0 && fileChange == 0));

  bool isAlongRankOrFile = (((abs(rankChange) == 0) ||
			     (abs(fileChange) == 0)) &&
			    !(rankChange == 0 && fileChange == 0));
  
  bool pathIsClear = true;

  int pathSteps;
  if (isAlongDiagonal) {
    // Set the number of squares in the path to be the absolute change in rank
    // (could equally be set to absolute change in file since they are equal).
    pathSteps = abs(rankChange);
  } else if (isAlongRankOrFile) {
    // Set it to the number of squares moved in the direction that it moved
    // (summing rankChange and fileChange is fine because one is always 0).
    pathSteps = abs(rankChange + fileChange);
  } else {
    // Don't bother checking if neither isAlongDiagonal nor isAlongRankOrFile
    // are true because the move is not possible.
    pathSteps = 0;
    pathIsClear = false;
  }

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

  return ((isAlongDiagonal || isAlongRankOrFile) && pathIsClear &&
	  (destinationIsFree || isTakingOpponent));
}

bool Queen::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that a Queen can make and check
  // if any are legal

  // Iterate over (abs(i), abs(j)) = (1, 0), (0, 1) and (1, 1) - eight
  // possible directions in total. i and j represent the directions in
  // which the Queen can move i.e. forward and backward along a rank,
  // file or either diagonal.
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (!(i == 0 && j == 0)) {
	
	int rankStep = i;
	int fileStep = j;
	try {
	  Square destination{square.getRank() + rankStep,
			     square.getFile() + fileStep};

	  // While a move in the direction is possible, check if it
	  // is legal. If it is not, move further along the direction
	  // and check again. Keep checking until a move is not possible
	  // or the move goes off the board, at which point skip to the
	  // next direction iteration.
	  while (this->isMovePossible(square, destination)) {
	    if (board.isMoveLegal(square, destination)) {
	      return true;
	    }
	    // Move one square further out
	    destination = Square{destination.getRank() + rankStep,
				 destination.getFile() + fileStep};
	  }
	} catch (OffBoardError const& e) {
	  // If the move goes off the board skip to the next direction
	  // iteration
	}
      }
    }
  }
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* Queen::copyPiece(ChessBoard& board) {
  return (new Queen{*this, board});
}
