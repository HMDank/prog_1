/*
Compile: make digit_sum
Run: ./digit_sum
make digit_sum && ./digit_sum
*/

#include "base.h"

unsigned get_int_length(unsigned number) { // O(log10(n))
  int count = 0;
  if (number == 0) {
    count = 1;
  } else {
    do {
      number /= 10;
      ++count;
    } while (number != 0);
  }
  return count;
}

int digit_sum(unsigned number, bool alternating) {
  int sum = 0;
  unsigned temp = number;
  int base = 1;
  unsigned length = get_int_length(temp);
  // generate base to get first digit (else we'd have to do 2 ifs, and that
  // looks ugly af)
  for (int times = length; times > 1; times--)
    base *= 10;

  for (unsigned position = 1; position <= length; ++position) {
    int digit = temp / base;
    if (alternating) {
      if (position % 2 == 0)
        sum -= digit;
      else
        sum += digit;
    } else {
      sum += digit;
    }
    temp = temp % base;
    if (base > 1)
      base /= 10;
  }
  return sum;
}

bool divisible_by_eleven(unsigned number) {
  // TODO
  return false;
}

void digit_sum_test() {
  // TODO
  test_equal_i(digit_sum(10, false), 1);
  test_equal_i(digit_sum(333, false), 9);
  test_equal_i(digit_sum(123, false), 6);
  test_equal_i(digit_sum(10, true), 1);
  test_equal_i(digit_sum(333, true), 3);
  test_equal_i(digit_sum(151, true), -3);

  // TODO
  test_equal_i(divisible_by_eleven(12), false);
  test_equal_i(divisible_by_eleven(11), true);
}

int main(void) {
  digit_sum_test();
  return 0;
}
