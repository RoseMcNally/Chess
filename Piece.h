#ifndef PIECE_H
#define PIECE_H

#include "constants.h"
#include "Square.h"
#include "Player.h"
#include <iostream>
#include <string>

class ChessBoard; // Forward declaration to avoid circular dependencies

/* The Piece class contains a Player, a reference, a string and a boolean 
   value.
   colour contains a Player enumerator giving the colour of the Piece.
   board is a reference to the ChessBoard object which owns the Piece.
   name is a string containing the name of the Piece.
   hasMoved is a boolean which is false is the Piece has not yet been 
   moved, and true if it has. 
   Piece is an abstract base class - the derived classes are Pawn, Bishop, 
   Knight, Rook, Queen and King. */

class Piece {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs a Piece object with colour, board and name initialised
     to the input values and hasMoved initialised to false. */
  Piece(Player colour, ChessBoard& board, std::string name);

  /* Destructor. */
  virtual ~Piece();

  /* This friend function allows the operator<< to be used with a Piece 
     object to output the name of the Piece to the output stream given. 
     It takes the Piece object by reference so works for all derived classes 
     too. */
  friend std::ostream& operator<<(std::ostream& os, Piece const& piece);

  // ---------- Getter functions -----------------------------------------------

  /* Returns a copy of the colour. */
  Player getColour() const;

  /* Returns a constant reference to the name. */
  std::string const& getName() const;

  // ---------- Setter functions -----------------------------------------------
  
  /* Sets the hasMoved value to the input. */
  void setHasMoved(bool hasMoved);
  
  // ---------- Checker functions ----------------------------------------------

  /* Checks the hasMoved value to see if the Piece has moved before. If not
     returns true, otherwise returns false. */
  bool isFirstMove() const;
  
  /* Checks if a Piece's move is possible by the rules of how a Piece should
     move in chess. Does not check if the move is legal. The function must 
     be called on the Piece object in the location of the sourceSquare. */
  virtual bool isMovePossible(Square sourceSquare,
			      Square destinationSquare) = 0;

  /* Checks if the Piece has any possible legal moves by iterating over
     all possible moves and calling the ChessBoard::isMoveLegal() function. 
     Should be called on the Piece object in the location of the square 
     input. */
  virtual bool isAnyLegalMovePossible(Square square) = 0;

  // ---------- Other functions ------------------------------------------------

  /* Returns a pointer to a copy of the Piece object on which this function 
     is called, but with the reference of the new object set to the board
     input. */
  virtual Piece* copyPiece(ChessBoard& board) = 0;
    
protected:
  Player colour;
  ChessBoard& board;
  std::string const name;
  bool hasMoved = false;
};

#endif
