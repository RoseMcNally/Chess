#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Square.h"
#include "Player.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "constants.h"
#include <string>

/* The ChessBoard class contains a Player enumerator and and a Piece
   (triple) pointer. When a ChessBoard object is constructed, an 8x8
   array of Piece pointers is constructed. This array represents the 
   squares on a chessboard, and the Piece pointers point to Piece objects
   or null if there is no Piece there. A Square object's rank and
   file can be used to index a location on the board. */

class ChessBoard {
public:
  // ---------- Contructors, destructors and operator overloads ----------------

  /* Constructs ChessBoard object with all the Pieces in the correct starting
     positions and the player set to White. */
  ChessBoard();

  /* Destructor. The ChessBoard object owns all of the objects pointed to
     in the board array, so this goes through and deletes all of them, and
     then deletes the array. */
  ~ChessBoard();

  /* Overloaded assignement operator. This function ensures deep copies
     are made of the board array, and that the Pieces pointed to by the
     copied board array contain references to the copied board. */
  ChessBoard& operator=(ChessBoard const& otherBoard);

  /* Copy constructor. Creates the board array and then calls the assignment
     operator to copy the contents of otherBoard to this. */
  ChessBoard(ChessBoard const& otherBoard);
  
  // ---------- Checker functions ----------------------------------------------

  /* Checks if a Piece pointer in the board array is pointing to nullptr
     or not. The input Square corresponds to the cell in the array
     that is checked. */
  bool isPieceThere(Square square) const;

  /* Checks if the Piece pointer at the input square is pointing to a Piece 
     which is the same colour as the opponentColour input. */
  bool isOpponentPieceThere(Square square, Player opponentColour) const;

  /* Checks if a move from sourceSquare to destinationSquare is legal, 
     i.e. that it doesn't move the player into check. This function does 
     not check if the move follows the rules of how the Piece itself can 
     move. */
  bool isMoveLegal(Square sourceSquare, Square destinationSquare);
  
  // ---------- Other functions ------------------------------------------------

  /* Clears the board, sets the player to White and adds al the pieces to the
     board in the correct starting positions. */
  void resetBoard();

  /* Allows a move from sourceSquare to destinationSquare to be made as long
     as it is in line with the rules of chess. If it is not, it outputs
     an informative error message. If it is, it outputs a message stating the 
     move and if a piece has been taken. It then checks if the opponent is
     in check, checkmate and stalemate. If the game is not over, it swaps
     the player over. 
     sourceSquare and destinationSquare must be in rank and file notation, 
     where the rank is between 1-8 and the file is between A-H. For example:
     "E2".
     If "W" or "B" is input as the sourceSquare, the castle version of this
     function is called from within this function. */
  void submitMove(std::string sourceSquare, std::string destinationSquare);

  /* Allows a player to castle as long as it is in line with the rules of
     chess. If the move is not allowed, the function outputs an informative
     error message. If it is allowed, the function makes the move and 
     checks if the opponent is in check, checkmate and stalemate. If the game
     is not over, it swaps the player over. 
     There are four possible inputs to this function:
     playerColour = 'B' for Black or 'W' for White,
     castleCode = "O-O" for kingside castle, or "O-O-O" for queenside castle.
     These codes were chosen to be in line with standard chess notation. */
  void submitMove(char playerColour, std::string castleCode);
  
private:
  Piece*** board;
  Player player = White;
  
  // ---------- Helper functions -----------------------------------------------

  /* Puts all the Pieces in the correct squares of the board array*/
  void setUpBoard();

  /* Sets a pointer in the board array to point at the same object that the
     piece input points to. The location of the pointer is given by the square
     input, which is a string in rank and file form, e.g. "E2". */
  void putPieceOnBoard(Piece* piece, std::string square);

  /* Removes all the Pieces from the board. Does not delete the board itself. */
  void clearBoard();

  /* Changes the player over. */
  void swapPlayer();

  /* Moves a piece from sourceSquare to destinationSquare. If there was a 
     piece on the destinationSquare then makeMove returns a string containing
     the name of the piece. If there wasn't a piece there it returns an empty
     string. */
  std::string makeMove(Square sourceSquare, Square destinationSquare);

  // ---------- Checker functions ----------------------------------------------

  /* Checks if player is in check by iterating over each opponent piece and
     checking whether they can move to take the King. */
  bool isPlayerInCheck(Player p) const;

  /* Check if the King has any legal moves. If not, checks how many pieces
     threaten the King, and if it is possible to take or block them. */
  bool isPlayerInCheckmate(Player p);

  /* Checks if it is possible to take the threatening piece with the 
     defending piece. If not, checks if the defending piece can move to
     block the threatening piece's path to the King. 
     defender, threat and king are the locations of the defending piece,
     the threatening piece and the king.*/
  bool isAbleToTakeOrBlock(Square defender, Square threat, Square king);

  /* Goes through each piece on the board and checks if it's colour matches
     the player. If yes, check if the piece has any legal moves. */
  bool isPlayerInStalemate(Player p);

  /* Checks if the opponent is in check, if yes then it checks for checkmate.
     Otherwise it checks for stalemate. It outputs an informative message
     if any of these are true. It returns false if the opponent is in 
     checkmate or stalemate, and true otherwise. */
  bool isGameContinuing();

  // ---------- Getter functions -----------------------------------------------

  /* Returns the square that the input player's King starts on. */
  Square getKingStartSquare(Player player);

  /* Returns the square that the input player's kingside Rook starts on. */
  Square getKingsideRookStartSquare(Player player);

  /* Returns the square that the input player's queenside Rook starts on. */
  Square getQueensideRookStartSquare(Player player);

  /* Returns the current position of p's King. If it is not on the board
     then it throws the OffBoardError exception. */
  Square getKingPosition(Player p) const;

  /* Returns a pointer to the Piece on the input square. */
  Piece* getPiece(Square square) const;
};

#endif
