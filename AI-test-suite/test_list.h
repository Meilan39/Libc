#include <stdlib.h>
#include <stdio.h>

#include "../list.h"

DEFINE_LIST(int, int)
DEFINE_LIST(char, char)

void print_list(List(int)* list, const char* label) {
    printf("%s (size %zu): ", label, size(list));
    for (size_t i = 0; i < size(list); i++) {
        printf("%d ", at(list, i));
    }
    printf("\n");
}

void test_list() {
    printf("=== Testing generic List<int> ===\n");

    // Default constructor (what you already had)
    List(int) *list = new_list(int);
    printf("List created with default constructor. Empty? %d\n", empty(list));
    delete_list(int, list); // Clean up immediately

    // --- NEW CONSTRUCTOR TESTS ---

    printf("\n-- Testing sized constructor (new_list_sized) --\n");
    List(int) *sized_list = new_list(int, 5);
    // Note: The values will be uninitialized garbage, which is expected.
    // The main thing to test is that the size is correct.
    printf("Created a list of size 5. Actual size: %zu\n", size(sized_list));
    delete_list(int, sized_list);

    printf("\n-- Testing filled constructor (new_list_filled) --\n");
    List(int) *filled_list = new_list(int, 4, 99); // Create a list of four 99s
    print_list(filled_list, "Filled list");
    printf("Verifying at(2) == 99: %s\n", at(filled_list, 2) == 99 ? "OK" : "FAIL");
    delete_list(int, filled_list);

    printf("\n-- Testing filled constructor (new_list_filled) --\n");
    List(char) *filled_string = new_list(char, 4, 'a'); // Create a list of four 99s
    printf("Verifying at(2) == a: %s\n", at(filled_list, 2) == 'a' ? "OK" : "FAIL");
    delete_list(char, filled_string);
    
    printf("\n-- Testing copy constructor (copy_list) --\n");
    // 1. Create and populate an original list
    List(int) *original_list = new_list(int);
    push_front(original_list, 100);
    push_front(original_list, 200);
    push_front(original_list, 300);
    print_list(original_list, "Original list");

    // 2. Make a copy
    List(int) *copied_list = copy_list(int, original_list);
    print_list(copied_list, "Copied list  ");

    // 3. Verify the copy is identical
    printf("Verifying size and content of copy... ");
    if (size(original_list) == size(copied_list) && at(copied_list, 0) == 300 && at(copied_list, 2) == 100) {
        printf("OK\n");
    } else {
        printf("FAIL\n");
    }

    // 4. Modify the original list to ensure the copy is independent (deep copy)
    printf("Modifying original list by popping front...\n");
    pop_front(original_list);
    print_list(original_list, "Original list after pop");
    print_list(copied_list,   "Copied list remains unchanged");
    printf("Verifying copy was not affected... %s\n", size(copied_list) == 3 ? "OK" : "FAIL");
    
    clear(copied_list);
    print_list(copied_list, "\ncopied list is cleared");

    // 5. Clean up both lists
    delete_list(int, original_list);
    delete_list(int, copied_list);

    printf("\n=== END OF NEW CONSTRUCTOR TESTS ===\n\n");

    // --- Your original, more detailed operation tests can go here ---
    // For completeness, I'll re-add a fresh list for the original tests.
    
    printf("=== Resuming original operation tests ===\n");
    List(int) *main_list = new_list(int);

    printf("\n-- push_front tests --\n");
    push_front(main_list, 10);
    push_front(main_list, 20);
    push_front(main_list, 30);
    print_list(main_list, "List after pushes");

    printf("at(0)=%d, at(1)=%d, at(2)=%d\n",
           at(main_list, 0), at(main_list, 1), at(main_list, 2));

    printf("\n-- pop_front test --\n");
    int popped = front(main_list);
    pop_front(main_list);
    printf("Popped: %d, new size=%zu\n", popped, size(main_list));
    print_list(main_list, "List after pop");

    printf("\n-- insert test --\n");
    insert(main_list, 1, 99); // insert at middle
    print_list(main_list, "List after inserting 99 at index 1");

    printf("\n-- erase test --\n");
    int erased = at(main_list, 1);
    erase(main_list, 1);
    printf("Erased index 1, value=%d\n", erased);
    print_list(main_list, "List after erase");

    printf("\n-- pop until empty --\n");
    while (!empty(main_list)) {
        printf("Popped %d\n", front(main_list));
        pop_front(main_list);
    }
    printf("List empty? %d\n", empty(main_list));

    printf("\n-- delete test --\n");
    delete_list(int, main_list);
    printf("List deleted successfully.\n");
}