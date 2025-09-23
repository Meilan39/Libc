#include <stdio.h>
#include <assert.h>

// Your library headers
#include "../ring.h"   // Assumes your ring buffer code is in this header

// Instantiate the Ring for the type 'int' with the name 'int'
DEFINE_RING(int, int)

// --- Helper Functions ---

/**
 * @brief Prints the full state of the ring buffer for diagnostics.
 * @param r The ring buffer to print.
 * @param label A descriptive label for the current state.
 */
void print_ring_state(Ring(int) *r, const char *label)
{
    if (r == NULL)
    {
        printf("%-30s | (NULL Ring Pointer)\n", label);
        return;
    }
    printf("%-30s | Size: %-2zu | Cap: %-2zu | Head: %-2zu | Tail: %-2zu | Content: ",
           label, size(r), capacity(r), r->head, r->tail);

    if (empty(r))
    {
        printf("(empty)\n");
        return;
    }

    // Print elements in logical order from head to tail
    for (size_t i = 0; i < size(r); ++i)
    {
        // Calculate the physical index in the circular array
        size_t index = (r->head + i) % capacity(r);
        printf("%d ", r->vec->arr[index]);
    }
    printf("\n");
}

// --- Test Suite ---

void test_ring()
{
    printf("===== Comprehensive Ring Buffer<int> Test Suite =====\n\n");

    // --- 1. Basic Lifecycle: new, empty, size, delete ---
    printf("--- 1. Basic Lifecycle ---\n");
    Ring(int) *r = new_ring(int);
    print_ring_state(r, "Default constructor");
    assert(empty(r) == 1);
    assert(size(r) == 0);
    delete_ring(int, r);
    printf("Lifecycle OK.\n\n");

    // --- 2. Core FIFO Behavior (Queue-like) ---
    printf("--- 2. Core FIFO Behavior (push_back / pop_front) ---\n");
    r = new_ring(int);
    push_back(r, 10);
    push_back(r, 20);
    push_back(r, 30);
    print_ring_state(r, "After 3 push_backs");
    assert(size(r) == 3);
    assert(front(r) == 10);
    assert(back(r) == 30);

    pop_front(r);
    print_ring_state(r, "After 1 pop_front");
    assert(size(r) == 2);
    assert(front(r) == 20);

    pop_front(r);
    pop_front(r);
    print_ring_state(r, "After 2 more pop_fronts");
    assert(empty(r) == 1);
    printf("FIFO OK.\n\n");

    // --- 3. Core LIFO Behavior (Stack-like) ---
    printf("--- 3. Core LIFO Behavior (push_front / pop_back) ---\n");
    push_front(r, 100);
    push_front(r, 200);
    push_front(r, 300);
    print_ring_state(r, "After 3 push_fronts");
    assert(size(r) == 3);
    assert(front(r) == 300);
    assert(back(r) == 100);

    pop_back(r);
    print_ring_state(r, "After 1 pop_back");
    assert(size(r) == 2);
    assert(back(r) == 200);
    printf("LIFO OK.\n\n");

    // --- 4. Critical Test: Wrap-Around Logic ---
    printf("--- 4. Critical Test: Wrap-Around ---\n");
    clear(r);
    reserve(r, 4); // Force a small capacity to test wrapping
    print_ring_state(r, "Reserved capacity 4");
    push_back(r, 1); push_back(r, 2); push_back(r, 3); push_back(r, 4);
    print_ring_state(r, "Filled to capacity");
    
    pop_front(r);
    pop_front(r);
    print_ring_state(r, "Popped two (head advanced)"); // Logical: [3, 4]
    assert(front(r) == 3);

    push_back(r, 5);
    push_back(r, 6);
    print_ring_state(r, "Pushed two (tail wrapped)"); // Logical: [3, 4, 5, 6]
    assert(front(r) == 3);
    assert(back(r) == 6);
    printf("Wrap-around OK.\n\n");

    // --- 5. Ultimate Test: Reallocation While Wrapped ---
    printf("--- 5. Ultimate Test: Reallocation While Wrapped ---\n");
    push_back(r, 7); // This push forces a grow and "un-wrapping"
    print_ring_state(r, "Pushed to trigger realloc");
    assert(size(r) == 5);
    assert(capacity(r) >= 8);
    assert(front(r) == 3); // Verify data integrity
    assert(back(r) == 7);
    
    // Verify the entire sequence is now correct and contiguous in memory
    int expected[] = {3, 4, 5, 6, 7};
    for (size_t i = 0; i < size(r); ++i) {
        size_t physical_index = (r->head + i) % capacity(r);
        assert(r->vec->arr[physical_index] == expected[i]);
    }
    printf("Reallocation while wrapped OK.\n\n");

    // --- 6. Copy and Move Semantics ---
    printf("--- 6. Copy and Move Semantics ---\n");
    Ring(int)* r_copy = copy_ring(int, r);
    print_ring_state(r, "Original for copy");
    print_ring_state(r_copy, "Copied");

    pop_front(r);
    printf("Popped from original...\n");
    print_ring_state(r, "Original after pop");
    print_ring_state(r_copy, "Copied (should be unchanged)");
    assert(size(r_copy) == 5 && front(r_copy) == 3);
    printf("Deep copy OK.\n");

    Ring(int)* r_move = move_ring(int, r_copy);
    print_ring_state(r_move, "Moved");
    print_ring_state(r_copy, "Copied (now gutted)");
    assert(empty(r_copy) && r_copy->vec->arr == NULL);
    printf("Move OK.\n\n");

    // --- 7. Final Cleanup ---
    delete_ring(int, r);
    delete_ring(int, r_copy);
    delete_ring(int, r_move);
    printf("All memory cleaned up.\n");
    
    printf("\n===== Test Suite Complete =====\n");
}