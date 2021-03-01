/* This file contains the member functions and friend functions of the
   Square class. */

#include "Square.h"
#include "constants.h"
#include <string>
#include "errors.h"

using namespace std;

// ---------- Contructors, destructors and operator overloads ----------------

Square::Square() {}

Square::Square(string rankAndFile) {
  if (!isOnBoard(rankAndFile)) {
    throw OffBoardError{rankAndFile};
  }
  rankIndex = static_cast<int>(rankAndFile[RANK_INDEX] - ASCII_ONE);
  fileIndex = static_cast<int>(rankAndFile[FILE_INDEX] - ASCII_A);
}

Square::Square(int rankIndex, int fileIndex) : rankIndex(rankIndex),
					       fileIndex(fileIndex) {
  if (!this->isOnBoard()) {
    throw OffBoardError{};
  }
}

Square::~Square() {}

ostream& operator<<(ostream& os, Square const& square) {
  char fileChar = static_cast<char>(square.fileIndex + ASCII_A);
  char rankChar = static_cast<char>(square.rankIndex + ASCII_ONE);
  os << fileChar << rankChar;
  return os;
}

bool Square::operator==(Square const& otherSquare) const {
  return (this->rankIndex == otherSquare.rankIndex &&
	  this->fileIndex == otherSquare.fileIndex);
}

// ---------- Getter functions -----------------------------------------------

int Square::getRank() const {
  return rankIndex;
}

int Square::getFile() const {
  return fileIndex;
}

// ---------- Checker functions ----------------------------------------------

bool Square::isOnBoard() const {
  bool isRankInRange = (rankIndex >= MIN_RANK && rankIndex <= MAX_RANK);
  bool isFileInRange = (fileIndex >= MIN_FILE && fileIndex <= MAX_FILE);
  return (isRankInRange && isFileInRange);
}

bool Square::isOnBoard(string moveInput) const {
  bool isCorrectLength = (moveInput.length() == 2);
  bool isCorrectRank = (moveInput[1] >= ASCII_ONE &&
			moveInput[1] <= ASCII_EIGHT);
  bool isCorrectFile = (moveInput[0] >= ASCII_A &&
			moveInput[0] <= ASCII_H);

  return (isCorrectLength &&
	  isCorrectRank &&
	  isCorrectFile);
}


