#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "global.h"
#include "ring.h"

#define DEFINE_STACK(T, N)                                                  \
                                                                            \
    DEFINE_RING_IMPL(T, stack_##N, stack)                                   \
                                                                            \
    struct Stack_functions_##N;                                             \
                                                                            \
    typedef struct                                                          \
    {                                                                       \
        Ring_stack_##N *ring;                                               \
        struct Stack_functions_##N *functions;                              \
    } Stack_##N;                                                            \
                                                                            \
    typedef struct Stack_functions_##N                                      \
    {                                                                       \
        int (*empty)(Stack_##N *);                                          \
        void (*reserve)(Stack_##N *, size_t);                               \
        size_t (*size)(Stack_##N *);                                        \
        size_t (*capacity)(Stack_##N *);                                    \
        T *(*top)(Stack_##N *);                                             \
        void (*clear)(Stack_##N *);                                         \
        void (*push)(Stack_##N *, T);                                       \
        void (*pop)(Stack_##N *);                                           \
    } Stack_functions_##N;                                                  \
                                                                            \
    static inline Stack_##N *stack_new_stack_1_##N();                       \
    static inline Stack_##N *stack_copy_stack_##N(const Stack_##N *other);  \
    static inline Stack_##N *stack_move_stack_##N(Stack_##N *other);        \
    static inline void stack_delete_stack_##N(Stack_##N *this);             \
                                                                            \
    static inline int stack_empty_##N(Stack_##N *this);                     \
    static inline void stack_reserve_##N(Stack_##N *this, size_t capacity); \
    static inline size_t stack_size_##N(Stack_##N *this);                   \
    static inline size_t stack_capacity_##N(Stack_##N *this);               \
    static inline T *stack_top_##N(Stack_##N *this);                        \
                                                                            \
    static inline void stack_clear_##N(Stack_##N *this);                    \
    static inline void stack_push_##N(Stack_##N *this, T data);             \
    static inline void stack_pop_##N(Stack_##N *this);                      \
                                                                            \
    static Stack_functions_##N stack_funcs_##N = {                          \
        &stack_empty_##N,                                                   \
        &stack_reserve_##N,                                                 \
        &stack_size_##N,                                                    \
        &stack_capacity_##N,                                                \
        &stack_top_##N,                                                     \
        &stack_clear_##N,                                                   \
        &stack_push_##N,                                                    \
        &stack_pop_##N,                                                     \
    };                                                                      \
                                                                            \
    static inline Stack_##N *stack_new_stack_1_##N()                        \
    {                                                                       \
        Stack_##N *this = malloc(sizeof(Stack_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = new_ring(stack_##N);                                   \
        this->functions = &stack_funcs_##N;                                 \
                                                                            \
        return this;                                                        \
    }                                                                       \
                                                                            \
    static inline Stack_##N *stack_copy_stack_##N(const Stack_##N *other)   \
    {                                                                       \
        Stack_##N *this = malloc(sizeof(Stack_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = copy_ring(stack_##N, other->ring);                     \
        this->functions = &stack_funcs_##N;                                 \
                                                                            \
        return this;                                                        \
    }                                                                       \
                                                                            \
    static inline Stack_##N *stack_move_stack_##N(Stack_##N *other)         \
    {                                                                       \
        Stack_##N *this = malloc(sizeof(Stack_##N));                        \
        if (this == NULL)                                                   \
            error("failed allocation");                                     \
                                                                            \
        this->ring = move_ring(stack_##N, other->ring);                     \
        this->functions = &stack_funcs_##N;                                 \
                                                                            \
        return this;                                                        \
    }                                                                       \
                                                                            \
    static inline void stack_delete_stack_##N(Stack_##N *this)              \
    {                                                                       \
        if (this == NULL)                                                   \
            return;                                                         \
                                                                            \
        delete_ring(stack_##N, this->ring);                                 \
        free(this);                                                         \
    }                                                                       \
                                                                            \
    static inline int stack_empty_##N(Stack_##N *this)                      \
    {                                                                       \
        return empty(this->ring);                                           \
    }                                                                       \
                                                                            \
    static inline void stack_reserve_##N(Stack_##N *this, size_t capacity)  \
    {                                                                       \
        reserve(this->ring, capacity);                                      \
    }                                                                       \
                                                                            \
    static inline size_t stack_size_##N(Stack_##N *this)                    \
    {                                                                       \
        return size(this->ring);                                            \
    }                                                                       \
                                                                            \
    static inline size_t stack_capacity_##N(Stack_##N *this)                \
    {                                                                       \
        return capacity(this->ring);                                        \
    }                                                                       \
                                                                            \
    static inline T *stack_top_##N(Stack_##N *this)                         \
    {                                                                       \
        return &back(this->ring);                                           \
    }                                                                       \
                                                                            \
    static inline void stack_clear_##N(Stack_##N *this)                     \
    {                                                                       \
        clear(this->ring);                                                  \
    }                                                                       \
                                                                            \
    static inline void stack_push_##N(Stack_##N *this, T data)              \
    {                                                                       \
        push_back(this->ring, data);                                        \
    }                                                                       \
                                                                            \
    static inline void stack_pop_##N(Stack_##N *this)                       \
    {                                                                       \
        pop_back(this->ring);                                               \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define Stack(N) Stack_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @return pointer to newly constructed container
 */
#define new_stack(...) GET_MACRO(__VA_ARGS__, new_stack_5, new_stack_4, new_stack_3, new_stack_2, new_stack_1)(__VA_ARGS__)
#define new_stack_1(N) stack_new_stack_1_##N()
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_stack(N, other) stack_copy_stack_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_stack(N, other) stack_move_stack_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_stack(N, this) stack_delete_stack_##N(this)

#include "macros.h"