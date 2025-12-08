#include "base.h"

const String permutation = "SGEMFVYZIDPBUKHARNXQWOLJTC";
// real stuffs             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// encrypt the input
String encrypt(String input) {
  // TODO
  String output = s_copy(input);
  int length = s_length(input);
  for (int index = 0; index < length; index++) {
    char current_char = input[index];
    if (isalpha(current_char)) {
      int position = current_char - 'A';
      output[index] = permutation[position];
    }
  }
  return output;
}

int index_of(String s, char c) {
  // TODO
  int len = s_length(s);
  for (int i = 0; i < len; i++) {
    if (s[i] == c)
      return i;
  }
  return -1;
}

String decrypt(String input) {
  // TODO
  String output = s_copy(input);
  int length = s_length(input);
  for (int index = 0; index < length; index++) {
    char current_char = input[index];
    if (isalpha(current_char)) {
      int position = index_of(permutation, current_char);
      if (position >= 0)
        output[index] = 'A' + position;
    }
  }
  return output;
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
  printsln(
      decrypt("VNSKC DSYQ IU PHUABFQQ OFNLSZNBHXQFK QSJI RWFN MWNEZ GSTFNK."));
} // ich verstehe die Referrenz nicht (?)
