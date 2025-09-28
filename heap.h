#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "vector.h"

#define DEFINE_HEAP(T, N) DEFINE_HEAP_IMPL(T, N, heap)
#define DEFINE_HEAP_IMPL(T, N, E)                                                                       \
                                                                                                        \
    struct Heap_functions_##N;                                                                          \
                                                                                                        \
    DEFINE_VECTOR_IMPL(T, heap_##N, E)                                                                  \
                                                                                                        \
    typedef struct                                                                                      \
    {                                                                                                   \
        Vector_heap_##N *vec;                                                                           \
        int (*cmp)(const T *, const T *);                                                               \
        struct Heap_functions_##N *functions;                                                           \
    } Heap_##N;                                                                                         \
                                                                                                        \
    typedef struct Heap_functions_##N                                                                   \
    {                                                                                                   \
        int (*empty)(Heap_##N *);                                                                       \
        void (*reserve)(Heap_##N *, size_t);                                                            \
        size_t (*size)(Heap_##N *);                                                                     \
        size_t (*capacity)(Heap_##N *);                                                                 \
        T *(*top)(Heap_##N *);                                                                          \
        void (*clear)(Heap_##N *);                                                                      \
        void (*push)(Heap_##N *, T);                                                                    \
        void (*pop)(Heap_##N *);                                                                        \
        void (*heapify)(Heap_##N *);                                                                    \
        void (*push_back)(Heap_##N *, T);                                                               \
    } Heap_functions_##N;                                                                               \
                                                                                                        \
    static inline int compare_min_##N(const T *a, const T *b);                                     \
    static inline int compare_max_##N(const T *a, const T *b);                                     \
                                                                                                        \
    static inline Heap_##N *heap_new_heap_1_##N();                                                      \
    static inline Heap_##N *heap_new_heap_2_##N(int (*cmp)(const T *, const T *));                      \
    static inline Heap_##N *heap_new_heap_3_##N(int (*cmp)(const T *, const T *), size_t size);         \
    static inline Heap_##N *heap_new_heap_4_##N(int (*cmp)(const T *, const T *), size_t size, T data); \
    static inline Heap_##N *heap_copy_heap_##N(const Heap_##N *other);                                  \
    static inline Heap_##N *heap_move_heap_##N(Heap_##N *other);                                        \
    static inline void heap_delete_heap_##N(Heap_##N *this);                                            \
                                                                                                        \
    static inline void heap_set_compare_##N(Heap_##N *this, int (*cmp)(const T *, const T *));          \
                                                                                                        \
    static inline int heap_empty_##N(Heap_##N *this);                                                   \
    static inline void heap_reserve_##N(Heap_##N *this, size_t size);                                   \
    static inline size_t heap_size_##N(Heap_##N *this);                                                 \
    static inline size_t heap_capacity_##N(Heap_##N *this);                                             \
    static inline T *heap_top_##N(Heap_##N *this);                                                      \
                                                                                                        \
    static inline void heap_clear_##N(Heap_##N *this);                                                  \
    static inline void heap_push_##N(Heap_##N *this, T data);                                           \
    static inline void heap_pop_##N(Heap_##N *this);                                                    \
    static inline void heap_heapify_##N(Heap_##N *this);                                                \
    static inline void heap_push_back_##N(Heap_##N *this, T data);                                      \
                                                                                                        \
    static Heap_functions_##N heap_funcs_##N = {                                                        \
        &heap_empty_##N,                                                                                \
        &heap_reserve_##N,                                                                              \
        &heap_size_##N,                                                                                 \
        &heap_capacity_##N,                                                                             \
        &heap_top_##N,                                                                                  \
        &heap_clear_##N,                                                                                \
        &heap_push_##N,                                                                                 \
        &heap_pop_##N,                                                                                  \
        &heap_heapify_##N,                                                                              \
        &heap_push_back_##N,                                                                            \
    };                                                                                                  \
                                                                                                        \
    static inline int compare_min_##N(const T *a, const T *b)                                      \
    {                                                                                                   \
        return *a < *b ? -1 : *a > *b;                                                                  \
    }                                                                                                   \
                                                                                                        \
    static inline int compare_max_##N(const T *a, const T *b)                                      \
    {                                                                                                   \
        return *a > *b ? -1 : *a < *b;                                                                  \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_new_heap_1_##N()                                                       \
    {                                                                                                   \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = new_vector(heap_##N);                                                               \
        this->functions = &heap_funcs_##N;                                                              \
        this->cmp = &compare_min_##N;                                                              \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_new_heap_2_##N(int (*cmp)(const T *, const T *))                       \
    {                                                                                                   \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = new_vector(heap_##N);                                                               \
        this->functions = &heap_funcs_##N;                                                              \
        this->cmp = cmp;                                                                                \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_new_heap_3_##N(int (*cmp)(const T *, const T *), size_t size)          \
    {                                                                                                   \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = new_vector(heap_##N, size);                                                         \
        this->functions = &heap_funcs_##N;                                                              \
        this->cmp = cmp;                                                                                \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_new_heap_4_##N(int (*cmp)(const T *, const T *), size_t size, T data)  \
    {                                                                                                   \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = new_vector(heap_##N, size, data);                                                   \
        this->functions = &heap_funcs_##N;                                                              \
        this->cmp = cmp;                                                                                \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_copy_heap_##N(const Heap_##N *other)                                   \
    {                                                                                                   \
        if (other == NULL)                                                                              \
            error("copy constructor called on NULL" #E);                                                \
                                                                                                        \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = copy_vector(heap_##N, other->vec);                                                  \
        this->functions = other->functions;                                                             \
        this->cmp = other->cmp;                                                                         \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline Heap_##N *heap_move_heap_##N(Heap_##N *other)                                         \
    {                                                                                                   \
        if (other == NULL)                                                                              \
            error("move constructor called on NULL" #E);                                                \
                                                                                                        \
        Heap_##N *this = malloc(sizeof(Heap_##N));                                                      \
        if (this == NULL)                                                                               \
            error("allocation failed");                                                                 \
                                                                                                        \
        this->vec = move_vector(heap_##N, other->vec);                                                  \
        this->functions = other->functions;                                                             \
        this->cmp = other->cmp;                                                                         \
                                                                                                        \
        return this;                                                                                    \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_delete_heap_##N(Heap_##N *this)                                             \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("delete called on NULL " #E);                                                         \
                                                                                                        \
        delete_vector(heap_##N, this->vec);                                                                       \
        free(this);                                                                                     \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_set_compare_##N(Heap_##N *this, int (*cmp)(const T *, const T *))           \
    {                                                                                                   \
        this->cmp = cmp;                                                                                \
    }                                                                                                   \
                                                                                                        \
    static inline int heap_empty_##N(Heap_##N *this)                                                    \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("empty called on NULL " #E);                                                          \
                                                                                                        \
        return empty(this->vec);                                                                        \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_reserve_##N(Heap_##N *this, size_t size)                                    \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("reserve called on NULL " #E);                                                        \
                                                                                                        \
        reserve(this->vec, size);                                                                       \
    }                                                                                                   \
    static inline size_t heap_size_##N(Heap_##N *this)                                                  \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("size called on NULL " #E);                                                           \
                                                                                                        \
        return size(this->vec);                                                                         \
    }                                                                                                   \
                                                                                                        \
    static inline size_t heap_capacity_##N(Heap_##N *this)                                              \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("capacity called on NULL " #E);                                                       \
                                                                                                        \
        return capacity(this->vec);                                                                     \
    }                                                                                                   \
                                                                                                        \
    static inline T *heap_top_##N(Heap_##N *this)                                                       \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("top called on NULL " #E);                                                            \
                                                                                                        \
        return &front(this->vec);                                                                       \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_clear_##N(Heap_##N *this)                                                   \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("clear called on NULL " #E);                                                          \
                                                                                                        \
        clear(this->vec);                                                                               \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_push_##N(Heap_##N *this, T data)                                            \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("push called on NULL " #E);                                                           \
                                                                                                        \
        Vector_heap_##N *vec = this->vec;                                                               \
        size_t i = vec->size;                                                                           \
                                                                                                        \
        push_back(vec, data);                                                                           \
                                                                                                        \
        while (i > 1)                                                                                   \
        {                                                                                               \
            if (this->cmp(vec->arr + i / 2 - 1, vec->arr + i - 1) <= 0)                                 \
                break;                                                                                  \
            LIBCSWAP(T, vec->arr + i - 1, vec->arr + i / 2 - 1)                                         \
            i /= 2;                                                                                     \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_pop_##N(Heap_##N *this)                                                     \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("pop called on NULL " #E);                                                            \
                                                                                                        \
        Vector_heap_##N *vec = this->vec;                                                               \
        size_t i = 1, k;                                                                                \
                                                                                                        \
        LIBCSWAP(T, vec->arr, vec->arr + vec->size - 1)                                                 \
        pop_back(vec);                                                                                  \
                                                                                                        \
        while (i * 2 <= vec->size)                                                                      \
        {                                                                                               \
            k = i * 2;                                                                                  \
            if (k < vec->size && this->cmp(vec->arr + k, vec->arr + k - 1) <= 0)                        \
                k++;                                                                                    \
            if (this->cmp(vec->arr + i - 1, vec->arr + k - 1) <= 0)                                     \
                break;                                                                                  \
            LIBCSWAP(T, vec->arr + i - 1, vec->arr + k - 1)                                             \
            i = k;                                                                                      \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_heapify_##N(Heap_##N *this)                                                 \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("heapify called on NULL " #E);                                                        \
                                                                                                        \
        Vector_heap_##N *vec = this->vec;                                                               \
        size_t maxIdx, k;                                                                               \
        T maxTri;                                                                                       \
                                                                                                        \
        for (size_t i = vec->size / 2; i > 1; i++)                                                      \
        {                                                                                               \
            maxTri = vec->arr[i - 1];                                                                   \
            k = i * 2;                                                                                  \
            if (k <= vec->size && this->cmp(vec->arr + k - 1, &maxTri) <= 0)                            \
            {                                                                                           \
                maxTri = vec->arr[k - 1];                                                               \
                maxIdx = k - 1;                                                                         \
            }                                                                                           \
            if (k < vec->size && this->cmp(vec->arr + k, &maxTri) <= 0)                                 \
            {                                                                                           \
                maxTri = vec->arr[k];                                                                   \
                maxIdx = k;                                                                             \
            }                                                                                           \
            if (this->cmp(&maxTri, vec->arr + i - 1) != 0)                                               \
            {                                                                                           \
                LIBCSWAP(T, vec->arr + i - 1, vec->arr + maxIdx)                                        \
            }                                                                                           \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    static inline void heap_push_back_##N(Heap_##N *this, T data)                                       \
    {                                                                                                   \
        if (this == NULL)                                                                               \
            error("push back called on NULL " #E);                                                      \
                                                                                                        \
        push_back(this->vec, data);                                                                     \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define Heap(N) Heap_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @return pointer to newly constructed container
 */
#define new_heap(...) GET_MACRO(__VA_ARGS__, new_heap_5, new_heap_4, new_heap_3, new_heap_2, new_heap_1)(__VA_ARGS__)
#define new_heap_1(N) heap_new_heap_1_##N()
#define new_heap_2(N, arg) heap_new_heap_2_##N(arg)
#define new_heap_3(N, arg1, arg2) heap_new_heap_3_##N(arg1, arg2)
#define new_heap_4(N, arg1, arg2, arg3) heap_new_heap_4_##N(arg1, arg2, arg3)
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_heap(N, other) heap_copy_heap_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_heap(N, other) heap_move_heap_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_heap(N, this) heap_delete_heap_##N(this)

#include "macros.h"