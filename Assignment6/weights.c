#include <stdio.h>
#include "base.h"

typedef enum unit_e {
    G,
    KG,
    T,
    LB
} Unit;
typedef struct weight_s {
    double amount;
    Unit unit;
} Weight;
Weight make_weight(double amount, Unit unit) {
    Weight w;
    w.amount = amount;
    w.unit = unit;
    return w;
}
bool test_within_weight(int line, Weight a, Weight e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.unit, e.unit);
    return x && u;
}
void print_weight(Weight w) {
    printf("%.3f ", w.amount);
    if (w.unit == G) {
        printf("g\n");
    } else if (w.unit == KG) {
        printf("kg\n");
    } else if (w.unit == T) {
        printf("t\n");
    } else if (w.unit == LB) {
        printf("lb\n");
    }
}
void print_weight_test() {
    print_weight(make_weight(1234, G));
    print_weight(make_weight(4.749, KG));
    print_weight(make_weight(3.1001, T));
    print_weight(make_weight(5.40006, LB));
}
Weight to_unit(Weight w, Unit target_unit) {
    double in_kg;
    if (w.unit == G) {
        in_kg = w.amount / 1000.0;
    } else if (w.unit == KG) {
        in_kg = w.amount;
    } else if (w.unit == T) {
        in_kg = w.amount * 1000.0;
    } else if (w.unit == LB) {
        in_kg = w.amount * 0.45359237;
    }
    double result_amount;
    if (target_unit == G) {
        result_amount = in_kg * 1000.0;
    } else if (target_unit == KG) {
        result_amount = in_kg;
    } else if (target_unit == T) {
        result_amount = in_kg / 1000.0;
    } else if (target_unit == LB) {
        result_amount = in_kg / 0.45359237;
    }
    return make_weight(result_amount, target_unit);
}
void to_unit_test(void) {
    test_within_weight(__LINE__, to_unit(make_weight(1000, G), KG), make_weight(1, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(2, KG), G), make_weight(2000, G), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, T), KG), make_weight(1000, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, LB), KG), make_weight(0.45359237, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, KG), LB), make_weight(2.20462, LB), 1e-3);
    test_within_weight(__LINE__, to_unit(make_weight(1000000, G), T), make_weight(1, T), 1e-6);
}
int compare(Weight w, Weight v) {
    Weight w_in_kg = to_unit(w, KG);
    Weight v_in_kg = to_unit(v, KG);
    if (w_in_kg.amount < v_in_kg.amount) {
        return -1;
    } else if (w_in_kg.amount > v_in_kg.amount) {
        return 1;
    } else {
        return 0;
    }
}
void compare_test(void) {
    test_equal_i(compare(make_weight(1000, G), make_weight(1, KG)), 0);
    test_equal_i(compare(make_weight(500, G), make_weight(1, KG)), -1);
    test_equal_i(compare(make_weight(2, KG), make_weight(1000, G)), 1);
    test_equal_i(compare(make_weight(1, T), make_weight(1000, KG)), 0);
    test_equal_i(compare(make_weight(1, LB), make_weight(1, KG)), -1);
    test_equal_i(compare(make_weight(100, G), make_weight(1, LB)), -1);
}
int main(void) {
    print_weight_test();
    to_unit_test();
    compare_test();
    return 0;
}