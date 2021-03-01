#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The Queen class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the Queen
   ChessBoard& board - reference to the ChessBoard object which owns the Queen
   std::string name - the name of the Piece, in this case "Queen"
   bool hasMoved - false if the Queen has not moved yet */

class Queen : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Queen object with colour and board set to the input variables,
     name set to "Queen" and hasMoved set to false.*/
  Queen(Player colour, ChessBoard& board);

  /* Constructs a Queen object which is a copy of the input Queen object, except
     for the board variable which is set to the input board. */
  Queen(Queen const& otherQueen, ChessBoard& board);

  /* Destructor. */
  virtual ~Queen();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Queen's move is possible by the rules of how a Queen should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the Queen object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the Queen has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Queen object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the Queen object on which this 
     function is called, but with the ChessBoard reference of the new object set 
     to the board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif
