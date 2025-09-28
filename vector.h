#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "global.h"

#define VECTOR_RESIZE_vector 0
#define VECTOR_RESIZE_string 1
#define VECTOR_RESIZE_ring 0
#define VECTOR_RESIZE_stack 0
#define VECTOR_RESIZE_queue 0
#define VECTOR_RESIZE_heap 0

#define DEFINE_VECTOR(T, N) DEFINE_VECTOR_IMPL(T, N, vector)
#define DEFINE_VECTOR_IMPL(T, N, E)                                                                  \
                                                                                                     \
    struct Vector_functions_##N;                                                                     \
                                                                                                     \
    typedef struct                                                                                   \
    {                                                                                                \
        size_t size;                                                                                 \
        size_t capacity;                                                                             \
        T *arr;                                                                                      \
        struct Vector_functions_##N *functions;                                                      \
    } Vector_##N;                                                                                    \
                                                                                                     \
    typedef struct Vector_functions_##N                                                              \
    {                                                                                                \
        int (*empty)(Vector_##N *);                                                                  \
        void (*reserve)(Vector_##N *, size_t);                                                       \
        void (*shrink)(Vector_##N *);                                                                \
        size_t (*size)(Vector_##N *);                                                                \
        size_t (*capacity)(Vector_##N *);                                                            \
        T *(*at)(Vector_##N *, size_t);                                                              \
        T *(*front)(Vector_##N *);                                                                   \
        T *(*back)(Vector_##N *);                                                                    \
        void (*clear)(Vector_##N *);                                                                 \
        void (*push_back)(Vector_##N *, T);                                                          \
        void (*pop_back)(Vector_##N *);                                                              \
        void (*insert_3)(Vector_##N *, size_t, T);                                                   \
        void (*insert_4)(Vector_##N *, size_t, const T *, size_t);                                   \
        void (*erase_2)(Vector_##N *, size_t);                                                       \
        void (*erase_3)(Vector_##N *, size_t, size_t);                                               \
    } Vector_functions_##N;                                                                          \
                                                                                                     \
    static inline void vector_grow_##N(Vector_##N *this, size_t size);                               \
                                                                                                     \
    static inline Vector_##N *vector_new_vector_1_##N();                                             \
    static inline Vector_##N *vector_new_vector_2_##N(size_t size);                                  \
    static inline Vector_##N *vector_new_vector_3_##N(size_t size, T data);                          \
    static inline Vector_##N *vector_new_vector_4_##N(const T *arr, size_t size);                    \
    static inline Vector_##N *vector_copy_vector_##N(const Vector_##N *other);                       \
    static inline Vector_##N *vector_move_vector_##N(Vector_##N *other);                             \
    static inline void vector_delete_vector_##N(Vector_##N *this);                                   \
                                                                                                     \
    static inline int vector_empty_##N(Vector_##N *this);                                            \
    static inline void vector_reserve_##N(Vector_##N *this, size_t capacity);                        \
    static inline void vector_shrink_##N(Vector_##N *this);                                          \
    static inline size_t vector_size_##N(Vector_##N *this);                                          \
    static inline size_t vector_capacity_##N(Vector_##N *this);                                      \
    static inline T *vector_at_##N(Vector_##N *this, size_t idx);                                    \
    static inline T *vector_front_##N(Vector_##N *this);                                             \
    static inline T *vector_back_##N(Vector_##N *this);                                              \
                                                                                                     \
    static inline void vector_clear_##N(Vector_##N *this);                                           \
    static inline void vector_push_back_##N(Vector_##N *this, T data);                               \
    static inline void vector_pop_back_##N(Vector_##N *this);                                        \
    static inline void vector_insert_3_##N(Vector_##N *this, size_t idx, T data);                    \
    static inline void vector_insert_4_##N(Vector_##N *this, size_t idx, const T *arr, size_t size); \
    static inline void vector_erase_2_##N(Vector_##N *this, size_t idx);                             \
    static inline void vector_erase_3_##N(Vector_##N *this, size_t idx, size_t size);                \
                                                                                                     \
    static Vector_functions_##N vector_funcs_##N = {                                                 \
        &vector_empty_##N,                                                                           \
        &vector_reserve_##N,                                                                         \
        &vector_shrink_##N,                                                                          \
        &vector_size_##N,                                                                            \
        &vector_capacity_##N,                                                                        \
        &vector_at_##N,                                                                              \
        &vector_front_##N,                                                                           \
        &vector_back_##N,                                                                            \
        &vector_clear_##N,                                                                           \
        &vector_push_back_##N,                                                                       \
        &vector_pop_back_##N,                                                                        \
        &vector_insert_3_##N,                                                                        \
        &vector_insert_4_##N,                                                                        \
        &vector_erase_2_##N,                                                                         \
        &vector_erase_3_##N,                                                                         \
    };                                                                                               \
                                                                                                     \
    static inline void vector_grow_##N(Vector_##N *this, size_t size)                                \
    {                                                                                                \
        size = size + VECTOR_RESIZE_##E;                                                             \
        if (this->capacity >= size)                                                                  \
            return;                                                                                  \
                                                                                                     \
        size_t capacity = this->capacity ? this->capacity : LIBCMAX(size, MEM_INIT_CAPACITY);        \
        while (capacity < size)                                                                      \
            capacity *= MEM_GROWTH_MULTIPLIER;                                                       \
                                                                                                     \
        this->arr = this->capacity                                                                   \
                        ? realloc(this->arr, capacity * sizeof(T))                                   \
                        : malloc(capacity * sizeof(T));                                              \
        this->capacity = capacity;                                                                   \
                                                                                                     \
        if (this->arr == NULL)                                                                       \
            error("allocation failed");                                                              \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_new_vector_1_##N()                                              \
    {                                                                                                \
        Vector_##N *this = malloc(sizeof(Vector_##N));                                               \
        if (this == NULL)                                                                            \
            error("allocation failed");                                                              \
                                                                                                     \
        this->size = 0;                                                                              \
        this->capacity = 0;                                                                          \
        this->arr = NULL;                                                                            \
        this->functions = &vector_funcs_##N;                                                         \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_new_vector_2_##N(size_t size)                                   \
    {                                                                                                \
        Vector_##N *this = vector_new_vector_1_##N();                                                \
                                                                                                     \
        vector_grow_##N(this, size);                                                                 \
        this->size = size;                                                                           \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_new_vector_3_##N(size_t size, T data)                           \
    {                                                                                                \
        Vector_##N *this = vector_new_vector_2_##N(size);                                            \
                                                                                                     \
        for (size_t i = 0; i < size; i++)                                                            \
            this->arr[i] = data;                                                                     \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_new_vector_4_##N(const T *arr, size_t size)                     \
    {                                                                                                \
        Vector_##N *this = vector_new_vector_2_##N(size);                                            \
                                                                                                     \
        memcpy(this->arr, arr, size * sizeof(T));                                                    \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_copy_vector_##N(const Vector_##N *other)                        \
    {                                                                                                \
        if (other == NULL)                                                                           \
            error("copy constructor called on NULL " #E);                                            \
                                                                                                     \
        Vector_##N *this = vector_new_vector_1_##N();                                                \
                                                                                                     \
        vector_grow_##N(this, other->capacity);                                                      \
        memcpy(this->arr, other->arr, other->capacity * sizeof(T));                                  \
        this->size = other->size;                                                                    \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline Vector_##N *vector_move_vector_##N(Vector_##N *other)                              \
    {                                                                                                \
        if (other == NULL)                                                                           \
            error("move constructor called on NULL " #E);                                            \
                                                                                                     \
        Vector_##N *this = vector_new_vector_1_##N();                                                \
                                                                                                     \
        this->size = other->size;                                                                    \
        this->capacity = other->capacity;                                                            \
        this->arr = other->arr;                                                                      \
                                                                                                     \
        other->size = 0;                                                                             \
        other->capacity = 0;                                                                         \
        other->arr = NULL;                                                                           \
                                                                                                     \
        return this;                                                                                 \
    }                                                                                                \
                                                                                                     \
    static inline void vector_delete_vector_##N(Vector_##N *this)                                    \
    {                                                                                                \
        if (this == NULL)                                                                            \
            return;                                                                                  \
                                                                                                     \
        if (this->arr)                                                                               \
            free(this->arr);                                                                         \
        free(this);                                                                                  \
    }                                                                                                \
                                                                                                     \
    static inline int vector_empty_##N(Vector_##N *this)                                             \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("empty called on NULL " #E);                                                       \
                                                                                                     \
        return this->size == 0;                                                                      \
    }                                                                                                \
                                                                                                     \
    static inline void vector_reserve_##N(Vector_##N *this, size_t capacity)                         \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("reserve called on NULL " #E);                                                     \
        if (this->capacity >= capacity)                                                              \
            return;                                                                                  \
                                                                                                     \
        vector_grow_##N(this, capacity);                                                             \
    }                                                                                                \
                                                                                                     \
    static inline void vector_shrink_##N(Vector_##N *this)                                           \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("shrink called on NULL " #E);                                                      \
        if (this->size == this->capacity)                                                            \
            return;                                                                                  \
                                                                                                     \
        this->capacity = this->size;                                                                 \
        this->arr = realloc(this->arr, this->capacity * sizeof(T));                                  \
    }                                                                                                \
                                                                                                     \
    static inline size_t vector_size_##N(Vector_##N *this)                                           \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("size called on NULL " #E);                                                        \
                                                                                                     \
        return this->size;                                                                           \
    }                                                                                                \
                                                                                                     \
    static inline size_t vector_capacity_##N(Vector_##N *this)                                       \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("capacity called on NULL " #E);                                                    \
                                                                                                     \
        return this->capacity;                                                                       \
    }                                                                                                \
                                                                                                     \
    static inline T *vector_at_##N(Vector_##N *this, size_t idx)                                     \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("at called on NULL " #E);                                                          \
        if (this->size <= idx)                                                                       \
            error(#E " index out of bounds");                                                        \
                                                                                                     \
        return this->arr + idx;                                                                      \
    }                                                                                                \
                                                                                                     \
    static inline T *vector_front_##N(Vector_##N *this)                                              \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("front called on NULL " #E);                                                       \
        if (this->size == 0)                                                                         \
            error("front called on empty " #E);                                                      \
                                                                                                     \
        return this->arr;                                                                            \
    }                                                                                                \
                                                                                                     \
    static inline T *vector_back_##N(Vector_##N *this)                                               \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("back called on NULL " #E);                                                        \
        if (this->size == 0)                                                                         \
            error("back called on emtpy " #E);                                                       \
                                                                                                     \
        return this->arr + this->size - 1;                                                           \
    }                                                                                                \
                                                                                                     \
    static inline void vector_clear_##N(Vector_##N *this)                                            \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("clear called on NULL " #E);                                                       \
                                                                                                     \
        this->size = 0;                                                                              \
    }                                                                                                \
                                                                                                     \
    static inline void vector_push_back_##N(Vector_##N *this, T data)                                \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("push back called on NULL " #E);                                                   \
                                                                                                     \
        vector_grow_##N(this, this->size + 1);                                                       \
        this->arr[this->size++] = data;                                                              \
    }                                                                                                \
                                                                                                     \
    static inline void vector_pop_back_##N(Vector_##N *this)                                         \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("pop back called on NULL " #E);                                                    \
        if (this->size == 0)                                                                         \
            error("pop back called on emtpy " #E);                                                   \
                                                                                                     \
        this->size--;                                                                                \
    }                                                                                                \
                                                                                                     \
    static inline void vector_insert_3_##N(Vector_##N *this, size_t idx, T data)                     \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("insert called on NULL " #E);                                                      \
        if (this->size < idx)                                                                        \
            error(#E " insert out of bounds");                                                       \
                                                                                                     \
        vector_grow_##N(this, this->size + 1);                                                       \
        memmove(this->arr + idx + 1, this->arr + idx,                                                \
                (this->size - idx) * sizeof(T));                                                     \
        this->arr[idx] = data;                                                                       \
        this->size++;                                                                                \
    }                                                                                                \
                                                                                                     \
    static inline void vector_insert_4_##N(Vector_##N *this, size_t idx, const T *arr, size_t size)  \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("insert called on NULL " #E);                                                      \
        if (this->size < idx)                                                                        \
            error(#E " insert out of bounds");                                                       \
                                                                                                     \
        vector_grow_##N(this, this->size + size);                                                    \
        memmove(this->arr + idx + size, this->arr + idx,                                             \
                (this->size - idx) * sizeof(T));                                                     \
        memcpy(this->arr + idx, arr, size * sizeof(T));                                              \
        this->size += size;                                                                          \
    }                                                                                                \
                                                                                                     \
    static inline void vector_erase_2_##N(Vector_##N *this, size_t idx)                              \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("erase called on NULL " #E);                                                       \
        if (this->size <= idx)                                                                       \
            error(#E " erase out of range");                                                         \
                                                                                                     \
        memmove(this->arr + idx, this->arr + idx + 1,                                                \
                (this->size - 1 - idx) * sizeof(T));                                                 \
        this->size--;                                                                                \
    }                                                                                                \
                                                                                                     \
    static inline void vector_erase_3_##N(Vector_##N *this, size_t idx, size_t size)                 \
    {                                                                                                \
        if (this == NULL)                                                                            \
            error("erase called on NULL " #E);                                                       \
        if (this->size <= idx || this->size < idx + size)                                            \
            error(#E " erase out of range");                                                         \
                                                                                                     \
        memmove(this->arr + idx, this->arr + idx + size,                                             \
                (this->size - size - idx) * sizeof(T));                                              \
        this->size -= size;                                                                          \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define Vector(N) Vector_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @param 2. Container(T) *new_container(N, size_t size);
 * @param 3. Container(T) *new_container(N, size_t size, T data);
 * @return pointer to newly constructed container
 */
#define new_vector(...) GET_MACRO(__VA_ARGS__, new_vector_5, new_vector_4, new_vector_3, new_vector_2, new_vector_1)(__VA_ARGS__)
#define new_vector_1(N) vector_new_vector_1_##N()
#define new_vector_2(N, arg) vector_new_vector_2_##N(arg)
#define new_vector_3(N, arg1, arg2) vector_new_vector_3_##N(arg1, arg2)
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_vector(N, other) vector_copy_vector_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_vector(N, other) vector_move_vector_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_vector(N, this) vector_delete_vector_##N(this)

#include "macros.h"