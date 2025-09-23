#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>

#include "global.h"

#define NPOS 0xFFFFFFFF
#define TERMINATOR(T) _Generic(((T){0}), \
    char: '\0',                          \
    wchar_t: L'\0')
#define STRLEN(T, arg1) _Generic(((T){0}), \
    char: strlen,\
    wchar_t: wcslen)(arg1)
#define STRCMP(T, arg1, arg2) _Generic(((T){0}), \
    char: strcmp, \
    wchar_t: wcscmp)(arg1, arg2)
#define STRNCMP(T, arg1, arg2, arg3) _Generic(((T){0}), \
    char: strncmp, \
    wchar_t: wcsncmp)(arg1, arg2, arg3)

#define DEFINE_STRING(T, N)                                                                         \
                                                                                                    \
    DEFINE_VECTOR_IMPL(T, string_##N, string)                                                       \
                                                                                                    \
    struct String_functions_##N;                                                                    \
                                                                                                    \
    typedef struct                                                                                  \
    {                                                                                               \
        Vector_string_##N *vec;                                                                     \
        struct String_functions_##N *functions;                                                     \
    } String_##N;                                                                                   \
                                                                                                    \
    typedef struct String_functions_##N                                                             \
    {                                                                                               \
        int (*empty)(String_##N *);                                                                 \
        void (*reserve)(String_##N *, size_t);                                                      \
        void (*shrink)(String_##N *);                                                               \
        size_t (*size)(String_##N *);                                                               \
        size_t (*capacity)(String_##N *);                                                           \
        T* (*at)(String_##N *, size_t);                                                              \
        T* (*front)(String_##N *);                                                                   \
        T* (*back)(String_##N *);                                                                    \
        void (*clear)(String_##N *);                                                                \
        void (*push_back)(String_##N *, T);                                                         \
        void (*pop_back)(String_##N *);                                                             \
        void (*insert_3)(String_##N *, size_t, const T *);                                          \
        void (*erase_3)(String_##N *, size_t, size_t);                                              \
        void (*append)(String_##N *, const T *);                                                    \
        void (*resize)(String_##N *, size_t);                                                       \
        void (*replace)(String_##N *, size_t, size_t, const T *);                                   \
        size_t (*find)(String_##N *, const T *, size_t);                                            \
        size_t (*rfind)(String_##N *, const T *, size_t);                                           \
        String_##N *(*substr)(String_##N *, size_t, size_t);                                        \
        const T* (*c_str)(String_##N *);                                                            \
        int (*compare)(String_##N *, String_##N *);                                                 \
    } String_functions_##N;                                                                         \
                                                                                                   \
    static inline String_##N *string_new_string_1_##N();                                            \
    static inline String_##N *string_new_string_2_##N(const T *arr);                                \
    static inline String_##N *string_new_string_3_##N(size_t size, T data);                         \
    static inline String_##N *string_copy_string_##N(const String_##N *other);                      \
    static inline String_##N *string_move_string_##N(String_##N *other);                            \
    static inline void string_delete_string_##N(String_##N *this);                                  \
                                                                                                    \
    static inline int string_empty_##N(String_##N *this);                                           \
    static inline void string_reserve_##N(String_##N *this, size_t capacity);                       \
    static inline void string_shrink_##N(String_##N *this);                                         \
    static inline size_t string_size_##N(String_##N *this);                                         \
    static inline size_t string_capacity_##N(String_##N *this);                                     \
    static inline T *string_at_##N(String_##N *this, size_t idx);                                    \
    static inline T *string_front_##N(String_##N *this);                                             \
    static inline T *string_back_##N(String_##N *this);                                              \
                                                                                                    \
    static inline void string_clear_##N(String_##N *this);                                          \
    static inline void string_push_back_##N(String_##N *this, T data);                              \
    static inline void string_pop_back_##N(String_##N *this);                                       \
    static inline void string_insert_3_##N(String_##N *this, size_t idx, const T *arr);             \
    static inline void string_erase_3_##N(String_##N *this, size_t idx, size_t size);               \
    static inline void string_append_##N(String_##N *this, const T *arr);                           \
    static inline void string_resize_##N(String_##N *this, size_t size);                            \
    static inline void string_replace_##N(String_##N *this, size_t idx, size_t size, const T *arr); \
                                                                                                    \
    static inline size_t string_find_##N(String_##N *this, const T *arr, size_t idx);               \
    static inline size_t string_rfind_##N(String_##N *this, const T *arr, size_t idx);              \
    static inline String_##N *string_substr_##N(String_##N *this, size_t idx, size_t size);         \
    static inline const T *string_c_str_##N(String_##N *this);                                      \
    static inline int string_compare_##N(String_##N *this, String_##N *other);                      \
                                                                                                    \
    static String_functions_##N string_funcs_##N = {                                                \
        &string_empty_##N,                                                                          \
        &string_reserve_##N,                                                                        \
        &string_shrink_##N,                                                                         \
        &string_size_##N,                                                                           \
        &string_capacity_##N,                                                                       \
        &string_at_##N,                                                                             \
        &string_front_##N,                                                                          \
        &string_back_##N,                                                                           \
        &string_clear_##N,                                                                          \
        &string_push_back_##N,                                                                      \
        &string_pop_back_##N,                                                                       \
        &string_insert_3_##N,                                                                       \
        &string_erase_3_##N,                                                                        \
        &string_append_##N,                                                                         \
        &string_resize_##N,                                                                         \
        &string_replace_##N,                                                                        \
        &string_find_##N,                                                                           \
        &string_rfind_##N,                                                                          \
        &string_substr_##N,                                                                         \
        &string_c_str_##N,                                                                          \
        &string_compare_##N,                                                                        \
    };                                                                                              \
                                                                                                    \
    static inline String_##N *string_new_string_1_##N()                                             \
    {                                                                                               \
        String_##N *this = malloc(sizeof(String_##N));                                              \
        if (this == NULL)                                                                           \
            error("failed allocation");                                                             \
                                                                                                    \
        this->vec = vector_new_vector_2_string_##N(0);                                              \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
        this->functions = &string_funcs_##N;                                                        \
                                                                                                    \
        return this;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline String_##N *string_new_string_2_##N(const T *arr)                                 \
    {                                                                                               \
        String_##N *this = malloc(sizeof(String_##N));                                              \
        if (this == NULL)                                                                           \
            error("failed allocation");                                                             \
                                                                                                    \
        this->vec = vector_new_vector_4_string_##N(arr, STRLEN(T, arr));                           \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
        this->functions = &string_funcs_##N;                                                        \
                                                                                                    \
        return this;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline String_##N *string_new_string_3_##N(size_t size, T data)                          \
    {                                                                                               \
        String_##N *this = malloc(sizeof(String_##N));                                              \
        if (this == NULL)                                                                           \
            error("failed allocation");                                                             \
                                                                                                    \
        this->vec = new_vector(string_##N, size, data);                                             \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
        this->functions = &string_funcs_##N;                                                        \
                                                                                                    \
        return this;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline String_##N *string_copy_string_##N(const String_##N *other)                       \
    {                                                                                               \
        if(other == NULL)\
            error("copy constructor called on NULL string");\
        \
        String_##N *this = string_new_string_1_##N();\
                                                                                                    \
        this->vec = copy_vector(string_##N, other->vec);                                            \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
        this->functions = &string_funcs_##N;                                                        \
                                                                                                    \
        return this;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline String_##N *string_move_string_##N(String_##N *other)                             \
    {                                                                                               \
        if(other == NULL)\
            error("move constructor called on NULL string");\
        \
        String_##N *this = string_new_string_1_##N();\
                                                                                                    \
        this->vec = move_vector(string_##N, other->vec);                                            \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
        this->functions = &string_funcs_##N;                                                        \
                                                                                                    \
        return this;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline void string_delete_string_##N(String_##N *this)                                   \
    {                                                                                               \
        delete_vector(string_##N, this->vec);                                                       \
        free(this);                                                                                 \
    }                                                                                               \
                                                                                                    \
    static inline int string_empty_##N(String_##N *this)                                            \
    {                                                                                               \
        return empty(this->vec);                                                                    \
    }                                                                                               \
                                                                                                    \
    static inline void string_reserve_##N(String_##N *this, size_t capacity)                        \
    {                                                                                               \
        reserve(this->vec, capacity);                                                               \
    }                                                                                               \
                                                                                                    \
    static inline void string_shrink_##N(String_##N *this)                                          \
    {                                                                                               \
        if (this == NULL)                                                                           \
            error("shrink called on NULL string");                                                  \
        if (this->vec->size + 1 == this->vec->capacity)                                             \
            return;                                                                                 \
                                                                                                    \
        this->vec->capacity = this->vec->size + 1;                                                  \
        this->vec->arr = realloc(this->vec->arr, this->vec->capacity * sizeof(T));                  \
        if (this->vec->arr == NULL)                                                                 \
            error("allocation failed");                                                             \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline size_t string_size_##N(String_##N *this)                                          \
    {                                                                                               \
        return size(this->vec);                                                                     \
    }                                                                                               \
                                                                                                    \
    static inline size_t string_capacity_##N(String_##N *this)                                      \
    {                                                                                               \
        return capacity(this->vec);                                                                 \
    }                                                                                               \
                                                                                                    \
    static inline T *string_at_##N(String_##N *this, size_t idx)                                     \
    {                                                                                               \
        return &at(this->vec, idx);                                                                  \
    }                                                                                               \
                                                                                                    \
    static inline T *string_front_##N(String_##N *this)                                              \
    {                                                                                               \
        return &front(this->vec);                                                                    \
    }                                                                                               \
                                                                                                    \
    static inline T *string_back_##N(String_##N *this)                                               \
    {                                                                                               \
        return &back(this->vec);                                                                     \
    }                                                                                               \
                                                                                                    \
    static inline void string_clear_##N(String_##N *this)                                           \
    {                                                                                               \
        clear(this->vec);                                                                           \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_push_back_##N(String_##N *this, T data)                               \
    {                                                                                               \
        push_back(this->vec, data);                                                                 \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_pop_back_##N(String_##N *this)                                        \
    {                                                                                               \
        pop_back(this->vec);                                                                        \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_insert_3_##N(String_##N *this, size_t idx, const T *arr)              \
    {                                                                                               \
        insert(this->vec, idx, arr, STRLEN(T, arr));                                               \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_erase_3_##N(String_##N *this, size_t idx, size_t size)                \
    {                                                                                               \
        erase(this->vec, idx, size);                                                                \
        this->vec->arr[this->vec->size] = TERMINATOR(T);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_append_##N(String_##N *this, const T *arr)                            \
    {                                                                                               \
        string_insert_3_##N(this, this->vec->size, arr);                                            \
    }                                                                                               \
                                                                                                    \
    static inline void string_resize_##N(String_##N *this, size_t size)                             \
    {                                                                                               \
        string_erase_3_##N(this, size, this->vec->size - size);                                     \
    }                                                                                               \
                                                                                                    \
    static inline void string_replace_##N(String_##N *this, size_t idx, size_t size, const T *arr)  \
    {                                                                                               \
        string_erase_3_##N(this, idx, size);                                                        \
        string_insert_3_##N(this, idx, arr);                                                        \
    }                                                                                               \
                                                                                                    \
    static inline size_t string_find_##N(String_##N *this, const T *arr, size_t idx)                \
    {                                                                                               \
        if (this == NULL)                                                                           \
            error("find called on NULL string");                                                    \
        if (this->vec->size <= idx)                                                                 \
            return NPOS;                                                                            \
                                                                                                    \
        size_t size = STRLEN(T, arr);                                                              \
        for (size_t i = idx; i + size <= this->vec->size; i++)                                      \
            if (STRNCMP(T, this->vec->arr + i, arr, size) == 0)                                    \
                return i;                                                                           \
                                                                                                    \
        return NPOS;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline size_t string_rfind_##N(String_##N *this, const T *arr, size_t idx)               \
    {                                                                                               \
        if (this == NULL)                                                                           \
            error("rfind called on NULL string");                                                   \
        if (this->vec->size <= idx)                                                                 \
            return NPOS;                                                                            \
                                                                                                    \
        size_t size = STRLEN(T, arr);                                                              \
        for (size_t i = idx;; i--)                                                                  \
        {                                                                                           \
            if (STRNCMP(T, this->vec->arr + i, arr, size) == 0)                                    \
                return i;                                                                           \
                                                                                                    \
            if (i == 0)                                                                             \
                break;                                                                              \
        }                                                                                           \
                                                                                                    \
        return NPOS;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline String_##N *string_substr_##N(String_##N *this, size_t idx, size_t size)          \
    {                                                                                               \
        if (this == NULL)                                                                           \
            error("substr called on NULL string");                                                  \
        if (this->vec->size <= idx || this->vec->size < idx + size)                                 \
            error("sub-string out of bounds");                                                      \
                                                                                                    \
        String_##N *ret = string_new_string_1_##N();                                                \
        const T *cstr = string_c_str_##N(this);                                                  \
        ret->vec = vector_new_vector_4_string_##N(cstr + idx, size);                                \
        ret->vec->arr[ret->vec->size] = TERMINATOR(T);                                               \
                                                                                                    \
        return ret;                                                                                 \
    }                                                                                               \
                                                                                                    \
    static inline const T *string_c_str_##N(String_##N *this)                                       \
    {                                                                                               \
        if (this == NULL)                                                                           \
            error("c_str called on NULL string");                                                   \
        if (this->vec->arr == NULL)                                                                 \
            error("c_str called on uninitialized string");                                          \
                                                                                                    \
        return this->vec->arr;                                                                      \
    }                                                                                               \
                                                                                                    \
    static inline int string_compare_##N(String_##N *this, String_##N *other)                       \
    {                                                                                               \
        if (this == NULL || other == NULL)                                                          \
            error("compare called on NULL string");                                                 \
                                                                                                    \
        return STRCMP(T, string_c_str_##N(this), string_c_str_##N(other));                         \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define String(N) String_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @param 2. Container(T) *new_container(N, size_t size);
 * @param 3. Container(T) *new_container(N, size_t size, T data);
 * @return pointer to newly constructed container
 */
#define new_string(...) GET_MACRO(__VA_ARGS__, new_string_5, new_string_4, new_string_3, new_string_2, new_string_1)(__VA_ARGS__)
#define new_string_1(N) string_new_string_1_##N()
#define new_string_2(N, arg) string_new_string_2_##N(arg)
#define new_string_3(N, arg1, arg2) string_new_string_3_##N(arg1, arg2)
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_string(N, other) string_copy_string_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_string(N, other) string_move_string_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_string(N, this) string_delete_string_##N(this)

#include "macros.h"