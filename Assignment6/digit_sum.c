/*
Compile: make digit_sum
Run: ./digit_sum
make digit_sum && ./digit_sum
*/

#include "base.h"

int digit_sum(unsigned number, bool alternating) {
    // TODO
    return 0;
}

bool divisible_by_eleven(unsigned number) {
    // TODO
    return false;
}

void digit_sum_test() {
    // TODO
    test_equal_i(digit_sum(10, false), 1);
    test_equal_i(digit_sum(333, false), 9);

    // TODO
    test_equal_i(divisible_by_eleven(12), false);
    test_equal_i(divisible_by_eleven(11), true);
}

int main(void) {
    digit_sum_test();
    return 0;
}
