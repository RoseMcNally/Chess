#ifndef SQUARE_H
#define SQUARE_H

#include <string>

/* The Square class is made up of two integers. A Square object represents
   a square on a standard chessboard. 
   rankIndex and fileIndex correspond to the rank and file of a square
   on a standard chessboard. */

class Square {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs Square object with uninitialised rankIndex and fileIndex. */
  Square();

  /* Constructs Square object with initialised rankIndex and fileIndex.
     rankAndFile should be a string of length 2. The first element of the 
     string should be a letter corresponding to the file in the range 'A-H'
     and the second element should be a numeric character corresponding to 
     the rank in the range '1-8'. If the input is not in the correct range
     then the constructor throws the OffBoardError exception defined
     in the "errors.h" file. */
  Square(std::string rankAndFile);

  /* Constructs Square object with rankIndex initialised to the input
     rankIndex and fileIndex initialised to the input fileIndex. 
     If rankIndex or fileIndex are not in the allowed range of 0-7 
     then the constructor throws the OffBoardError exception defined
     in the "errors.h" file. */
  Square(int rankIndex, int fileIndex);

  /* Destructor. */
  ~Square();

  /* Returns true if the rankIndex and the fileIndex of both Square objects
     are equal. Returns fase otherwise. */
  bool operator==(Square const& otherSquare) const;

  /* This friend function allows the operator<< to be used with a Square 
     object to output the Square's contents to the output stream specified.
     The Square's contents is output in rank and file form, i.e. a string
     containg the file letter and the rank number, for example 'E4'. 
     Please note this function is defined in the Square.cpp implementation
     file. */
  friend std::ostream& operator<<(std::ostream& os, Square const& square);
  
  // ---------- Getter functions -----------------------------------------------

  /* Returns a copy of the rankIndex. */
  int getRank() const;

  /* Returns a copy of the fileIndex. */
  int getFile() const;

private:
  int rankIndex;
  int fileIndex;

  // ---------- Checker functions ----------------------------------------------

  /* Checks that a Square object contains a valid rankIndex and fileIndex, i.e.
     that they both lie in the range 0-7. */
  bool isOnBoard() const;

  /* Checks that a string containing the rank and file in chess notation 
     refers to a square on a standard chess board. */
  bool isOnBoard(std::string moveInput) const;
  
};

#endif
