/* This file contains the member functions of the Knight class. */

#include "Knight.h"
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

Knight::Knight(Player colour, ChessBoard& board) :
  Piece(colour, board, "Knight") {}

Knight::Knight(Knight const& otherKnight, ChessBoard& board) :
  Piece(otherKnight.colour, board, otherKnight.name) {}

Knight::~Knight() {}

// ---------- Checker functions ------------------------------------------------

bool Knight::isMovePossible(Square sourceSquare, Square destinationSquare) {
  int rankChange = destinationSquare.getRank() - sourceSquare.getRank();
  int fileChange = destinationSquare.getFile() - sourceSquare.getFile();

  bool isMovingAlongL = ((abs(rankChange) == 2 && abs(fileChange) == 1) ||
			 (abs(rankChange) == 1 && abs(fileChange) == 2));

  bool destinationIsFree = !board.isPieceThere(destinationSquare);

  bool isTakingOpponent = board.isOpponentPieceThere(destinationSquare,
						     !colour);

  return (isMovingAlongL && (destinationIsFree || isTakingOpponent));
}

bool Knight::isAnyLegalMovePossible(Square square) {
  // Iterate over all possible moves that a Knight can make and check
  // if any are legal

  // Iterate over (abs(i), abs(j)) = (1, 2) and (2, 1) - eight possible
  // moves in total. i and j represent the changes in rank and file.
  for (int i = -2; i <= 2; i++) {
    for (int j = -2; j <= 2; j++) {
      if ((abs(i) != abs(j)) && (i != 0) && (j != 0)) {
	
	try {
	  Square destination{square.getRank() + i,
			     square.getFile() + j};
	  
	  if (this->isMovePossible(square, destination) &&
	      board.isMoveLegal(square, destination)) {
	    return true;
	  }
	} catch (OffBoardError const& e) {
	  // If the move is off the board then skip to the next possible
	  // move without checking it.
	}
      }
    }
  }    
  return false;
}

// ---------- Other functions --------------------------------------------------

Piece* Knight::copyPiece(ChessBoard& board) {
  return (new Knight{*this, board});
}
