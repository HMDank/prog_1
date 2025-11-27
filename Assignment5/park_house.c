/*
Compile: make park_house
Run: ./park_house
make park_house && ./park_house
*/

#include "base.h"

/* Design a function that returns the state of a park house given the number
of free parking spots */

typedef enum ParkHouseState {
  VOLL,
  FAST_VOLL,
  FREI,
} ParkHouseState;

ParkHouseState det_park_house_state(int free_spots);

String print_park_house_state(ParkHouseState state);

static void det_park_house_state_test() {
  // a) TODO
  test_equal_i(det_park_house_state(0), VOLL);
  test_equal_i(det_park_house_state(1), FAST_VOLL);
  test_equal_i(det_park_house_state(9), FAST_VOLL);
  test_equal_i(det_park_house_state(10), FREI);
  test_equal_i(det_park_house_state(21), FREI);
}
// a) TODO
ParkHouseState det_park_house_state(int free_spots) {
  if (free_spots == 0) {
    return VOLL;
  } else if (free_spots < 10) {
    return FAST_VOLL;
  }
  return FREI;
}

// b) TODO
String print_park_house_state(ParkHouseState state) {
  if (state == VOLL) {
    return "The Parkhaus is full. Maybe ask the building nextdoor instead?";
  } else if (state == FAST_VOLL) {
    return "The Parkhaus is almost full. Be quick. Like no seriously. Quick.";
  } else if (state == FREI) {
    return "The Parkhaus is free. Feel free to park here! :>";
  }
  return "Invalid state";
}

void aufgabe_2c() {
  // 2c
  int free_spots = -1;
  while (free_spots < 0) {
    prints("Free parking spots left: ");
    free_spots = i_input();
    if (free_spots < 0) {
      printsln("Invalid input. Please enter a non-negative integer.");
    }
  }
  printsln(print_park_house_state(det_park_house_state(free_spots)));
}

int main(void) {
  det_park_house_state_test();
  printsln(print_park_house_state(det_park_house_state(0)));
  printsln(print_park_house_state(det_park_house_state(8)));
  printsln(print_park_house_state(det_park_house_state(21)));

  aufgabe_2c();
  return 0;
}
