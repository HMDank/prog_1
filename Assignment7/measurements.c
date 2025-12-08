#include "base.h"

typedef struct statistics_s {
    // todo
} Statistics;

Statistics make_statistics() {
    // todo
}

void print_statistics(Statistics s) {
    // todo
}

Statistics compute_statistics(String table) {
    // todo
}

int main(void) {
    String table = s_read_file("measurements.txt");
    Statistics statistics = compute_statistics(table);
    print_statistics(statistics);
    return 0;
}
