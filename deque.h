#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "vector.h"

#define DEQUE_CONTAINER_SIZE

#define DEFINE_DEQUE(T, N) DEFINE_DEQUE_IMPL(T, N, deque)
#define DEFINE_DEQUE_IMPL(T, N, E)                                                                  \
                                                                                                     \
    struct Deque_functions_##N;                                                                     \
                                                                                                     \
    typedef struct\
    {\
        size_t head;\
        size_t tail;\
        T *arr;\
    } Deque_container_##N;\
    \
    DEFINE_VECTOR_IMPL(Deque_container_##N*, deque_##N, deque)                                                       \
    \
    typedef struct                                                                                   \
    {                                                                                                \
        size_t size;\
        size_t head;                                                                                 \
        size_t tail;                                                                                 \
        Vector_deque_##N *vec;                                                                     \                                                                                \
        struct Deque_functions_##N *functions;                                                      \
    } Deque_##N;                                                                                    \
                                                                                                     \
    typedef struct Deque_functions_##N                                                              \
    {                                                                                                \
        int (*empty)(Deque_##N *);                                                                  \
        size_t (*size)(Deque_##N *);                                                                \
        T (*front)(Deque_##N *);                                                                    \
        T (*back)(Deque_##N *);                                                                     \
        void (*clear)(Deque_##N *);                                                                 \
        void (*push_front)(Deque_##N *, T);                                                          \
        void (*push_back)(Deque_##N *, T);                                                              \
        void (*pop_front)(Deque_##N *);                                                          \
        void (*pop_back)(Deque_##N *);                                                              \
    } Deque_functions_##N;                                                                          \
                                                                                                     \
    static inline Deque_container_##N *deque_new_container_##N();\
    static inline Deque_container_##N *deque_copy_container_##N(const Deque_container_##N *other);\
    static inline void deque_grow_##N(Deque_##N *this, size_t size);                               \
                                                                                                     \
    static inline Deque_##N *deque_new_deque_1_##N();                                             \
    static inline Deque_##N *deque_copy_deque_##N(const Deque_##N *other);                       \
    static inline Deque_##N *deque_move_deque_##N(Deque_##N *other);                             \
    static inline void deque_delete_deque_##N(Deque_##N *this);                                   \
                                                                                                     \
    static inline int deque_empty_##N(Deque_##N *this);                                            \
    static inline size_t deque_size_##N(Deque_##N *this);                                          \
    static inline T deque_front_##N(Deque_##N *this);                                              \
    static inline T deque_back_##N(Deque_##N *this);                                               \
                                                                                                     \
    static inline void deque_clear_##N(Deque_##N *this);                                           \
    static inline void deque_push_front_##N(Deque_##N *this, T data);                               \
    static inline void deque_push_back_##N(Deque_##N *this, T data);                                        \
    static inline void deque_pop_front_##N(Deque_##N *this);                               \
    static inline void deque_pop_back_##N(Deque_##N *this);                                        \
                                                                                                     \
    static Deque_functions_##N deque_funcs_##N = {                                                 \
        &deque_empty_##N,                                                                           \
        &deque_reserve_##N,                                                                         \
        &deque_shrink_##N,                                                                          \
        &deque_size_##N,                                                                            \
        &deque_capacity_##N,                                                                        \
        &deque_front_##N,                                                                           \
        &deque_back_##N,                                                                            \
        &deque_clear_##N,                                                                           \
        &deque_push_front_##N,                                                                       \
        &deque_push_back_##N,                                                                       \
        &deque_pop_front_##N,                                                                        \
        &deque_pop_back_##N,                                                                        \
    };\
    \
    static inline Deque_container_##N *deque_new_container_##N(); {\
        Deque_container_##N *this = malloc(sizeof(Deque_container_##N));\
        if(this == NULL)\
            error("allocation failed");\
        \
        this->arr = malloc(DEQUE_CONTAINER_SIZE * sizeof(T));\
        this->head = 0;\
        this->tail = 0;\
        \
        return this;\
    }\
    \
    static inline Deque_container_##N *deque_copy_container_##N(const Deque_container_##N *other) {\
        if(other == NULL)\
            return NULL;\
        \
        Deque_contaienr_##N *this = malloc(sizeof(Deque_container_##N));\
        if(this == NULL)\
            error("allocation failed"); \
        \
        memcpy(this->arr, other->arr, other->size * sizeof(T));\
        this->head = other->head;\
        this->tail = other->tail;\
        \
        return this;\
    }\
    \
    static inline Deque_##N *deque_new_deque_1_##N() \
    {\
        Deque_##N *this = malloc(sizeof(Deque_##N));\
        if(this == NULL)\
            error("failed allocation");\
        \
        Deque_container_##N *container = deque_new_container_##N();\
        this->vec = new_vector(deque_##N, 1, container);\
        this->size = 0;\
        this->head = 0;\
        this->tail = 0;\
        \
        return this; \
    }                                             \
    \
    static inline Deque_##N *deque_copy_deque_##N(const Deque_##N *other) {\
        \
        if(other == NULL)\
            error("copy constructor called on NULL deque"); \
        \
        Deque_##N *this = deque_new_deque_##N();\
        \
        this->vec = new_vector(deque_##N, other->size);\
        for(size_t i = 0; i < other->vec->capacity; i++)\
            this->vec->arr[i] = deque_copy_container_##N(other->vec->arr[i]);\
        \
        this->size = other->size; \
        this->head = other->head; \
        this->tail = other->tail; \
        \
        return this;\
    }                       \
    \
    static inline Deque_##N *deque_move_deque_##N(Deque_##N *other) {\
        \
        if(other == NULL)\
            error("move constructor called on NULL deque");\
        \
        Deque_##N *this = deque_new_deque_##N();\
        \
        this->vec = move_vector(deque_##N, other->vec);\
        \
        this->size = other->size;\
        this->head = other->head;\
        this->tail = other->tail;\
        \
        other->size = 0; \
        other->head = 0; \
        other->tail = 0;\
        \
        return this;\
    }                             \
    \
    static inline void deque_delete_deque_##N(Deque_##N *this) {\
        \
        if(this == NULL) \
            error("delete called on NULL deque");\
        \
        for(size_t i = 0; i < this->vec->capacity; i++) {\
            if(this->vec->arr[i] == NULL) \
                continue;\
            \
            free(this->vec->arr[i]->arr);\
            free(this->vec->arr[i]);\
        }\
        \
        delete_vector(this->vec);\
        free(this);\
    }                                   \
                                                                                                     \
    static inline int deque_empty_##N(Deque_##N *this) {\
        if(this == NULL) error("empty called on NULL deque");\
        \
        return this->size == 0;\
    }                                            \
    \
    static inline size_t deque_size_##N(Deque_##N *this) {\
        if(this == NULL) error("size called on NULL deque");\
        \
        return this->size;\ 
    }                                          \
    \
    static inline T *deque_front_##N(Deque_##N *this) {\
        if(this == NULL) error("front called on NULL deque");\
        \
        Deque_container_##N *container = this->vec->arr[this->head];
        return container->arr + container->head;
    }                                              \
    static inline T *deque_back_##N(Deque_##N *this);                                               \
                                                                                                     \
    static inline void deque_clear_##N(Deque_##N *this);                                           \
    static inline void deque_push_front_##N(Deque_##N *this, T data);                               \
    static inline void deque_push_back_##N(Deque_##N *this, T data);                                        \
    static inline void deque_pop_front_##N(Deque_##N *this);                               \
    static inline void deque_pop_back_##N(Deque_##N *this);                                        \
