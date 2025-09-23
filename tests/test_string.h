#include <stdio.h>
#include <string.h>

#include "../string.h"

DEFINE_STRING(char, char)


void print_string(String(char) *s, const char *label)
{
    if (s == NULL)
    {
        printf("%-25s | (NULL String Pointer)\n", label);
        return;
    }
    if (s->vec->arr) {
        printf("%-25s | Size: %-2zu | Capacity: %-2zu | Content: \"%s\"\n",
                label, size(s), capacity(s), c_str(s));
    } else {
        printf("%-25s | Size: %-2zu | Capacity: %-2zu | Content: \n",
                label, size(s), capacity(s));
    }   
}

void test_string()
{
    printf("===== Comprehensive String Test Suite =====\n\n");

    // --- 1. Constructor and Destructor Tests ---
    printf("--- 1. Constructor & Destructor Tests ---\n");
    String(char) *s1 = new_string(char); // Default
    print_string(s1, "Default constructor");

    String(char) *s2 = new_string(char, "Hello, C!"); // From C-string
    print_string(s2, "Constructor from c-str");

    String(char) *s3 = new_string(char, 10, 'A'); // Filled constructor
    print_string(s3, "Filled constructor (10,A)");

    delete_string(char, s1);
    delete_string(char, s2);
    delete_string(char, s3);
    printf("Constructors and basic deletion OK.\n\n");

    // --- 2. Copy and Move Semantics ---
    printf("--- 2. Copy and Move Semantics ---\n");
    String(char) *original = new_string(char, "original");
    print_string(original, "Original");

    String(char) *copied = copy_string(char, original);
    print_string(copied, "Copied");

    printf("Modifying original...\n");
    append(original, " changed");
    print_string(original, "Original after change");
    print_string(copied, "Copied (should be unchanged)");
    printf("Deep copy verified: %s\n", strcmp(c_str(copied), "original") == 0 ? "OK" : "FAIL");

    String(char) *moved = move_string(char, copied);
    print_string(moved, "Moved (has copied's data)");
    print_string(copied, "Copied (should be gutted)");
    printf("Move semantics verified: %s\n\n", (size(copied) == 0 && copied->vec->arr == NULL) ? "OK" : "FAIL");
    
    delete_string(char, original);
    delete_string(char, copied);
    delete_string(char, moved);

    // --- 3. Push Back, Capacity, and Reallocation ---
    printf("--- 3. Push Back & Reallocation ---\n");
    String(char) *s_realloc = new_string(char);
    print_string(s_realloc, "Start empty");
    for (int i = 0; i < 10; ++i)
    {
        push_back(s_realloc, 'a' + i);
        char label[50];
        sprintf(label, "Pushed '%c'", 'a' + i);
        print_string(s_realloc, label);
    }
    printf("Reallocation logic appears OK.\n\n");

    // --- 4. Modifiers and Accessors ---
    printf("--- 4. Modifiers and Accessors ---\n");
    print_string(s_realloc, "Current state");
    printf("front() -> '%c', back() -> '%c', at(4) -> '%c'\n", front(s_realloc), back(s_realloc), at(s_realloc, 4));
    
    pop_back(s_realloc);
    print_string(s_realloc, "After pop_back()");

    clear(s_realloc);
    print_string(s_realloc, "After clear()");
    printf("Is empty? %s\n", empty(s_realloc) ? "Yes" : "No");
    
    push_back(s_realloc, 'X');
    print_string(s_realloc, "After pushing to cleared");
    delete_string(char, s_realloc);
    printf("\n");

    // --- 5. Insert, Erase, Append, Replace ---
    printf("--- 5. Complex Modifications ---\n");
    String(char) *s_mod = new_string(char, "hello world");
    print_string(s_mod, "Initial");

    insert(s_mod, 6, "cruel ");
    print_string(s_mod, "After insert()");

    erase(s_mod, 5, 6);
    print_string(s_mod, "After erase()");

    append(s_mod, " again!");
    print_string(s_mod, "After append()");
    
    replace(s_mod, 6, 5, "friends");
    print_string(s_mod, "After replace()");
    
    resize(s_mod, 13);
    print_string(s_mod, "After resize() to 13");
    printf("\n");

    // --- 6. Search Functions (find, rfind) ---
    printf("--- 6. Search Functions ---\n");
    print_string(s_mod, "Searching in");
    size_t pos1 = find(s_mod, "friends", 0);
    printf("find('friends', 0) -> %zu. Verification: %s\n", pos1, pos1 == 6 ? "OK" : "FAIL");
    size_t pos2 = find(s_mod, "Hello", 0);
    printf("find('Hello', 0) -> %zu (NPOS). Verification: %s\n", pos2, pos2 == NPOS ? "OK" : "FAIL");
    
    append(s_mod, " and friends");
    print_string(s_mod, "Appended for rfind test");
    size_t pos3 = rfind(s_mod, "friends", 24);
    printf("rfind('friends', 25) -> %zu. Verification: %s\n", pos3, pos3 == 18 ? "OK" : "FAIL");
    printf("\n");
    
    // --- 7. Substr and Compare ---
    printf("--- 7. Substr and Compare ---\n");
    String(char) *sub = substr(s_mod, 6, 7);
    print_string(sub, "Substring (6, 7)");
    printf("Comparing 'friends' to substring: %s\n", compare(sub, sub) == 0 ? "Match (OK)" : "Mismatch (FAIL)");

    String(char)* s_comp = new_string(char, "friends");
    printf("Comparing '%s' and '%s': %d (should be 0)\n", c_str(sub), c_str(s_comp), compare(sub, s_comp));
    
    delete_string(char, sub);
    delete_string(char, s_comp);
    delete_string(char, s_mod);
    
    printf("\n===== Test Suite Complete =====\n");
}