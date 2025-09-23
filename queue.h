#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "global.h"
#include "ring.h"

#define DEFINE_STACK(T, N)                                                  \
                                                                            \
    DEFINE_RING_IMPL(T, queue_##N, queue)                                   \
                                                                            \
    struct Queue_functions_##N;                                             \
                                                                            \
    typedef struct                                                          \
    {                                                                       \
        Ring_queue_##N *ring;                                               \
        struct Queue_functions_##N *functions;                              \
    } Queue_##N;                                                            \
                                                                            \
    typedef struct Queue_functions_##N                                      \
    {                                                                       \
        int (*empty)(Queue_##N *);                                          \
        void (*reserve)(Queue_##N *, size_t);                               \
        size_t (*size)(Queue_##N *);                                        \
        size_t (*capacity)(Queue_##N *);                                    \
        T *(*front)(Queue_##N *);                                           \
        T *(*back)(Queue_##N *);                                            \
        void (*clear)(Queue_##N *);                                         \
        void (*push)(Queue_##N *, T);                                       \
        void (*pop)(Queue_##N *);                                           \
    } Queue_functions_##N;                                                  \
                                                                            \
    static inline Queue_##N *queue_new_queue_1_##N();                       \
    static inline Queue_##N *queue_copy_queue_##N(const Queue_##N *other);  \
    static inline Queue_##N *queue_move_queue_##N(Queue_##N *other);        \
    static inline void queue_delete_queue_##N(Queue_##N *this);             \
                                                                            \
    static inline int queue_empty_##N(Queue_##N *this);                     \
    static inline void queue_reserve_##N(Queue_##N *this, size_t capacity); \
    static inline size_t queue_size_##N(Queue_##N *this);                   \
    static inline size_t queue_capacity_##N(Queue_##N *this);               \
    static inline T *queue_front_##N(Queue_##N *this);                      \
    static inline T *queue_back_##N(Queue_##N *this);                       \
                                                                            \
    static inline void queue_clear_##N(Queue_##N *this);                    \
    static inline void queue_push_##N(Queue_##N *this, T data);             \
    static inline void queue_pop_##N(Queue_##N *this);                      \
                                                                            \
    static Queue_functions_##N queue_funcs_##N = {                          \
        &queue_empty_##N,                                                   \
        &queue_reserve_##N,                                                 \
        &queue_size_##N,                                                    \
        &queue_capacity_##N,                                                \
        &queue_front_##N,                                                   \
        &queue_back_##N,                                                    \
        &queue_clear_##N,                                                   \
        &queue_push_##N,                                                    \
        &queue_pop_##N,                                                     \
    };                                                                      \
                                                                            \
    static inline Queue_##N *queue_new_queue_1_##N()                        \
    {                                                                       \
        Queue_##N *this = malloc(sizeof(Queue_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = new_ring(queue_##N);                                            \
        this->functions = &queue_funcs_##N;                             \
    }                                                                       \
                                                                            \
    static inline Queue_##N *queue_copy_queue_##N(const Queue_##N *other)   \
    {                                                                       \
        Queue_##N *this = malloc(sizeof(Queue_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = copy_ring(queue_##N, other->ring);                                \
        this->functions = &queue_funcs_##N;                             \
    }                                                                       \
                                                                            \
    static inline Queue_##N *queue_move_queue_##N(Queue_##N *other)         \
    {                                                                       \
        Queue_##N *this = malloc(sizeof(Queue_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = move_ring(queue_##N, other->ring);                                \
        this->functions = &queue_funcs_##N;                             \
    }                                                                       \
                                                                            \
    static inline void queue_delete_queue_##N(Queue_##N *this)              \
    {                                                                       \
        delete_ring(ring_##N, this->ring);                                  \
        free(this);                                                         \
    }                                                                       \
                                                                            \
    static inline int queue_empty_##N(Queue_##N *this)                      \
    {                                                                       \
        return empty(this->ring);                                           \
    }                                                                       \
                                                                            \
    static inline void queue_reserve_##N(Queue_##N *this, size_t capacity)  \
    {                                                                       \
        reserve(this->ring, capacity);                                      \
    }                                                                       \
                                                                            \
    static inline size_t queue_size_##N(Queue_##N *this)                    \
    {                                                                       \
        return size(this->ring);                                            \
    }                                                                       \
                                                                            \
    static inline size_t queue_capacity_##N(Queue_##N *this)                \
    {                                                                       \
        return capacity(this->ring);                                        \
    }                                                                       \
                                                                            \
    static inline T *queue_front_##N(Queue_##N *this)                       \
    {                                                                       \
        return &front(this->ring);                                          \
    }                                                                       \
                                                                            \
    static inline T *queue_back_##N(Queue_##N *this)                        \
    {                                                                       \
        return &back(this->ring);                                           \
    }                                                                       \
                                                                            \
    static inline void queue_clear_##N(Queue_##N *this)                     \
    {                                                                       \
        clear(this->ring);                                                  \
    }                                                                       \
                                                                            \
    static inline void queue_push_##N(Queue_##N *this, T data)              \
    {                                                                       \
        push_back(this->ring, data);                                        \
    }                                                                       \
                                                                            \
    static inline void queue_pop_##N(Queue_##N *this)                       \
    {                                                                       \
        pop_front(this->ring);                                              \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define Queue(N) Queue_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @return pointer to newly constructed container
 */
#define new_queue(...) GET_MACRO(__VA_ARGS__, new_queue_5, new_queue_4, new_queue_3, new_queue_2, new_queue_1)(__VA_ARGS__)
#define new_queue_1(N) queue_new_queue_1_##N()
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_queue(N, other) queue_copy_queue_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_queue(N, other) queue_move_queue_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_queue(N, this) queue_delete_queue_##N(this)

#include "macros.h"