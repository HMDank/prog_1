#include "base.h"

typedef struct draw_options_s {
    bool has_border;
    String fill_pattern;
} DrawOptions;

typedef struct rectangle_s {
    // todo
} Rectangle;

/* Gibt ein DrawOptions Struct zurück, das dafür sorgt dass Rechtecke nur durch
 * Rauten und ohne Rahmen skizziert werden.
 */
DrawOptions make_draw_options_flat() {
    return (DrawOptions){
        .has_border = false,
        .fill_pattern = "#",
    };
}

/* Gibt ein DrawOptions Struct zurück, das dafür sorgt dass Rechtecke mit einem
 * Rahmen skizziert werden. Die Füllung des Rechtecks wird durch den String
 * "fill" bestimmt, der ständig wiederholend in das Rechteck geschrieben wird.
 */
DrawOptions make_draw_options_fill(String fill) {
    require("fill is a non-empty string", s_length(fill) > 0);

    return (DrawOptions){
        .has_border = true,
        .fill_pattern = fill,
    };
}

DrawOptions make_draw_options_range(char from, char to) {
    // todo
}

Rectangle make_rectangle(int x, int y, int w, int h) {
    // todo
}

bool intersects(Rectangle a, Rectangle b) {
    // todo
}

void print_rectangle(Rectangle rect, DrawOptions options) {
    // todo
}

void test_intersects(void) {
    test_equal_i(intersects(
        make_rectangle(0, 0, 10, 10),
        make_rectangle(32, 32, 10, 10)
    ), false);

    test_equal_i(intersects(
        make_rectangle(100, 100, 32, 16),
        make_rectangle(50, 32, 50, 10)
    ), false);

    test_equal_i(intersects(
        make_rectangle(50, 32, 50, 10),
        make_rectangle(100, 100, 32, 16)
    ), false);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(16, 16, 4, 4)
    ), true);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(8, 20, 32, 4)
    ), true);

    test_equal_i(intersects(
        make_rectangle(16, 16, 16, 16),
        make_rectangle(20, 8, 4, 32)
    ), true);
}

int main(void) {
    test_intersects();

    print_rectangle(make_rectangle(0, 0, 9, 5), make_draw_options_fill(" "));
    puts("===");
    print_rectangle(make_rectangle(3, 3, 10, 5), make_draw_options_fill("123"));
    puts("===");
    print_rectangle(make_rectangle(5, 2, 4, 6), make_draw_options_fill(":_:"));
    puts("===");
    print_rectangle(make_rectangle(1, 2, 4, 4), make_draw_options_flat());

    return 0;
}

/* Beispielausgaben:

print_rectangle(make_rectangle(0, 0, 9, 5), make_draw_options_fill(" "));
+-------+
|       |
|       |
|       |
+-------+

print_rectangle(make_rectangle(3, 3, 10, 5), make_draw_options_fill("123"));



   +--------+
   |12312312|
   |31231231|
   |23123123|
   +--------+

print_rectangle(make_rectangle(5, 2, 4, 6), make_draw_options_fill(":_:"));


     +--+
     |:_|
     |::|
     |_:|
     |:_|
     +--+

print_rectangle(make_rectangle(1, 2, 4, 4), make_draw_options_flat());


 ####
 ####
 ####
 ####

*/
