#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The Knight class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the Knight
   ChessBoard& board - reference to the ChessBoard object which owns the Knight
   std::string name - the name of the Piece, in this case "Knight"
   bool hasMoved - false if the Knight has not moved yet */

class Knight : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Knight object with colour and board set to the input 
     variables, name set to "Knight" and hasMoved set to false.*/
  Knight(Player colour, ChessBoard& board);

  /* Constructs a Knight object which is a copy of the input Knight object, 
     except for the board variable which is set to the input board. */
  Knight(Knight const& otherKnight, ChessBoard& board);

  /* Destructor. */
  virtual ~Knight();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Knight's move is possible by the rules of how a Knight should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the Knight object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the Knight has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Knight object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the Knight object on which this 
     function is called, but with the ChessBoard reference of the new object set 
     to the board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif
