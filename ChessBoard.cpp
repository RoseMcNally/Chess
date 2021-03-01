/* This file contains the member functions of the ChessBoard class. */

#include "ChessBoard.h"
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
#include "errors.h"
#include <iostream>
#include <string>

using namespace std;

// ---------- Contructors, destructors and operator overloads ------------------

ChessBoard::ChessBoard() {
  // Create 8x8 array of pointers to Piece objects
  board = new Piece**[BOARD_LENGTH];
  for (int i = 0; i < BOARD_LENGTH; i++) {
    board[i] = new Piece*[BOARD_WIDTH];
    for (int j = 0; j < BOARD_WIDTH; j++) {
      board[i][j] = nullptr;
    }
  }
  // Add Pieces
  setUpBoard();
}

ChessBoard::~ChessBoard() {
  // Delete all the Pieces and then the array of pointers
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      delete board[i][j];
    }
    delete[] board[i];
  }
  delete[] board;
}

ChessBoard& ChessBoard::operator=(ChessBoard const& otherBoard) {
  this->player = otherBoard.player;
  
  clearBoard();
  
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {

      // If there is a Piece on a square on the other board, create
      // a copy of the Piece with a reference to this board and put
      // it on the square on this board
      if (otherBoard.board[i][j] != nullptr) {
	Piece* otherPiece = otherBoard.board[i][j];
	auto* newPiece = otherPiece->copyPiece(*this); 
	this->board[i][j] = newPiece;
      }
      
    }
  }
  return *this;
}

ChessBoard::ChessBoard(ChessBoard const& otherBoard) {
  // Create 8x8 array of pointers to Piece objects
  board = new Piece**[BOARD_LENGTH];
  for (int i = 0; i < BOARD_LENGTH; i++) {
    board[i] = new Piece*[BOARD_WIDTH];
    for (int j = 0; j < BOARD_WIDTH; j++) {
      board[i][j] = nullptr;
    }
  }

  *this = otherBoard;
}

// ---------- Checker functions ------------------------------------------------

bool ChessBoard::isPieceThere(Square square) const {
  return (getPiece(square) != nullptr);
}

bool ChessBoard::isOpponentPieceThere(Square square,
				      Player opponentColour) const {
  if (getPiece(square) == nullptr) {
    return false;
  }
  return (getPiece(square)->getColour() == opponentColour);
}

bool ChessBoard::isMoveLegal(Square sourceSquare, Square destinationSquare) {
  // Create a copy of the current board, make the move and check whether
  // the player is in check as a result
  
  ChessBoard* copyBoard = new ChessBoard{*this};
  Player playerColour = getPiece(sourceSquare)->getColour();
  
  copyBoard->makeMove(sourceSquare, destinationSquare);
  
  if (copyBoard->isPlayerInCheck(playerColour)) {
    delete copyBoard;
    return false;
  }
  
  delete copyBoard;
  return true;
}

// ---------- Other functions --------------------------------------------------

void ChessBoard::resetBoard() {
  clearBoard();
  player = White;
  setUpBoard();
}

void ChessBoard::submitMove(string sourceSquare, string destinationSquare) {

  // Checks on input -------------------------------------------
  
  // If the first input is "W" or "B" call the castle version of submitMove()
  if (sourceSquare == "W" || sourceSquare == "B") {
    submitMove(static_cast<char>(sourceSquare[0]), destinationSquare);
    return;
  }

  Square source, destination;

  // If the inputs do not correspond to squares on the board, output
  // error message
  try {
    source = Square{sourceSquare};
    destination = Square{destinationSquare};
  } catch (OffBoardError const& e) {
    cerr << e.what() << endl;
    cerr << "Please enter a correct rank and file combination,\n";
    cerr << "or a colour and castle code. For example:\n";
    cerr << ">> chessboard.sumbitMove(\"E2\", \"E4\");\n";
    cerr << ">> chessboard.submitMove('B', \"O-O\");" << endl;
    return;
  }

  if (source == destination) {
    cout << "A piece cannot move to the square it's already on!" << endl;
    return;
  }
  
  if (!isPieceThere(source)) {
    cout << "There is no piece at position " << source << "!" << endl;
    return;
  }

  if (isOpponentPieceThere(source, !player)) {
    cout << "It is not " << !player << "'s turn to move!" << endl;
    return;
  }

  // Making move -----------------------------------------------

  Piece* piece = getPiece(source);

  // If the move is possible and legal, make the move, set the hasMoved
  // variable of the piece to true, output message and check the state of
  // the game (check/checkmate/stalemate)
  if (piece->isMovePossible(source, destination) &&
      isMoveLegal(source, destination)) {
    string opponentPiece = makeMove(source, destination);
    piece->setHasMoved(true);
    
    cout << player << "'s " << *piece << " moves from ";
    cout << source << " to " << destination;

    if (opponentPiece != "") {
      cout << " taking "  << !player << "'s " << opponentPiece;
    }
    cout << endl;
   
    if (isGameContinuing()) {
      swapPlayer();
    }
    
  } else {
    cerr << player << "'s " << *piece << " cannot move to ";
    cerr << destination << "!" << endl;
  }
}


// Function for castling
void ChessBoard::submitMove(char playerColour, std::string castleCode) {
  
  bool validInput = ((playerColour == 'W' || playerColour == 'B') &&
		     (castleCode == "O-O" || castleCode == "O-O-O"));
    
  if (!validInput) {
    cout << "Sorry, invalid input! Please enter a correct rank and file\n";
    cout << "combination, or a colour and castle code. For example:\n";
    cout << ">> chessboard.sumbitMove(\"E2\", \"E4\");\n";
    cout << ">> chessboard.submitMove('B', \"O-O\");" << endl;
    return;
  }

  bool isCorrectPlayer = ((this->player == White && playerColour == 'W') ||
			  (this->player == Black && playerColour == 'B'));
  
  if (!isCorrectPlayer) {
    cout << "It is not " << !player << "'s turn to move!" << endl;
    return;
  }

  // Find starting positions of King and Rook
  
  bool isKingside = (castleCode == "O-O");
  Square kingPosition = getKingStartSquare(player);
  Square rookPosition;
  if (isKingside) {
    rookPosition = getKingsideRookStartSquare(player);
  } else {
    rookPosition = getQueensideRookStartSquare(player);
  }

  Piece* king = getPiece(kingPosition);
  Piece* rook = getPiece(rookPosition);

  // Check if King and Rook have moved before
  
  if (king == nullptr ||
      king->getName() != "King" ||
      king->getColour() != player ||
      !king->isFirstMove()) {
    cout << player << " cannot castle, the King has moved previously" << endl;
    return;
  }

  if (rook == nullptr ||
      rook->getName() != "Rook" ||
      rook->getColour() != player ||
      !rook->isFirstMove()) {
    cout << player << " cannot castle, the Rook has moved previously" << endl;
    return;
  }

  // Check that the squares between the King and Rook are clear
  
  bool pathIsClear = true;
  int fileChange = rookPosition.getFile() - kingPosition.getFile();

  for (int i = 1; i < abs(fileChange); i++) {
    int fileStep = i * fileChange / abs(fileChange);
    Square pathSquare{kingPosition.getRank(),
		      kingPosition.getFile() + fileStep};
    pathIsClear = pathIsClear && !isPieceThere(pathSquare);
  }
  
  if (!pathIsClear) {
    cout << player << " cannot castle, the squares between the King" << endl;
    cout << "and the Rook are not clear" << endl;
    return;
  }

  // Check that the player is not in check
  
  if (isPlayerInCheck(player)) {
    cout << player << " cannot castle, the King is in check" << endl;
    return;
  }

  // Check that the player will not move through check
  
  int fileStep = fileChange / abs(fileChange);
  Square pathSquare{kingPosition.getRank(),
		    kingPosition.getFile() + fileStep};
  if (!isMoveLegal(kingPosition, pathSquare)) {
    cout << player << " cannot castle, the King would";
    cout << " pass through check" << endl;
    return;
  }

  // Check that the player will not move into check

  // King always moves two towards the Rook and Rook always ends
  // up on other side of King - one away from where King was originally
  Square kingDestination{kingPosition.getRank(),
                         kingPosition.getFile() + 2 * fileStep};
  Square rookDestination{rookPosition.getRank(),
			 kingPosition.getFile() + 1 * fileStep};
  
  if (!isMoveLegal(kingPosition, kingDestination)) {
    cout << player << " cannot castle, the King would move into check" << endl;
    return;
  }

  // Making move 
  
  makeMove(kingPosition, kingDestination);
  makeMove(rookPosition, rookDestination);

  king->setHasMoved(true);
  rook->setHasMoved(true);

  string side = (isKingside) ? "kingside" : "queenside";
  
  cout << player << " castles " << side << endl;
  
  if (isGameContinuing()) {
    swapPlayer();
  }
}

// ---------- Helper functions -------------------------------------------------

void ChessBoard::setUpBoard() {
  // Pawns
  for (int i = 0; i < BOARD_WIDTH; i++) {
    Piece* newPawn = new Pawn{White, *this};
    board[RANK_TWO][i] = newPawn;
  }
  for (int i = 0; i < BOARD_WIDTH; i++) {
    Piece* newPawn = new Pawn{Black, *this};
    board[RANK_SEVEN][i] = newPawn;
  }
  
  // Bishops
  Piece* newBishop = new Bishop{White, *this};
  putPieceOnBoard(newBishop, WHITE_QUEEN_BISHOP);
  newBishop = new Bishop{White, *this};
  putPieceOnBoard(newBishop, WHITE_KING_BISHOP);
  newBishop = new Bishop{Black, *this};
  putPieceOnBoard(newBishop, BLACK_QUEEN_BISHOP);
  newBishop = new Bishop{Black, *this};
  putPieceOnBoard(newBishop, BLACK_KING_BISHOP);

  // Knights
  Piece* newKnight = new Knight{White, *this};
  putPieceOnBoard(newKnight, WHITE_QUEEN_KNIGHT);
  newKnight = new Knight{White, *this};
  putPieceOnBoard(newKnight, WHITE_KING_KNIGHT);
  newKnight = new Knight{Black, *this};
  putPieceOnBoard(newKnight, BLACK_QUEEN_KNIGHT);
  newKnight = new Knight{Black, *this};
  putPieceOnBoard(newKnight, BLACK_KING_KNIGHT);

  // Rooks
  Piece* newRook = new Rook{White, *this};
  putPieceOnBoard(newRook, WHITE_QUEEN_ROOK);
  newRook = new Rook{White, *this};
  putPieceOnBoard(newRook, WHITE_KING_ROOK);
  newRook = new Rook{Black, *this};
  putPieceOnBoard(newRook, BLACK_QUEEN_ROOK);
  newRook = new Rook{Black, *this};
  putPieceOnBoard(newRook, BLACK_KING_ROOK);

  // Queens
  Piece* newQueen = new Queen{White, *this};
  putPieceOnBoard(newQueen, WHITE_QUEEN);
  newQueen = new Queen{Black, *this};
  putPieceOnBoard(newQueen, BLACK_QUEEN);

  // Kings
  Piece* newKing = new King{White, *this};
  putPieceOnBoard(newKing, WHITE_KING_START_SQUARE);
  newKing = new King{Black, *this};
  putPieceOnBoard(newKing, BLACK_KING_START_SQUARE);
  
  cout << "A new chess game is started!" << endl;
}

void ChessBoard::putPieceOnBoard(Piece* piece, string position) {
  try {
    Square square{position};
    int rank = square.getRank();
    int file = square.getFile();
    board[rank][file] = piece;
  } catch (OffBoardError const& e) {
    cerr << "You cannot place a piece there," << endl;
    cerr << e.what() << endl;
  }
}

void ChessBoard::clearBoard() {
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      delete this->board[i][j];
      this->board[i][j] = nullptr;
    }
  }
}

void ChessBoard::swapPlayer() {
  player = !player;
}

string ChessBoard::makeMove(Square sourceSquare, Square destinationSquare) {
  string opponentPiece;
  Piece* destination = getPiece(destinationSquare);

  int sourceRank = sourceSquare.getRank();
  int sourceFile = sourceSquare.getFile();
  int destinationRank = destinationSquare.getRank();
  int destinationFile = destinationSquare.getFile();
  
  if (destination != nullptr) {
    opponentPiece = destination->getName();
    delete destination;
  } else {
    opponentPiece = "";
  }
  board[destinationRank][destinationFile] = board[sourceRank][sourceFile];
  board[sourceRank][sourceFile] = nullptr;
  return opponentPiece;
}

// ---------- Checker functions ------------------------------------------------

bool ChessBoard::isPlayerInCheck(Player p) const {
  // For each square on the board, if there is an opponent piece there,
  // check if it is possible for the piece to take the king - if yes, then
  // the player is in check
  Square kingPosition = getKingPosition(p);
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] != nullptr && board[i][j]->getColour() == !p) {
	if (board[i][j]->isMovePossible(Square{i, j}, kingPosition)) {
	  return true;
	}
      }
    }
  }
  return false;
}

bool ChessBoard::isPlayerInCheckmate(Player p) {
  // Check if King has any legal moves
  Square kingPosition = getKingPosition(p);
  if (getPiece(kingPosition)->isAnyLegalMovePossible(kingPosition)) {
    return false;
  }

  // Search the board for Pieces that threaten the King
  Square threateningPiece;
  int threatCount = 0;
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] != nullptr && board[i][j]->getColour() == !p) {
	if (board[i][j]->isMovePossible(Square{i, j}, kingPosition)) {
	  threateningPiece = Square{i, j};	  
	  threatCount++;
	}
      }
    }
  }

  // If there are no threats, the player is not in checkmate
  // If there is more than one threatening piece, then the player
  // is in checkmate because it is not possible to block or take
  // more than one piece in a single go.
  if (threatCount == 0) {
    return false;
  }
  if (threatCount > 1) {
    return true;
  }

  // If there is one threatening piece, search the board for pieces
  // that can move to block or take it.
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] != nullptr && board[i][j]->getColour() == p) {
	Square defender = Square{i, j};
	if (isAbleToTakeOrBlock(defender, threateningPiece, kingPosition)) {
	  return false;
	}
      }
    }
  }
  	  
  return true;
}

bool ChessBoard::isAbleToTakeOrBlock(Square defender,
				     Square threat,
				     Square king) {
  int rankChange = king.getRank() - threat.getRank();
  int fileChange = king.getFile() - threat.getFile();

  // Check if it is possible to take the threatening piece
  if (getPiece(defender)->isMovePossible(defender, threat) &&
      isMoveLegal(defender, threat)) {
    return true;
  }

  // Check if the threatening piece is a Pawn or a Knight as
  // neither can be blocked
  if (getPiece(threat)->getName() == "Knight" ||
      getPiece(threat)->getName() == "Pawn") {
    return false;
  }

  // We know that the threatening piece can move to take the King,
  // and that it is either a Bishop, a Rook or a Queen, so it
  // is either moving along the diagonal or a rank or file
  bool isAlongDiagonal = (abs(rankChange) == abs(fileChange));
  int pathSteps;
  
  if (isAlongDiagonal) {
    pathSteps = abs(rankChange); // could equally be fileChange
  } else { // in this case it is moving along a rank or file
    // summing rank and file change is okay since one of the terms will be 0
    pathSteps = abs(rankChange + fileChange);
  }

  // Check if defender can move to any squares in the threatening piece's
  // path to the King - i.e. can the defender block it
  for (int i = 1; i < pathSteps; i++) {
    int rankStep = (rankChange == 0) ? 0 : i * rankChange / abs(rankChange);
    int fileStep = (fileChange == 0) ? 0 : i * fileChange / abs(fileChange);

    Square squareInPath = Square(threat.getRank() + rankStep,
				 threat.getFile() + fileStep);

    if (getPiece(defender)->isMovePossible(defender, squareInPath) &&
	isMoveLegal(defender, squareInPath)) {
      return true;
    }
  }

  return false;
}

bool ChessBoard::isPlayerInStalemate(Player p) {
  // For each of the player's pieces on the chessboard,
  // check if they have any legal moves
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] != nullptr && board[i][j]->getColour() == p) {
	Square s = Square{i, j};
	if (getPiece(s)->isAnyLegalMovePossible(s)) {
	  return false;
	}
      }
    }
  }
  return true;
}

bool ChessBoard::isGameContinuing() {
  if (isPlayerInCheck(!player)) {
    if (isPlayerInCheckmate(!player)) {
      cout << !player << " is in checkmate" << endl;
      return false;
    } else {
      cout << !player << " is in check" << endl;
      return true;
    }
  } else if (isPlayerInStalemate(!player)) {
    cout << !player << " is in stalemate" << endl;
    return false;
  }
  return true;
}

// ---------- Getter functions -------------------------------------------------

Square ChessBoard::getKingStartSquare(Player player) {
  if (player == White) {
    return Square{WHITE_KING_START_SQUARE};
  } else {
    return Square{BLACK_KING_START_SQUARE};
  }
}

Square ChessBoard::getKingsideRookStartSquare(Player player) {
  if (player == White) {
    return Square{WHITE_KING_ROOK};
  } else {
    return Square{BLACK_KING_ROOK};
  }
}

Square ChessBoard::getQueensideRookStartSquare(Player player) {
  if (player == White) {
    return Square{WHITE_QUEEN_ROOK};
  } else {
    return Square{BLACK_QUEEN_ROOK};
  }
}

Square ChessBoard::getKingPosition(Player p) const {
  for (int i = 0; i < BOARD_LENGTH; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (board[i][j] != nullptr &&
	  board[i][j]->getColour() == p &&
	  board[i][j]->getName() == "King") {
	return Square{i, j};
      }
    }
  }
  string colour = (p == White) ? "White" : "Black";
  string message = "The " + colour + " King";
  throw OffBoardError{message};
}

Piece* ChessBoard::getPiece(Square square) const {
  int rank = square.getRank();
  int file = square.getFile();
  return board[rank][file];
}
