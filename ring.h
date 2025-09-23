#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "vector.h"

#define DEFINE_RING(T, N) DEFINE_RING_IMPL(T, N, ring)
#define DEFINE_RING_IMPL(T, N, E)                                          \
                                                                           \
    struct Ring_functions_##N;                                             \
                                                                           \
    DEFINE_VECTOR_IMPL(T, ring_##N, E)                                     \
                                                                           \
    typedef struct                                                         \
    {                                                                      \
        size_t head;                                                       \
        size_t tail;                                                       \
        Vector_ring_##N *vec;                                              \
        struct Ring_functions_##N *functions;                              \
    } Ring_##N;                                                            \
                                                                           \
    typedef struct Ring_functions_##N                                      \
    {                                                                      \
        int (*empty)(Ring_##N *);                                          \
        void (*reserve)(Ring_##N *, size_t);                               \
        size_t (*size)(Ring_##N *);                                        \
        size_t (*capacity)(Ring_##N *);                                    \
        T *(*front)(Ring_##N *);                                           \
        T *(*back)(Ring_##N *);                                            \
        void (*clear)(Ring_##N *);                                         \
        void (*push_front)(Ring_##N *, T);                                 \
        void (*push_back)(Ring_##N *, T);                                  \
        void (*pop_front)(Ring_##N *);                                     \
        void (*pop_back)(Ring_##N *);                                      \
    } Ring_functions_##N;                                                  \
                                                                           \
    static inline void ring_grow_##N(Ring_##N *this, size_t size);         \
                                                                           \
    static inline Ring_##N *ring_new_ring_1_##N();                         \
    static inline Ring_##N *ring_copy_ring_##N(const Ring_##N *other);     \
    static inline Ring_##N *ring_move_ring_##N(Ring_##N *other);           \
    static inline void ring_delete_ring_##N(Ring_##N *this);               \
                                                                           \
    static inline int ring_empty_##N(Ring_##N *this);                      \
    static inline void ring_reserve_##N(Ring_##N *this, size_t size);      \
    static inline size_t ring_size_##N(Ring_##N *this);                    \
    static inline size_t ring_capacity_##N(Ring_##N *this);                \
    static inline T *ring_front_##N(Ring_##N *this);                       \
    static inline T *ring_back_##N(Ring_##N *this);                        \
                                                                           \
    static inline void ring_clear_##N(Ring_##N *this);                     \
    static inline void ring_push_front_##N(Ring_##N *this, T data);        \
    static inline void ring_push_back_##N(Ring_##N *this, T data);         \
    static inline void ring_pop_front_##N(Ring_##N *this);                 \
    static inline void ring_pop_back_##N(Ring_##N *this);                  \
                                                                           \
    static Ring_functions_##N ring_funcs_##N = {                           \
        &ring_empty_##N,                                                   \
        &ring_reserve_##N,                                                 \
        &ring_size_##N,                                                    \
        &ring_capacity_##N,                                                \
        &ring_front_##N,                                                   \
        &ring_back_##N,                                                    \
        &ring_clear_##N,                                                   \
        &ring_push_front_##N,                                              \
        &ring_push_back_##N,                                               \
        &ring_pop_front_##N,                                               \
        &ring_pop_back_##N,                                                \
    };                                                                     \
                                                                           \
    static inline void ring_grow_##N(Ring_##N *this, size_t size)          \
    {                                                                      \
        Vector_ring_##N *vec = this->vec;                                  \
        size_t capacity = vec->capacity;                                   \
                                                                           \
        vector_grow_ring_##N(vec, size);                                   \
                                                                           \
        if (vec->capacity != capacity && this->tail < this->head)          \
        {                                                                  \
            memmove(vec->arr + this->head + vec->capacity - capacity,      \
                    vec->arr + this->head,                                 \
                    sizeof(T) * (capacity - this->head));                  \
                                                                           \
            this->head += vec->capacity - capacity;                        \
        }                                                                  \
    }                                                                      \
                                                                           \
    static inline Ring_##N *ring_new_ring_1_##N()                          \
    {                                                                      \
        Ring_##N *this = malloc(sizeof(Ring_##N));                         \
        if (this == NULL)                                                  \
            error("failed allocation");                                    \
                                                                           \
        this->vec = new_vector(ring_##N, 0);                               \
        this->head = 0;                                                    \
        this->tail = 0;                                                    \
        this->functions = &ring_funcs_##N;                                 \
                                                                           \
        return this;                                                       \
    }                                                                      \
                                                                           \
    static inline Ring_##N *ring_copy_ring_##N(const Ring_##N *other)      \
    {                                                                      \
        if (other == NULL)                                                 \
            error("copy constructor called on NULL " #E);                  \
                                                                           \
        Ring_##N *this = malloc(sizeof(Ring_##N));                         \
        if (this == NULL)                                                  \
            error("failed allocation");                                    \
                                                                           \
        this->vec = copy_vector(ring_##N, other->vec);                     \
        this->head = other->head;                                          \
        this->tail = other->tail;                                          \
        this->functions = &ring_funcs_##N;                             \
                                                                           \
        return this;                                                       \
    }                                                                      \
                                                                           \
    static inline Ring_##N *ring_move_ring_##N(Ring_##N *other)            \
    {                                                                      \
        if (other == NULL)                                                 \
            error("move constructor called on NULL" #E);                   \
                                                                           \
        Ring_##N *this = malloc(sizeof(Ring_##N));                         \
        if (this == NULL)                                                  \
            error("failed allocation");                                    \
                                                                           \
        this->vec = move_vector(ring_##N, other->vec);                     \
        this->head = other->head;                                          \
        this->tail = other->tail;                                          \
        this->functions = &ring_funcs_##N;                             \
                                                                           \
        other->head = 0;                                                   \
        other->tail = 0;                                                   \
                                                                           \
        return this;                                                       \
    }                                                                      \
                                                                           \
    static inline void ring_delete_ring_##N(Ring_##N *this)                \
    {                                                                      \
        if (this == NULL)                                                  \
            error("delete called on NULL " #E);                            \
                                                                           \
        delete_vector(ring_##N, this->vec);                                \
        free(this);                                                        \
    }                                                                      \
                                                                           \
    static inline int ring_empty_##N(Ring_##N *this)                       \
    {                                                                      \
        return empty(this->vec);                                           \
    }                                                                      \
                                                                           \
    static inline void ring_reserve_##N(Ring_##N *this, size_t size)       \
    {                                                                      \
        if (this == NULL)                                                  \
            error("reserve called on NULL " #E);                           \
                                                                           \
        ring_grow_##N(this, size);                                         \
    }                                                                      \
                                                                           \
    static inline size_t ring_size_##N(Ring_##N *this)                     \
    {                                                                      \
        return size(this->vec);                                            \
    }                                                                      \
                                                                           \
    static inline size_t ring_capacity_##N(Ring_##N *this)                 \
    {                                                                      \
        return capacity(this->vec);                                        \
    }                                                                      \
                                                                           \
    static inline T *ring_front_##N(Ring_##N *this)                        \
    {                                                                      \
        if (this == NULL)                                                  \
            error("front called on NULL " #E);                             \
        if (empty(this->vec))                                              \
            error("front called on Empty " #E);                            \
                                                                           \
        return this->vec->arr + this->head;                                \
    }                                                                      \
                                                                           \
    static inline T *ring_back_##N(Ring_##N *this)                         \
    {                                                                      \
        if (this == NULL)                                                  \
            error("back called on NULL " #E);                              \
        if (empty(this->vec))                                              \
            error("back called on Empty " #E);                             \
                                                                           \
        return this->vec->arr + this->tail;                                \
    }                                                                      \
                                                                           \
    static inline void ring_clear_##N(Ring_##N *this)                      \
    {                                                                      \
        clear(this->vec);                                                  \
        this->head = 0;                                                    \
        this->tail = 0;                                                    \
    }                                                                      \
                                                                           \
    static inline void ring_push_front_##N(Ring_##N *this, T data)         \
    {                                                                      \
        if (this == NULL)                                                  \
            error("push front called on NULL " #E);                        \
                                                                           \
        Vector_ring_##N *vec = this->vec;                                  \
        ring_grow_##N(this, vec->size + 1);                                \
                                                                           \
        if (vec->size > 0)                                                 \
            this->head = (this->head + vec->capacity - 1) % vec->capacity; \
                                                                           \
        vec->arr[this->head] = data;                                       \
        vec->size++;                                                       \
    }                                                                      \
                                                                           \
    static inline void ring_push_back_##N(Ring_##N *this, T data)          \
    {                                                                      \
        if (this == NULL)                                                  \
            error("push back called on NULL " #E);                         \
                                                                           \
        Vector_ring_##N *vec = this->vec;                                  \
        ring_grow_##N(this, vec->size + 1);                                \
                                                                           \
        if (vec->size > 0)                                                 \
            this->tail = (this->tail + 1) % vec->capacity;                 \
                                                                           \
        vec->arr[this->tail] = data;                                       \
        vec->size++;                                                       \
    }                                                                      \
                                                                           \
    static inline void ring_pop_front_##N(Ring_##N *this)                  \
    {                                                                      \
        if (this == NULL)                                                  \
            error("pop front called on NULL " #E);                         \
        if (this->vec->size == 0)                                          \
            error("pop front called on empty " #E);                        \
                                                                           \
        Vector_ring_##N *vec = this->vec;                                  \
                                                                           \
        if (vec->size > 1)                                                 \
            this->head = (this->head + 1) % vec->capacity;                 \
                                                                           \
        vec->size--;                                                       \
    }                                                                      \
                                                                           \
    static inline void ring_pop_back_##N(Ring_##N *this)                   \
    {                                                                      \
        if (this == NULL)                                                  \
            error("pop back called on NULL " #E);                          \
        if (this->vec->size == 0)                                          \
            error("pop back called on empty " #E);                         \
                                                                           \
        Vector_ring_##N *vec = this->vec;                                  \
                                                                           \
        if (vec->size > 1)                                                 \
            this->tail = (this->tail + vec->capacity - 1) % vec->capacity; \
                                                                           \
        vec->size--;                                                       \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define Ring(N) Ring_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @return pointer to newly constructed container
 */
#define new_ring(...) GET_MACRO(__VA_ARGS__, new_ring_5, new_ring_4, new_ring_3, new_ring_2, new_ring_1)(__VA_ARGS__)
#define new_ring_1(N) ring_new_ring_1_##N()
// #define new_ring_2(N, arg) ring_new_ring_2_##N(arg)
// #define new_ring_3(N, arg1, arg2) ring_new_ring_3_##N(arg1, arg2)
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_ring(N, other) ring_copy_ring_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_ring(N, other) ring_move_ring_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_ring(N, this) ring_delete_ring_##N(this)

#include "macros.h"