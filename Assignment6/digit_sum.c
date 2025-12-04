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

/**
 * Calculates the (alternating) sum of the digits of a given integer.
 *
 * @param number The integer whose digits will be summed.
 * @param alternating whether to calculate the sum or alternating sum
 * @return The sum of the digits of the input integer.
 */
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
/**
 * checks whether the number is divisible by 11 or not
 *
 * @param number the number in question.
 * @return whether it's divisible by 11 or not.
 */
bool divisible_by_eleven(unsigned number) {
  int alternating_sum = digit_sum(number, true);
  if (alternating_sum < 0)
    alternating_sum = -alternating_sum;
  if (alternating_sum == 0)
    return true;
  if (alternating_sum < 11)
    return false;
  return divisible_by_eleven(alternating_sum);
} // TODO: Is this doable with DP?

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
  test_equal_i(divisible_by_eleven(121), true);
}

int main(void) {
  digit_sum_test();
  return 0;
}
