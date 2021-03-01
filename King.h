#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The King class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the King
   ChessBoard& board - reference to the ChessBoard object which owns the King
   std::string name - the name of the Piece, in this case "King"
   bool hasMoved - false if the King has not moved yet */

class King : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a King object with colour and board set to the input variables,
     name set to "King" and hasMoved set to false.*/
  King(Player colour, ChessBoard& board);

  /* Constructs a King object which is a copy of the input King object, except
     for the board variable which is set to the input board. */
  King(King const& otherKing, ChessBoard& board);

  /* Destructor. */
  virtual ~King();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a King's move is possible by the rules of how a King should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the King object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the King has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the King object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the King object on which this function
     is called, but with the ChessBoard reference of the new object set to the 
     board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif
