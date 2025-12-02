/*
Compile: make loops
Run: ./loops
make loops && ./loops
*/

#include "base.h"

void loops_a(int n) {
  for (int row = 1; row <= n; row++) {
    for (int col = 1; col <= row; col++) {
      printf("%d ", col);
    }
    printf("\n");
  }
}

void loops_b(int n) {
  for (int row = 1; row <= n; row++) {
    if (n - row > 0) {
      printf("%*c", 2 * (n - row), ' ');
    }
    for (int col = row; col >= 1; col--) {
      printf("%d ", col);
    }
    printf("\n");
  }
}

void loops_c(int n) {
  for (int row = 1; row <= n; row++) {
    if (n - row > 0) {
      printf("%*c", (n - row), ' ');
    }
    for (int col = row; col >= 1; col--) {
      printf("%d ", col);
    }
    printf("\n");
  }
}

void loops_d(int n) {
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (col == row || col == n - row - 1) {
        if (row < (n - 1) / 2) {
          printf("%d  ", row);
        } else
          printf("%d  ", n - row - 1);
      } else
        printf("   ");
    }
    printf("\n");
  }
}
// todo: implement helper functions for loops_e (recommended) (no u)
void loops_e(int n) {
  for (int row = 0; row < n; row++) {
    if (n - row - 1 > 0) {
      printf("%*s", (n - row - 1), " ");
    } // create an empty traingle at the start
    if (row == 0 || row == n - 1) { // first and last line
      for (int col = 0; col < 2 * n;
           col++) { // 2n because the width is twice as many characters
        if (col == 0 || col == 2 * n - 1) { // first and last column
          printf("%s", "+");
        } else
          printf("%s", "-");
      }
    } else { // columns inbetweens
      printf("%c%*c", '/', (2 * n - 1), '/');
    }
    printf("\n");
  }
}

// todo: implement helper functions for loops_f (recommended)

void loops_f(int n) {
  for (int row = 0; row < n; row++) {

    if (n - row - 1 > 0) {
      printf("%*s", (n - row - 1), " ");
    } // create an empty traingle at the start

    if (row == 0 || row == n - 1) {           // first and last line
      for (int col = 0; col < 2 * n; col++) { // width is 2n characters
        if (col == 0 || col == 2 * n - 1) {   // first and last column
          printf("%s", "+");
        } else
          printf("%s", "-");
      }
    } else { // columns inbetweens
      printf("%c", '/');
      for (int count = 0; count < n - 1; count++) {
        printf("%d ",
               (count + (row - 1) * (n - 1)) % 10); // trial and error :DDD
      }
      printf("%c", '/');
    }
    printf("\n");
  }
}

int main(void) {
  //   loops_a(5);
  //   loops_b(5);
  //   loops_c(5);
  //   loops_d(5);
  //   loops_a(9);
  //   loops_b(9);
  //   loops_c(9);
  //   loops_d(9);
  //   loops_e(3);
  //   loops_e(4);
  //   loops_e(5);
  //   loops_e(9);
  //   loops_e(12);
  loops_f(5);
  loops_f(9);
  return 0;
}
