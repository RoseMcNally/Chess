#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

// ---------- OffBoardError ----------------------------------------------------

class OffBoardError : public std::exception {
public:
  /* Constructs OffBoardError object with an uninitialised explanation string */
  OffBoardError() noexcept;

  /* Constructs OffBoardError object with the explanation string initialised
     to: square + " is not on the board!". */
  OffBoardError(std::string const& square) noexcept;

  /* Returns a pointer to a c string containing the explanation message. */
  const char* what() const noexcept override;
private:
  std::string explanation;
};

#endif
