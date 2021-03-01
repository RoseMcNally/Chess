/* This file contains the member functions of the Pawn class. */

#include "Piece.h"
#include "Pawn.h"
#include "Player.h"
#include "ChessBoard.h"
#include "constants.h"
#include "errors.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// ---------- Contructors, destructors and operator overloads ------------------

Pawn::Pawn(Player colour, ChessBoard& board) : Piece(colour, board, "Pawn") {}

Pawn::Pawn(Pawn const& otherPawn, ChessBoard& board) :
  Piece(otherPawn.colour, board, otherPawn.name) {}

Pawn::~Pawn() {}

// ---------- Checker functions ------------------------------------------------

bool Pawn::isMovePossible(Square sourceSquare,
			  Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();
  
  bool isOneSquareForward = (fileChange == 0 &&
			     ((rankChange == 1 && colour == White) ||
			      (rankChange == -1 && colour == Black)));
  
  bool isTwoSquaresForward = (fileChange == 0 &&
			      ((rankChange == 2 && colour == White) ||
			       (rankChange == -2 && colour == Black)));
  
  bool isFirstMoveOfPawn = !(this->hasMoved);

  bool pathIsClear = true;
  
  // If Pawn moves two squares forward, check the square in between
  if (isTwoSquaresForward) {
    try {
      Square squareInPath =
	Square(sourceSquare.getRank() + (rankChange / abs(rankChange)),
	       sourceSquare.getFile());
      
      pathIsClear = !(board.isPieceThere(squareInPath));
    } catch (OffBoardError const& e) {
      // Path is not clear if it involves moving off the board
      pathIsClear = false;
    }
  }
		  
  bool destinationIsFree = !(board.isPieceThere(destinationSquare));

  bool isOneAlongDiagonal = (abs(fileChange) == 1 &&
			     ((rankChange == 1 && colour == White) ||
			      (rankChange == -1 && colour == Black)));

  bool isTakingOpponent = (board.isOpponentPieceThere(destinationSquare,
						      !colour));

  bool isMovePossible = ((isOneSquareForward && destinationIsFree) ||

			 (isTwoSquaresForward && destinationIsFree &&
			  pathIsClear && isFirstMoveOfPawn) ||

			 (isOneAlongDiagonal && isTakingOpponent));

  return isMovePossible;
}

bool Pawn::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that Pawn can make and check
  // if any are legal

  int rankChange = (colour == White) ? 1 : -1; // Forward one square

  // Either one left, right or straight ahead
  for (int fileChange = -1; fileChange <= 1; fileChange++) {
    
    int destinationRank = square.getRank() + rankChange;
    int destinationFile = square.getFile() + fileChange;

    try {
      Square destination{destinationRank, destinationFile};
      if (this->isMovePossible(square, destination) &&
	  board.isMoveLegal(square, destination)) {
	return true;
      }
    } catch (OffBoardError const& e) {
      // If the square created is not on the board,
      // just move on to the next loop iteration
    }    
  }

  bool isFirstMoveOfPawn = !(this->hasMoved);

  if (isFirstMoveOfPawn) {
    rankChange = (colour == White) ? 2 : -2;
    int fileChange = 0;

    try {
      Square destination{square.getRank() + rankChange,
			 square.getFile() + fileChange};
      
      if (this->isMovePossible(square, destination) &&
	  board.isMoveLegal(square, destination)) {
	return true;
      }
    } catch (OffBoardError const& e) {
      // Don't check if the move is off the board
    }
  }
  
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* Pawn::copyPiece(ChessBoard& board) {
  return (new Pawn{*this, board});
}
