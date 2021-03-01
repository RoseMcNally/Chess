#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Player.h"
#include "Square.h"
#include "ChessBoard.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <string>

/* The Bishop class is derived from the Piece class. It inherits the member 
   variables: 
   Player colour - contains the colour of the Bishop
   ChessBoard& board - reference to the ChessBoard object which owns the Bishop
   std::string name - the name of the Piece, in this case "Bishop"
   bool hasMoved - false if the Bishop has not moved yet */

class Bishop : public Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Bishop object with colour and board set to the input 
     variables, name set to "Bishop" and hasMoved set to false.*/
  Bishop(Player colour, ChessBoard& board);

  /* Constructs a Bishop object which is a copy of the input Bishop object, 
     except for the board variable which is set to the input board. */
  Bishop(Bishop const& otherBishop, ChessBoard& board);

  /* Destructor. */
  virtual ~Bishop();

  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Bishop's move is possible by the rules of how a Bishop should 
     move in chess. Does not check if the move is legal. The function must 
     be called on the Bishop object in the location of the sourceSquare. */
  bool isMovePossible(Square sourceSquare, Square destinationSquare) override;

  /* Checks if the Bishop has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Bishop object in the location of the square 
     input. */
  bool isAnyLegalMovePossible(Square square) override;

  // ---------- Other functions ------------------------------------------------

  /* Returns a Piece pointer to a copy of the Bishop object on which this 
     function is called, but with the ChessBoard reference of the new object set 
     to the board input. */
  Piece* copyPiece(ChessBoard& board) override;
};

#endif

