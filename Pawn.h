#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The Pawn class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the Pawn
   ChessBoard& board - reference to the ChessBoard object which owns the Pawn
   std::string name - the name of the Piece, in this case "Pawn"
   bool hasMoved - false if the Pawn has not moved yet */

class Pawn : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Pawn object with colour and board set to the input variables,
     name set to "Pawn" and hasMoved set to false.*/
  Pawn(Player colour, ChessBoard& board);

  /* Constructs a Pawn object which is a copy of the input Pawn object, except
     for the board variable which is set to the input board. */
  Pawn(Pawn const& otherPawn, ChessBoard& board);

  /* Destructor. */
  virtual ~Pawn();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Pawn's move is possible by the rules of how a Pawn should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the Pawn object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the Pawn has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Pawn object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the Pawn object on which this function
     is called, but with the ChessBoard reference of the new object set to the 
     board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif

