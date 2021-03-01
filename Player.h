#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

/* The player enumeration represents the two sides in a chess game: Black
   and White. */

enum Player { White, Black };

/* This function allows a Player enumerator to be output to the output 
   stream specified. The output is either the string "Black" or "White"
   corresponding to the two enumerator values. */
std::ostream& operator<<(std::ostream& os, const Player& player);

/* This function returns the opposite enumerator to the input one, i.e.
   !White returns Black and !Black returns White. */
Player operator!(const Player player);

#endif
