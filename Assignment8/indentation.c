/*
Compile: make indentation
Run: ./indentation
Compile & run: make indentation && ./indentation
*/
#include "base.h"

int indentation(char * s) {
    require_not_null(s);
    // todo
    int count = 0;
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == ' ') {
            count++;
            i++;
        } else if (s[i] == '\t') {
            return -1;
        } else {
            break;
        }
    }
    return count;
}

char * left_trim(char * s) {
    require_not_null(s);
    // todo
    int indent = indentation(s);
    if (indent == -1) {
        return "";
    }
    return s + indent;
}

char * extract_comment(char * s) {
    require_not_null(s);
    // todo
    char * p = s;
    while (*p != '\0') {
        if (*p == '/' && *(p + 1) == '/') {
            p += 2;
            return left_trim(p);
        }
        p++;
    }
    return "";
}

void indentation_test(void) {
    test_equal_i(indentation(""), 0);
    test_equal_i(indentation(" "), 1);
    test_equal_i(indentation("x"), 0);
    test_equal_i(indentation("\t"), -1); // error
    test_equal_i(indentation("  "), 2);
    test_equal_i(indentation("x "), 0);
    test_equal_i(indentation("\t "), -1); // error
    test_equal_i(indentation(" x"), 1);
    test_equal_i(indentation("xy"), 0);
    test_equal_i(indentation("\tx"), -1); // error
    test_equal_i(indentation(" \t"), -1); // error
    test_equal_i(indentation("  \t"), -1); // error
    test_equal_i(indentation("x\t"), 0);
    test_equal_i(indentation("\t\t"), -1); // error
    test_equal_i(indentation("    \tx"), -1); // error
    test_equal_i(indentation("    \t x"), -1); // error
    test_equal_i(indentation("xy \t"), 0);
    test_equal_i(indentation(" xyz \t"), 1);
    test_equal_i(indentation("  abcd \t"), 2);
    test_equal_i(indentation("    a \t"), 4);
    test_equal_i(indentation("  "), 2);
    test_equal_i(indentation("    "), 4);
    test_equal_i(indentation("    hello \t "), 4);
}

void left_trim_test(void) {
    test_equal_s(left_trim("   sample  "), "sample  ");
    test_equal_s(left_trim("Hello World"), "Hello World");
    test_equal_s(left_trim("    hello"), "hello");
    test_equal_s(left_trim("  Hello World"), "Hello World");
    test_equal_s(left_trim("\t\tHello"), ""); // error
    test_equal_s(left_trim("    \tHello"), ""); // error
}

void extract_comment_test(void) {
    test_equal_s(extract_comment("int i = 4/2;"), "");
    test_equal_s(extract_comment("int i = 0; // a new integer"), "a new integer");
    test_equal_s(extract_comment("   double f = 0.0; //   a new double"), "a new double");
    test_equal_s(extract_comment("  bool b = false; //a new bool"), "a new bool");
    test_equal_s(extract_comment("  bool b = false; //a new bool  "), "a new bool  ");
    test_equal_s(extract_comment("  bool b = false; //"), "");
    test_equal_s(extract_comment("int i = 0;"), "");
}

int main(void) {
    indentation_test();
    left_trim_test();
    extract_comment_test();
    return 0;
}
