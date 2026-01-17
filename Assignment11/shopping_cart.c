/*
    Compile: make shopping_cart
    Run: ./shopping_cart
    make shopping_cart && ./shopping_cart
*/

#include "pointer_list.h"

typedef enum {
    C_FOOD,
    C_BOOK,
    C_ELECTRONICS,
} Category;

// Data definition for a shopping list item
typedef struct {
    String name;
    Category cat;
    // The price is given in cents
    // E.g.: a value of 1000 indicates a price of 10.00€
    int price;
} Item;

// String, Category (enum), int -> Item *
// Create an item (constructor).
Item* new_item(String name, Category cat, int price) {
    Item* item = xmalloc(sizeof(Item));

    *item = (Item) {
        .name = s_copy(name),
        .cat = cat,
        .price = price,
    };

    return item;
}

// Item* -> Item*
// Create a copy of an Item.
void* copy_item(void* x) {
    // TODO: a)
    return NULL;
}

// Item* -> String
// String representation of a shopping cart Item.
String item_to_string(void* x) {
    Item* item = (Item *) x;
    size_t n = 100 + s_length(item->name);
    String text = xmalloc(n);

    String cat_string = "unknown";
    switch(item->cat) {
    case C_FOOD:
        cat_string = "Food";
        break;
    case C_BOOK:
        cat_string = "Book";
        break;
    case C_ELECTRONICS:
        cat_string = "Electronics";
        break;
    }

    snprintf(text, n - 1, "\"%s\" (%s) %d.%d€", item->name, cat_string, item->price / 100, item->price % 100);
    return text;
}

// Item* -> void
// Releases memory of an Item.
void free_item(void* x) {
    // TODO: a)
}

// Item* -> bool
// Returns true if the item is an electronic device.
bool is_electronics(void* element, int i, void* x) {
    // TODO: b)
    return false;
}

// Item* -> String
// Maps an Item to its name.
void* item_name(void* element, int i, void* x) {
    // TODO: d)
    return "";
}

// Item* -> bool
// Returns true if the price is less than *x.
bool price_less_than(void* element, int i, void* x) {
    // TODO: c)
    Item* item = (Item *)element;
    int a = *(int *)x;
    return item->price < a;
}



int main(void) {
    report_memory_leaks(true);

    Item* i1 = new_item("Algorithms and Data Structures", C_BOOK, 7500);
    Item* i2 = new_item("Game Console", C_ELECTRONICS, 55000);
    Item* i3 = new_item("Potatoes", C_FOOD, 250);
    Item* i4 = new_item("Headphones", C_ELECTRONICS, 8000);

    printsln("= shopping cart =");
    Node* list = new_node(i1, new_node(i2, new_node(i3, new_node(i4, NULL))));
    println_list(list, item_to_string);

    printsln("= first electronics item =");
    Item* found_item = find_list(list, is_electronics, NULL);
    if (found_item != NULL) {
        String s = item_to_string(found_item);
        printsln(s);
        free(s);
    }

    printsln("= first item cheaper than 10€ =");
    // TODO: b)

 

    free_list(list, free_item);

    return 0;
}