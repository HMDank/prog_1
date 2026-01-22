/*
    Compile: make parentheses
    Run: ./parentheses
    make parentheses && ./parentheses
*/
// shoutout to prog1lib/lecture_examples/stack.character
#include "base.h"

typedef struct {
  String text;
  int top;
  int size;
} Stack;

Stack *new_stack(int size) {
  Stack *stack = xmalloc(sizeof(Stack));
  stack->text = xmalloc(size * sizeof(char));
  stack->top = -1;
  stack->size = size;
  return stack;
}

void free_stack(Stack *stack) {
  free(stack->text);
  free(stack);
}

bool is_empty(Stack *stack) { return stack->top == -1; }

void push(Stack *stack, char character) {
  if (stack->top < stack->size - 1) {
    stack->text[++stack->top] = character;
  }
}

char pop(Stack *stack) {
  if (!is_empty(stack)) {
    return stack->text[stack->top--];
  }
  return '\0';
}

bool verify_parentheses(String text) {
  Stack *stack = new_stack(s_length(text));

  for (int index = 0; index < s_length(text); index++) {
    char character = text[index];

    if (character == '(' || character == '[' || character == '{' ||
        character == '<') {
      push(stack, character);
    }

    else if (character == ')' || character == ']' || character == '}' ||
             character == '>') {
      if (is_empty(stack)) { // aka no matching opening bracket.
        free_stack(stack);
        return false;
      }

      char top = pop(stack);
      if ((character == ')' && top != '(') ||
          (character == ']' && top != '[') ||
          (character == '}' && top != '{') ||
          (character == '>' && top != '<')) {
        free_stack(stack);
        return false;
      }
    }
  }
  bool result = is_empty(stack);
  free_stack(stack);
  return result;
}

int main(void) {
  report_memory_leaks(true);

  test_equal_i(verify_parentheses(""), true);
  test_equal_i(verify_parentheses("Hello World"), true);
  test_equal_i(verify_parentheses("()"), true);
  test_equal_i(verify_parentheses("<{[()]}>"), true);
  test_equal_i(verify_parentheses("<{[)]}>"), false);
  test_equal_i(verify_parentheses("( Test ) "), true);
  test_equal_i(verify_parentheses("(1+2)*[2+3+(1 + 6/5)]"), true);
  test_equal_i(
      verify_parentheses("(an unmatched left parenthesis creates an unresolved "
                         "tension that will stay with you all day"),
      false);
  test_equal_i(verify_parentheses("< [ > ]"), false);
  test_equal_i(verify_parentheses("<{[()]}"), false);
  test_equal_i(
      verify_parentheses(
          "(<<({[({<{<({<([[[<[{(<{(<{{<[{<{{{<<{([<<<{{[{<<[[(([{[[[([(({()}"
          "))"
          "])]]]}]))]]>>}]}}>>>])}>>}}}>}]>}}>)}>)}]>]]])>})>}>})]})>>)"),
      true);

  return 0;
}
