/* This file contains the member function definitions for the derived exception 
   class OffBoardError in "errors.h". */

#include "errors.h"
#include <exception>
#include <string>

using namespace std;

// ---------- OffBoardError ----------------------------------------------------

OffBoardError::OffBoardError() noexcept {}

OffBoardError::OffBoardError(string const& square) noexcept {
  explanation = square + " is not on the board!";
}

const char* OffBoardError::what() const noexcept {
  return explanation.c_str();
}
