#include <stdio.h>
#include "../vector.h" // Assumes your vector code is in this header

// Define the vector type for int
DEFINE_VECTOR(int, int)

// Helper function to print a vector's state for easy verification
void print_vector(Vector(int)* v, const char* label) {
    printf("%-25s | Size: %-2zu | Capacity: %-2zu | Elements: ", label, size(v), capacity(v));
    for (size_t i = 0; i < size(v); i++) {
        printf("%d ", at(v, i));
    }
    printf("\n");
}

void test_vector() {
    printf("===== Comprehensive Vector<int> Test Suite =====\n\n");

    // --- Constructor Tests ---
    printf("--- 1. Constructor Tests ---\n");
    Vector(int)* v1 = new_vector(int);
    print_vector(v1, "Default constructor");

    Vector(int)* v2 = new_vector(int, 5); // Sized constructor
    print_vector(v2, "Sized constructor (5)");
    
    Vector(int)* v3 = new_vector(int, 4, 77); // Filled constructor
    print_vector(v3, "Filled constructor (4, 77)");

    delete_vector(int, v1);
    delete_vector(int, v2);
    delete_vector(int, v3);
    printf("\n");

    // --- Push Back & Reallocation Test ---
    printf("--- 2. Push Back & Reallocation Test ---\n");
    Vector(int)* main_vec = new_vector(int);
    print_vector(main_vec, "Initial state");
    for (int i = 0; i < 10; ++i) {
        push_back(main_vec, i * 10);
        char label[50];
        sprintf(label, "After pushing %d", i * 10);
        print_vector(main_vec, label);
    }
    printf("\n");

    printf("--- 2.5. shrink memory ---\n");
    shrink(main_vec);
    print_vector(main_vec, "after shrinking");
    printf("\n");

    // --- Accessor Tests (at, front, back) ---
    printf("--- 3. Accessor Tests ---\n");
    printf("at(0) should be 0:    %d\n", at(main_vec, 0));
    printf("at(5) should be 50:   %d\n", at(main_vec, 5));
    printf("front() should be 0:  %d\n", front(main_vec));
    printf("back() should be 90:  %d\n", back(main_vec));
    printf("\n");

    // --- Pop Back Test ---
    printf("--- 4. Pop Back Test ---\n");
    pop_back(main_vec);
    print_vector(main_vec, "After one pop_back");
    printf("New back() should be 80: %d\n", back(main_vec));
    printf("\n");

    // --- Insert Test ---
    printf("--- 5. Insert Test ---\n");
    insert(main_vec, 0, 111); // Insert at front
    print_vector(main_vec, "Insert 111 at index 0");
    insert(main_vec, 5, 555); // Insert in middle
    print_vector(main_vec, "Insert 555 at index 5");
    insert(main_vec, size(main_vec), 999); // Insert at end
    print_vector(main_vec, "Insert 999 at the end");
    printf("\n");
    
    // --- Erase Test ---
    printf("--- 6. Erase Test ---\n");
    erase(main_vec, 6); // Erase from middle
    print_vector(main_vec, "Erase element at index 6");
    erase(main_vec, 0); // Erase from front
    print_vector(main_vec, "Erase element at index 0");
    printf("\n");

    // --- Reserve Test ---
    printf("--- 7. Reserve Test ---\n");
    print_vector(main_vec, "State before reserve");
    reserve(main_vec, 50);
    print_vector(main_vec, "After reserving 50");
    printf("\n");

    // --- Clear Test ---
    printf("--- 8. Clear Test ---\n");
    clear(main_vec);
    print_vector(main_vec, "After clear");
    printf("Pushing 123 after clear...\n");
    push_back(main_vec, 123);
    print_vector(main_vec, "State after push");
    printf("\n");

    // --- Copy Constructor Test ---
    printf("--- 9. Copy Constructor Test ---\n");
    print_vector(main_vec, "Original vector");
    Vector(int)* copied_vec = copy_vector(int, main_vec);
    print_vector(copied_vec, "Copied vector");
    printf("Modifying original by pushing 456...\n");
    push_back(main_vec, 456);
    print_vector(main_vec, "Original after push");
    print_vector(copied_vec, "Copied (should be unchanged)");
    printf("\n");

    // --- Move Constructor Test ---
    printf("--- 10. Move Constructor Test ---\n");
    print_vector(main_vec, "Original before move");
    Vector(int)* moved_vec = move_vector(int, main_vec);
    print_vector(moved_vec, "New vector after move");
    print_vector(main_vec, "Original after move (gutted)");
    printf("\n");

    // --- Final Cleanup ---
    printf("--- 11. Final Cleanup ---\n");
    delete_vector(int, main_vec);
    delete_vector(int, copied_vec);
    delete_vector(int, moved_vec);
    printf("All vectors deleted successfully.\n");
    printf("\n===== Test Suite Complete =====\n");
}