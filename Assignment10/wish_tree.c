/*
    Compile: make wish_tree
    Run: ./wish_tree
    Compile & run: make wish_tree && ./wish_tree
*/

#include "base.h"

typedef struct Element Element;

void free_element(Element *element);

typedef struct Node {
  struct Node *next;
  char *value;
} Node;

/*
    Returns a pointer to a dynamically allocated node.
*/
Node *new_node(char *value, Node *next) {
  Node *node = xmalloc(sizeof(Node));
  node->next = next;
  node->value = s_copy(value);
  return node;
}

/*
    Releases the memory used by node.
*/
Node *free_node(Node *node) {
  Node *next = node->next;
  free(node->value);
  free(node);
  return next;
}

/*
    Returns the length of a list of nodes.
*/
int length(Node *node) {
  int count = 0;
  while (node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

/*
    Returns true if the list of nodes contains find.
*/
bool contains(Node *node, char *find) {
  while (node != NULL) {
    if (strcmp(node->value, find) == 0) {
      return true;
    }
    node = node->next;
  }
  return false;
}

/*
    A TreeNode has a left and right successor of type TreeNode. A successor
   TreeNode is a TreeNode or NULL

            TreeNode root
           /          \
          /            \
    TreeNode left      TreeNode right
    /       \       /           \
   ...      ...    ...          ...
*/

typedef struct TreeNode {
  struct TreeNode *left;
  struct TreeNode *right;
  struct Element *element;
} TreeNode;

/*
    Returns a pointer to a dynamically allocated tree_node.
*/
TreeNode *new_tree_node(Element *element) {
  TreeNode *bnode = xmalloc(sizeof(TreeNode));
  bnode->left = NULL;
  bnode->right = NULL;
  bnode->element = element;
  return bnode;
}

/*  TODO: g)
    Releases the memory used by a tree_node and also frees the included element.
*/
void free_tree_node(TreeNode *tree) {
  if (tree == NULL) {
    return;
  }
  free_tree_node(tree->left);
  free_tree_node(tree->right);
  free_element(tree->element);
  free(tree);
}

// TODO: b)
struct Element {
  char *text;
  int frequency;
  Node *wishers;
};

// TODO: b)
Element *new_element(char *wish, char *child) {
  Element *element = xmalloc(sizeof(Element));
  element->text = s_copy(wish);
  element->frequency = 1;
  element->wishers = new_node(child, NULL);
  return element;
}

// TODO: g)
void free_element(Element *element) {
  if (element == NULL) {
    return;
  }
  free(element->text);
  while (element->wishers != NULL) {
    element->wishers = free_node(element->wishers);
  }
  free(element);
}
// TODO: c)
TreeNode *add_wish(TreeNode *tree, char *wish, char *child) {
  if (tree == NULL) { // else would lead to seg_fault
    return new_tree_node(new_element(wish, child));
  }

  if (strcmp(wish, tree->element->text) == 0) {
    if (!contains(tree->element->wishers, child)) {
      tree->element->wishers = new_node(child, tree->element->wishers);
    }
    tree->element->frequency++;
  } else if (strcmp(wish, tree->element->text) < 0) {
    tree->left = add_wish(tree->left, wish, child);
  } else {
    tree->right = add_wish(tree->right, wish, child);
  }

  return tree;
}

typedef struct ElementNode {
  struct ElementNode *next;
  Element *element;
} ElementNode;

ElementNode *new_element_node(Element *element, ElementNode *next) {
  ElementNode *en = xmalloc(sizeof(ElementNode));
  en->next = next;
  en->element = element;
  return en;
}
// TODO: g)
void free_element_list(ElementNode *en) {
  while (en != NULL) {
    ElementNode *next = en->next;
    free(en);
    en = next;
  }
}

void print_element_list(ElementNode *list, int n) {
  printf("%55s\t%6s\n", "Wunsch", "Anzahl");
  while (n > 0 && list != NULL) {
    printf("%55s\t%6d\n", list->element->text, list->element->frequency);
    n--;
    list = list->next;
  }
}

// TODO: e)
ElementNode *insert_ordered_by_count(ElementNode *result, TreeNode *tree) {
  if (tree == NULL) {
    return result;
  }

  result = insert_ordered_by_count(result, tree->left);
  result = insert_ordered_by_count(result, tree->right);

  if (result == NULL || tree->element->frequency > result->element->frequency) {
    return new_element_node(tree->element, result);
  }

  ElementNode *current = result;
  while (current->next != NULL &&
         current->next->element->frequency >= tree->element->frequency) {
    current = current->next;
  }

  current->next = new_element_node(tree->element, current->next);

  return result;
}

// TODO: d)
static void print_actual_tree(TreeNode *tree) {
  if (tree == NULL)
    return;
  print_actual_tree(tree->left);
  printf("%55s\t%6d\t", tree->element->text, tree->element->frequency);

  // Print children on the same line
  Node *wishers = tree->element->wishers;
  while (wishers != NULL) {
    printf("%s", wishers->value);
    if (wishers->next != NULL) {
      printf(", ");
    }
    wishers = wishers->next;
  }
  printf("\n");

  print_actual_tree(tree->right);
}

void print_tree_as_list(TreeNode *tree) {
  printf("%55s\t%6s\t%s\n", "Wunsch", "Anzahl", "Kinder");
  print_actual_tree(tree);
}

// Skips the rest of the current line.
char *skip_line(char *s) {
  while (*s != '\n' && *s != '\0')
    s++;
  if (*s == '\n')
    s++;
  return s;
}

// Skips the current token.
char *skip_token(char *s) {
  while (*s != ',' && *s != '\n' && *s != '\0')
    s++;
  return s;
}

// Skips spaces.
char *skip_spaces_and_commas(char *s) {
  while (*s == ' ' || *s == ',')
    s++;
  return s;
}

// Create a new token from s (inclusive) to t (exclusive).
char *new_token(char *s, char *t) {
  char *token = xmalloc(t - s + 1);
  int i = 0;
  while (s < t) {
    token[i] = *s;
    i++;
    s++;
  }
  token[i] = '\0';
  return token;
}

// Returns a new token by first skipping spaces and commas and then reading the
// token. Sets *s to the first character after the token.
char *next_token(/*INOUT*/ char **s) {
  *s = skip_spaces_and_commas(*s);
  char *t = skip_token(*s);
  char *token = new_token(*s, t);
  *s = t; // set *s to the character after the token
  return token;
}

/*
    This function reads in one line of the wish text file and adds the wishes of
   a child to tree.
*/
TreeNode *read_wish_list(char **s, TreeNode *tree) {
  char *child = next_token(s);

  while (**s != '\0' && **s != '\n') {
    char *wish = next_token(s);
    *s = skip_spaces_and_commas(*s);
    tree = add_wish(tree, wish, child);
    free(wish);
  }

  free(child);
  return tree;
}

/*
    This function reads the whole file and uses the read_wish_list function to
   parse a single line.
*/
TreeNode *read_wishes(char *filename, TreeNode *tree) {
  char *file = s_read_file(filename);
  char *s = file;
  s = skip_line(s);
  while (*s != '\0') {
    tree = read_wish_list(&s, tree);
    s = skip_line(s);
  }
  free(file);
  return tree;
}

int main(int argc, char **argv) {
  report_memory_leaks(true);

  TreeNode *tree = read_wishes("wishes.txt", NULL);

  print_tree_as_list(tree);

  ElementNode *sorted_by_count = insert_ordered_by_count(NULL, tree);

  //   print_element_list(sorted_by_count, 10);

  // TODO: f)
  Node *all_children = NULL;
  int gift_count = 0;
  ElementNode *current = sorted_by_count;

  while (current != NULL && gift_count < 11) {
    // Add all children from this gift
    Node *wishers = current->element->wishers;
    while (wishers != NULL) {
      if (!contains(all_children, wishers->value)) {
        all_children = new_node(wishers->value, all_children);
      }
      wishers = wishers->next;
    }
    gift_count++;
    current = current->next;
  }

  int unique_children = length(all_children);
  printf("With top 11 gifts, %d children get presents.\n", unique_children);

  if (unique_children >= 29) {
    printf("All children got the gifts!\n");
  } else {
    printf("Only %d out of 29 children get gifts.\n", unique_children);
  }

  // Free children list
  while (all_children != NULL) {
    all_children = free_node(all_children);
  }

  // TODO: g)
  free_element_list(sorted_by_count);
  free_tree_node(tree);

  return 0;
}