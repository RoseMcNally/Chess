#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The Rook class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the Rook
   ChessBoard& board - reference to the ChessBoard object which owns the Rook
   std::string name - the name of the Piece, in this case "Rook"
   bool hasMoved - false if the Rook has not moved yet */

class Rook : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Rook object with colour and board set to the input variables,
     name set to "Rook" and hasMoved set to false.*/
  Rook(Player colour, ChessBoard& board);

  /* Constructs a Rook object which is a copy of the input Rook object, except
     for the board variable which is set to the input board. */
  Rook(Rook const& otherRook, ChessBoard& board);

  /* Destructor. */
  virtual ~Rook();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Rook's move is possible by the rules of how a Rook should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the Rook object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the Rook has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Rook object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the Rook object on which this function
     is called, but with the ChessBoard reference of the new object set to the 
     board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif
