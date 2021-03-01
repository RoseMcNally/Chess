/* This file contains the operator overloads for the Player enumeration. */

#include "Player.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Player& player) {
  os << ((player == White) ? "White" : "Black");
  return os;
}

Player operator!(const Player player) {
  return ((player == White) ? Black : White);
}
