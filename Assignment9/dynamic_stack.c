/*
    Compile: make dynamic_stack
    Run: ./dynamic_stack
    make dynamic_stack && ./dynamic_stack
*/

#include "base.h"

//a)
typedef struct dynamic_stack_s {
    int *data;
    int size;
    int capacity;
} DynamicStack;

DynamicStack* stack_new() {
    // TODO: b)
    DynamicStack *s = xmalloc(sizeof(DynamicStack));
    s->size = 0;
    s->capacity = 4;
    s->data = xcalloc(s->capacity, sizeof(int));
    return s;
}

void stack_free(DynamicStack* stack) {
    // TODO: e)
    if (stack == NULL) return;
    if (stack->data != NULL) free(stack->data);
    free(stack);
}

void stack_push(DynamicStack* stack, int value) {
    // TODO: c)
    if (stack == NULL) return;
    if (stack->size >= stack->capacity) {
        int new_capacity = stack->capacity > 0 ? stack->capacity * 2 : 1;
        stack->data = xrealloc(stack->data, new_capacity * sizeof(int));
        stack->capacity = new_capacity;
    }
    stack->data[stack->size++] = value;
}

int stack_pop(DynamicStack* stack) {
    // TODO: d)
    if (stack == NULL || stack->size == 0) return 0;
    stack->size--;
    return stack->data[stack->size];
}

void test_stack_ops(DynamicStack* stack) {
    stack_push(stack, 42);
    stack_push(stack, 1);
    stack_push(stack, 13);
    test_equal_i(stack_pop(stack), 13);
    test_equal_i(stack_pop(stack), 1);
    stack_push(stack, 400);
    stack_push(stack, 500);
    stack_push(stack, 600);
    stack_push(stack, 700);
    test_equal_i(stack_pop(stack), 700);
    test_equal_i(stack_pop(stack), 600);
    test_equal_i(stack_pop(stack), 500);
    test_equal_i(stack_pop(stack), 400);
    test_equal_i(stack_pop(stack), 42);
    test_equal_i(stack_pop(stack), 0);
}

int main(void) {
    DynamicStack* stack = stack_new();
    test_stack_ops(stack);

    stack_free(stack);

    DynamicStack* stack2 = stack_new();
    stack_free(stack2);
}
