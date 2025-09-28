#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../heap.h"

DEFINE_HEAP(int, int)

int is_heap_valid(Heap(int) *h)
{
    if (empty(h)) return 1;
    size_t s = size(h);
    int *arr = h->vec->arr;
    for (size_t i = 1; i <= s; ++i)
    {
        printf("%d ", arr[i-1]);
        // size_t left = 2 * i;
        // size_t right = 2 * i + 1;
        // if (left < s && h->cmp(arr + i, arr + left) > 0) return 0;
        // if (right < s && h->cmp(arr + i, arr + right) > 0) return 0;
    }
    printf("\n");
    return 1;
}

void test_heap()
{
    printf("===== Comprehensive Binary Heap<int> Test Suite =====\n\n");

    // --- 1. Min-Heap Tests ---
    printf("--- 1. Min-Heap Core Functionality ---\n");
    Heap(int) *min_heap = new_heap(int); // Uses default min-heap compare
    
    printf("Pushing 10, 4, 15, 20, 1...\n");
    push(min_heap, 10); assert(is_heap_valid(min_heap));
    push(min_heap, 4);  assert(is_heap_valid(min_heap));
    push(min_heap, 15); assert(is_heap_valid(min_heap));
    push(min_heap, 20); assert(is_heap_valid(min_heap));
    push(min_heap, 1);  assert(is_heap_valid(min_heap));
    
    printf("Heap size: %zu, Top element: %d (expected 1)\n", size(min_heap), top(min_heap));
    assert(top(min_heap) == 1);
    
    printf("Popping elements from min-heap (should be sorted ascending):\n");
    int expected_min[] = {1, 4, 10, 15, 20};
    for (int i = 0; i < 5; ++i) {
        int val = top(min_heap);
        printf("Popped: %d\n", val);
        assert(val == expected_min[i]);
        pop(min_heap);
        assert(is_heap_valid(min_heap));
    }
    assert(empty(min_heap));
    printf("Min-Heap OK.\n\n");

    // --- 2. Max-Heap Tests ---
    printf("--- 2. Max-Heap Core Functionality ---\n");
    Heap(int) *max_heap = new_heap(int, compare_max_int); // Use max-heap compare
    
    printf("Pushing 10, 4, 15, 20, 1...\n");
    push(max_heap, 10); assert(is_heap_valid(max_heap));
    push(max_heap, 4);  assert(is_heap_valid(max_heap));
    push(max_heap, 15); assert(is_heap_valid(max_heap));
    push(max_heap, 20); assert(is_heap_valid(max_heap));
    push(max_heap, 1);  assert(is_heap_valid(max_heap));

    printf("Heap size: %zu, Top element: %d (expected 20)\n", size(max_heap), top(max_heap));
    assert(top(max_heap) == 20);

    printf("Popping elements from max-heap (should be sorted descending):\n");
    int expected_max[] = {20, 15, 10, 4, 1};
    for (int i = 0; i < 5; ++i) {
        int val = top(max_heap);
        printf("Popped: %d\n", val);
        assert(val == expected_max[i]);
        pop(max_heap);
        assert(is_heap_valid(max_heap));
    }
    assert(empty(max_heap));
    printf("Max-Heap OK.\n\n");

    // --- 3. Heapify Test ---
    printf("--- 3. Heapify on Unsorted Data ---\n");
    int unsorted_data[] = {34, 12, 88, 9, 1, 45, 67, 23};
    size_t count = sizeof(unsorted_data) / sizeof(int);
    
    // Use the push_back and heapify method
    for (size_t i = 0; i < count; ++i) {
        push_back(max_heap, unsorted_data[i]);
    }
    printf("Heap before heapify is not a valid heap.\n");
    heapify(max_heap);
    printf("Heap after heapify should be valid: %s\n", is_heap_valid(max_heap) ? "OK" : "FAIL");
    assert(is_heap_valid(max_heap));
    printf("Top element after heapify: %d (expected 88)\n", top(max_heap));
    assert(top(max_heap) == 88);
    printf("Heapify OK.\n\n");

    // --- 4. Copy and Move Semantics ---
    printf("--- 4. Copy and Move Semantics ---\n");
    Heap(int)* h_copy = copy_heap(int, max_heap);
    printf("Copied heap top: %d\n", top(h_copy));
    assert(top(h_copy) == 88);
    pop(max_heap);
    printf("Original top after pop: %d\n", top(max_heap));
    printf("Copied top (should be unchanged): %d\n", top(h_copy));
    assert(top(h_copy) == 88);
    printf("Deep copy OK.\n");

    Heap(int)* h_move = move_heap(int, h_copy);
    printf("Moved heap top: %d\n", top(h_move));
    assert(top(h_move) == 88);
    assert(empty(h_copy));
    printf("Move OK.\n\n");

    // --- 5. Cleanup ---
    delete_heap(int, min_heap);
    delete_heap(int, max_heap);
    delete_heap(int, h_copy);
    delete_heap(int, h_move);
    printf("All memory cleaned up.\n");
    printf("\n===== Test Suite Complete =====\n");
}