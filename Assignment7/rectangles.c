#include "base.h"

typedef struct draw_options_s {
    bool has_border;
    String fill_pattern;
} DrawOptions;

typedef struct rectangle_s {
    int x;
    int y;
    int w;
    int h;

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
    require("Die x Koordinate muss positiv sein", x >= 0);
    require("Die y Koordiante muss positiv sein", y >= 0);
    require("Die Breite muss positiv sein", w >= 0);
    require("Die Hoehe muss positiv sein.", h >= 0);

    return (Rectangle){
        .x = x,
        .y = y,
        .w = w,
        .h = h,
    };
}

bool intersects(Rectangle a, Rectangle b) {
    int a_right = a.x + a.w;
    int a_bottom = a.y + a.h;
    int b_right = b.x + b.w;
    int b_bottom = b.y + b.h;

    return !(a_right <= b.x || a.x >= b_right || a_bottom <= b.y || a.y >= b_bottom);
}

void print_rectangle(Rectangle rect, DrawOptions options) {

    for (int i = 0; i < rect.y; i++) {
        println("");
    }
    
    if (options.has_border) {

        for (int i = 0; i < rect.x; i++) {
            prints(" ");
        }
        prints("+");
        for (int i = 0; i < rect.w - 2; i++) {
            prints("-");
        }
        printsln("+");

        int fill_length = s_length(options.fill_pattern);
        int fill_index = 0;
        
        for (int row = 0; row < rect.h - 2; row++) {

            for (int i = 0; i < rect.x; i++) {
                prints(" ");
            }
            prints("|");
            

            for (int col = 0; col < rect.w - 2; col++) {
                char c = s_get(options.fill_pattern, fill_index % fill_length);
                printc(c);
                fill_index++;
            }
            
            printsln("|");
        }
        
        for (int i = 0; i < rect.x; i++) {
            prints(" ");
        }
        prints("+");
        for (int i = 0; i < rect.w - 2; i++) {
            prints("-");
        }
        printsln("+");
        
    } else {

        for (int row = 0; row < rect.h; row++) {

            for (int i = 0; i < rect.x; i++) {
                prints(" ");
            }
            
            for (int col = 0; col < rect.w; col++) {
                prints(options.fill_pattern);
            }
            
            println("");
        }
    }
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
