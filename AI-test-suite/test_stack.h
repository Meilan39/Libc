#include <stdio.h>
#include <assert.h>

// Must include vector.h first as stack.h depends on it
#include "../stack.h"

// Define the Stack type for integers
DEFINE_STACK(int, int)

// Helper function to print the contents of a stack.
// Note: This is destructive but useful for testing. It pops all elements,
// prints them, and then pushes them back onto a new stack for verification.
void print_and_verify_stack(Stack(int)* s, const char* label) {
    printf("%-25s | Size: %-2zu | Capacity: %-2zu | Top-to-Bottom: ",
           label, size(s), capacity(s));
    
    if (empty(s)) {
        printf("(empty)\n");
        return;
    }

    // Temporarily pop items to print them in order
    Stack(int)* temp_stack = new_stack(int);
    while (!empty(s)) {
        int val = top(s);
        printf("%d ", val);
        push(temp_stack, top(s));
        pop(s);
    }
    printf("\n");

    // Restore the original stack by pushing items back from the temp stack
    while (!empty(temp_stack)) {
        push(s, top(temp_stack));
        pop(temp_stack);
    }
    delete_stack(int, temp_stack);
}

void test_stack() {
    printf("===== Comprehensive Stack<int> Test Suite =====\n\n");

    // --- 1. Constructor and Destructor Tests ---
    printf("--- 1. Constructor & Destructor Tests ---\n");
    Stack(int)* s1 = new_stack(int); // Default
    print_and_verify_stack(s1, "Default constructor");
    printf("Is empty? %s\n\n", empty(s1) ? "Yes (OK)" : "No (FAIL)");
    delete_stack(int, s1);

    // --- 2. Core LIFO Operations (Push, Pop, Top) ---
    printf("--- 2. Core LIFO Operations (Push, Pop, Top) ---\n");
    Stack(int)* s_lifo = new_stack(int);
    
    printf("Pushing 10, 20, 30...\n");
    push(s_lifo, 10);
    print_and_verify_stack(s_lifo, "Pushed 10");
    assert(top(s_lifo) == 10);

    push(s_lifo, 20);
    print_and_verify_stack(s_lifo, "Pushed 20");
    assert(top(s_lifo) == 20);

    push(s_lifo, 30);
    print_and_verify_stack(s_lifo, "Pushed 30");
    assert(top(s_lifo) == 30 && size(s_lifo) == 3);
    printf("Push and Top OK.\n\n");

    printf("Popping elements...\n");
    int val1 = top(s_lifo);
    pop(s_lifo);
    printf("Popped: %d (expected 30)\n", val1);
    assert(val1 == 30);
    print_and_verify_stack(s_lifo, "After first pop");
    assert(top(s_lifo) == 20);

    int val2 = top(s_lifo);
    pop(s_lifo);
    printf("Popped: %d (expected 20)\n", val2);
    assert(val2 == 20);
    print_and_verify_stack(s_lifo, "After second pop");
    assert(top(s_lifo) == 10 && size(s_lifo) == 1);
    
    pop(s_lifo);
    print_and_verify_stack(s_lifo, "After final pop");
    assert(empty(s_lifo));
    printf("LIFO order verified: OK.\n\n");

    // --- 3. Capacity and Reserve ---
    printf("--- 3. Capacity and Reserve ---\n");
    for (int i = 0; i < 10; ++i) {
        push(s_lifo, i);
    }
    print_and_verify_stack(s_lifo, "After 10 pushes");
    
    reserve(s_lifo, 100);
    printf("After reserving 100...\n");
    print_and_verify_stack(s_lifo, "Reserved 100");
    assert(capacity(s_lifo) >= 100);
    printf("Reserve OK.\n\n");

    // --- 4. Copy and Move Semantics ---
    printf("--- 4. Copy and Move Semantics ---\n");
    print_and_verify_stack(s_lifo, "Original for copy");
    
    Stack(int)* s_copy = copy_stack(int, s_lifo);
    print_and_verify_stack(s_copy, "Copied stack");

    printf("Popping from original...\n");
    pop(s_lifo);
    print_and_verify_stack(s_lifo, "Original after pop");
    print_and_verify_stack(s_copy, "Copied (should be unchanged)");
    assert(size(s_copy) == 10 && top(s_copy) == 9);
    printf("Deep copy verified: OK.\n\n");

    Stack(int)* s_move = move_stack(int, s_copy);
    print_and_verify_stack(s_move, "Moved stack");
    print_and_verify_stack(s_copy, "Copied (should be gutted)");
    assert(size(s_copy) == 0 && empty(s_copy));
    printf("Move semantics verified: OK.\n\n");
    
    // --- 5. Final Cleanup ---
    printf("--- 5. Final Cleanup ---\n");
    delete_stack(int, s_lifo);
    delete_stack(int, s_copy);
    delete_stack(int, s_move);
    printf("All stacks deleted successfully.\n");
    printf("\n===== Test Suite Complete =====\n");
}