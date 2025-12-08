#include "base.h"

const String permutation = "SGEMFVYZIDPBUKHARNXQWOLJTC";

String encrypt(String input) {
    // TODO
    return s_copy(input);
}

int index_of(String s, char c) {
    // TODO
    return -1;
}

String decrypt(String input) {
    // TODO
    return s_copy(input);
}

void test_identity(String s) {
    assert("encrypted text must differ from input", !s_equals(s, encrypt(s)));
    test_equal_s(s, decrypt(encrypt(s)));
}

int main(void) {
    test_identity("HELLO WORLD");
    test_identity("SOME SUPER SECRET TEXT");
    test_identity("DOES QUOTATION CAUSE ISSUES? IT SHOULDN'T.");
    test_identity("BE SURE TO DRINK YOUR OVALTINE");

    printsln("The secret text says:");
    printsln(decrypt("VNSKC DSYQ IU PHUABFQQ OFNLSZNBHXQFK QSJI RWFN MWNEZ GSTFNK."));
}
