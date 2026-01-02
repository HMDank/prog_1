/*
    Compile: make wolf_goat_cabbage
    Run: ./wolf_goat_cabbage
    make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"

// Represents a single list node. The value is dynamically allocated. The node
// is the owner of the value and has to free it when itself is released.
struct Node {
  String value;      // dynamically allocated string, release memory!
  struct Node *next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node *new_node(String value, Node *next) {
  Node *node = xcalloc(1, sizeof(Node));
  node->value = s_copy(value); // s_copy performs dynamic allocation
  node->next = next;
  return node;
}

// Prints the components of the given list.
void print_list(Node *list) {
  if (list == NULL) {
    printf("[]");
  } else {
    printf("[%s", list->value);
    for (Node *n = list->next; n != NULL; n = n->next) {
      printf(" %s", n->value);
    }
    printf("]");
  }
}

// Print list followed by a newline.
void println_list(Node *list) {
  print_list(list);
  printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node *list) {
  // TODO: 3a)
  // (there will be memory leaks if this function is not yet implemented)
}

bool test_equal_lists(int line, Node *list1, Node *list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
  Node *list1 = NULL;
  Node *list2 = NULL;
  test_equal_lists(__LINE__, list1, list2);
  list1 = new_node("hello", NULL);
  list2 = list1;
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  list1 = new_node("hello", NULL);
  list2 = new_node("hello", NULL);
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
  list1 = new_node("hello", NULL);
  list2 = new_node("you", NULL);
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
  list1 = new_node("first", new_node("second", NULL));
  list2 = new_node("first", new_node("second", NULL));
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
  list1 = new_node("first", new_node("second", NULL));
  list2 = new_node("first", new_node("hello", NULL));
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
  list1 = new_node("first", new_node("second", NULL));
  list2 = new_node("first", new_node("second", new_node("third", NULL)));
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
  list1 = new_node("first", new_node("second", new_node("third", NULL)));
  list2 = new_node("first", new_node("second", NULL));
  test_equal_lists(__LINE__, list1, list2);
  free_list(list1);
  free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node *list1, Node *list2) {
  // TODO: 3b)
  return false;
}

int length_list(Node *list);

// Example calls for length_list (below).
void length_list_test(void) {
  // TODO: 3c)
}

// Number of elements of the list.
int length_list(Node *list) {
  int n = 0;
  for (Node *node = list; node != NULL; node = node->next)
    n++;
  return n;
}

int index_list(Node *list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
  // TODO: 3d)
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node *list, String s) {
  // TODO: 3d)
  return -1;
}

// Check whether list contains s.
bool contains_list(Node *list, String s) { return index_list(list, s) >= 0; }

Node *remove_list(Node *list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
  // TODO: 3e)
}

// Remove element at position index from list. The element at index has to be
// deleted.
Node *remove_list(Node *list, int index) {
  // TODO: 3e)
  return list;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank.
// We don't care for the transition (boat crossing the river).
enum Position { LEFT, RIGHT };

// The data that represents the state of the puzzle.
typedef struct {
  // List of objects on the left river bank.
  Node *left;

  // List of objects on the right river bank.
  Node *right;

  // List of objects in the boat. The boat has a capacity of one object only.
  Node *boat;

  // Current boat position.
  enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
  return (Puzzle){new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))),
                  NULL, NULL, LEFT};
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle *p) {
  print_list(p->left);
  if (p->position == RIGHT)
    prints("     ");
  print_list(p->boat);
  if (p->position == LEFT)
    prints("     ");
  println_list(p->right);
}

// Release memory and quit.
void finish_puzzle(Puzzle *p) {
  free_list(p->left);
  free_list(p->right);
  free_list(p->boat);
  exit(0);
}

void evaluate_puzzle(Puzzle *p) {
  // TODO: 4a)
}

void play_puzzle(Puzzle *p) {
  print_puzzle(p);
  // TODO: 4b)
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
  report_memory_leaks(true); // TODO: 2c)

  test_equal_lists_test();
  length_list_test();
  index_list_test();
  remove_list_test();

  // Puzzle p = make_puzzle();
  // play_puzzle(&p);
  return 0;
}
