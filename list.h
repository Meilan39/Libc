#include <stdlib.h>
#include <stdio.h>

#include "global.h"

#define DEFINE_LIST(T, N) DEFINE_LIST_IMPL(T, N, "list")
#define DEFINE_LIST_IMPL(T, N, ERROR_NAME)                                       \
                                                                                 \
    struct List_functions_##N;                                                   \
                                                                                 \
    typedef struct List_node_##N                                                 \
    {                                                                            \
        T data;                                                                  \
        struct List_node_##N *next;                                              \
    } List_node_##N;                                                             \
                                                                                 \
    typedef struct                                                               \
    {                                                                            \
        size_t size;                                                             \
        List_node_##N *head;                                                     \
        struct List_functions_##N *functions;                                    \
    } List_##N;                                                                  \
                                                                                 \
    typedef struct List_functions_##N                                            \
    {                                                                            \
        int (*empty)(List_##N *);                                                \
        size_t (*size)(List_##N *);                                              \
        T *(*at)(List_##N *, size_t);                                            \
        T *(*front)(List_##N *);                                                 \
        void (*clear)(List_##N *);                                               \
        void (*push_front)(List_##N *, T);                                       \
        void (*pop_front)(List_##N *);                                           \
        void (*insert_3)(List_##N *, size_t, T);                                 \
        void (*erase_2)(List_##N *, size_t);                                     \
    } List_functions_##N;                                                        \
                                                                                 \
    static List_functions_##N list_funcs_##N;                                    \
                                                                                 \
    static inline List_node_##N *list_new_node_##N(T data, List_node_##N *next); \
                                                                                 \
    static inline List_##N *list_new_list_1_##N();                               \
    static inline List_##N *list_new_list_2_##N(size_t size);                    \
    static inline List_##N *list_new_list_3_##N(size_t size, T data);            \
    static inline List_##N *list_copy_list_##N(const List_##N *other);           \
    static inline List_##N *list_move_list_##N(List_##N *other);                 \
    static inline void list_delete_list_##N(List_##N *this);                     \
                                                                                 \
    static inline int list_empty_##N(List_##N *this);                            \
    static inline size_t list_size_##N(List_##N *this);                          \
    static inline T *list_at_##N(List_##N *this, size_t idx);                    \
    static inline T *list_front_##N(List_##N *this);                             \
                                                                                 \
    static inline void list_clear_##N(List_##N *this);                           \
    static inline void list_push_front_##N(List_##N *this, T data);              \
    static inline void list_pop_front_##N(List_##N *this);                       \
    static inline void list_insert_3_##N(List_##N *this, size_t idx, T data);    \
    static inline void list_erase_2_##N(List_##N *this, size_t idx);             \
                                                                                 \
    static List_functions_##N list_funcs_##N = {                                 \
        &list_empty_##N,                                                         \
        &list_size_##N,                                                          \
        &list_at_##N,                                                            \
        &list_front_##N,                                                         \
        &list_clear_##N,                                                         \
        &list_push_front_##N,                                                    \
        &list_pop_front_##N,                                                     \
        &list_insert_3_##N,                                                      \
        &list_erase_2_##N,                                                       \
    };                                                                           \
                                                                                 \
    static inline List_node_##N *list_new_node_##N(T data, List_node_##N *next)  \
    {                                                                            \
        List_node_##N *node = malloc(sizeof(List_node_##N));                     \
        if (node == NULL)                                                        \
            error("failled allocation");                                         \
        node->data = data;                                                       \
        node->next = next;                                                       \
        return node;                                                             \
    }                                                                            \
                                                                                 \
    static inline List_##N *list_new_list_1_##N()                                \
    {                                                                            \
        List_##N *this = malloc(sizeof(List_##N));                               \
        if (this == NULL)                                                        \
            error("failled allocation");                                         \
        this->size = 0;                                                          \
        this->head = NULL;                                                       \
        this->functions = &list_funcs_##N;                                       \
        return this;                                                             \
    }                                                                            \
                                                                                 \
    static inline List_##N *list_new_list_2_##N(size_t size)                     \
    {                                                                            \
        List_##N *this = list_new_list_1_##N();                                  \
        for (size_t i = 0; i < size; i++)                                        \
            list_push_front_##N(this, 0);                                        \
        return this;                                                             \
    }                                                                            \
                                                                                 \
    static inline List_##N *list_new_list_3_##N(size_t size, T data)             \
    {                                                                            \
        List_##N *this = list_new_list_1_##N();                                  \
        for (size_t i = 0; i < size; i++)                                        \
            list_push_front_##N(this, data);                                     \
        return this;                                                             \
    }                                                                            \
                                                                                 \
    static inline List_##N *list_copy_list_##N(const List_##N *other)            \
    {                                                                            \
        if (other == NULL)                                                       \
            error("copy constructor called on NULL " ERROR_NAME);                \
                                                                                 \
        List_##N *this = list_new_list_1_##N();                                  \
        List_node_##N *next = other->head;                                       \
        List_node_##N **cur = &this->head;                                       \
        for (size_t i = 0; i < other->size; i++)                                 \
        {                                                                        \
            *cur = list_new_node_##N(next->data, NULL);                          \
            next = next->next;                                                   \
            cur = &((*cur)->next);                                               \
        }                                                                        \
        this->size = other->size;                                                \
        return this;                                                             \
    }                                                                            \
                                                                                 \
    static inline List_##N *list_move_list_##N(List_##N *other)                  \
    {                                                                            \
        if (other == NULL)                                                       \
            error("move constructor called on NULL " ERROR_NAME);                \
                                                                                 \
        List_##N *this = list_new_list_1_##N();                                  \
        this->size = other->size;                                                \
        this->head = other->head;                                                \
        other->size = 0;                                                         \
        other->head = NULL;                                                      \
        return this;                                                             \
    }                                                                            \
                                                                                 \
    static inline void list_delete_list_##N(List_##N *this)                      \
    {                                                                            \
        if (this == NULL)                                                        \
            return;                                                              \
                                                                                 \
        List_node_##N *next = this->head, *temp;                                 \
        for (size_t i = 0; i < this->size; i++)                                  \
        {                                                                        \
            temp = next;                                                         \
            next = next->next;                                                   \
            free(temp);                                                          \
        }                                                                        \
        free(this);                                                              \
    }                                                                            \
                                                                                 \
    static inline int list_empty_##N(List_##N *this)                             \
    {                                                                            \
        if (this == NULL)                                                        \
            error("empty called on NULL " ERROR_NAME);                           \
                                                                                 \
        return this->size == 0;                                                  \
    }                                                                            \
                                                                                 \
    static inline size_t list_size_##N(List_##N *this)                           \
    {                                                                            \
        if (this == NULL)                                                        \
            error("size called on NULL " ERROR_NAME);                            \
                                                                                 \
        return this->size;                                                       \
    }                                                                            \
                                                                                 \
    static inline T *list_at_##N(List_##N *this, size_t idx)                     \
    {                                                                            \
        if (this == NULL)                                                        \
            error("at called on NULL " ERROR_NAME);                              \
        if (this->size <= idx)                                                   \
            error(ERROR_NAME " index out of bounds");                            \
                                                                                 \
        List_node_##N *next = this->head;                                        \
        for (size_t i = 0; i < idx; i++)                                         \
            next = next->next;                                                   \
        return &(next->data);                                                    \
    }                                                                            \
                                                                                 \
    static inline T *list_front_##N(List_##N *this)                              \
    {                                                                            \
        if (this == NULL)                                                        \
            error("front called on NULL " ERROR_NAME);                           \
        if (this->size == 0)                                                     \
            error("front called on empty " ERROR_NAME);                          \
                                                                                 \
        return &(this->head->data);                                              \
    }                                                                            \
                                                                                 \
    static inline void list_clear_##N(List_##N *this)                            \
    {                                                                            \
        if (this == NULL)                                                        \
            error("clear called on NULL " ERROR_NAME);                           \
                                                                                 \
        List_node_##N *next = this->head, *temp;                                 \
        for (size_t i = 0; i < this->size; i++)                                  \
        {                                                                        \
            temp = next;                                                         \
            next = next->next;                                                   \
            free(temp);                                                          \
        }                                                                        \
                                                                                 \
        this->head = NULL;                                                       \
        this->size = 0;                                                          \
    }                                                                            \
                                                                                 \
    static inline void list_push_front_##N(List_##N *this, T data)               \
    {                                                                            \
        if (this == NULL)                                                        \
            error("push front called on NULL " ERROR_NAME);                      \
                                                                                 \
        List_node_##N *new = list_new_node_##N(data, this->head);                \
        this->head = new;                                                        \
        this->size++;                                                            \
    }                                                                            \
                                                                                 \
    static inline void list_pop_front_##N(List_##N *this)                        \
    {                                                                            \
        if (this == NULL)                                                        \
            error("pop front called on NULL " ERROR_NAME);                       \
        if (this->size == 0)                                                     \
            error("pop front called on empty " ERROR_NAME);                      \
                                                                                 \
        List_node_##N *temp = this->head;                                        \
        this->head = this->head->next;                                           \
        this->size--;                                                            \
                                                                                 \
        free(temp);                                                              \
    }                                                                            \
                                                                                 \
    static inline void list_insert_3_##N(List_##N *this, size_t idx, T data)     \
    {                                                                            \
        if (this == NULL)                                                        \
            error("insert called on NULL " ERROR_NAME);                          \
        if (this->size < idx)                                                    \
            error(ERROR_NAME " insert out of bounds");                           \
                                                                                 \
        List_node_##N **next = &this->head;                                      \
        for (size_t i = 0; i < idx; i++)                                         \
            next = &((*next)->next);                                             \
        List_node_##N *new = list_new_node_##N(data, *next);                     \
        *next = new;                                                             \
        this->size++;                                                            \
    }                                                                            \
                                                                                 \
    static inline void list_erase_2_##N(List_##N *this, size_t idx)              \
    {                                                                            \
        if (this == NULL)                                                        \
            error("erase called on NULL " ERROR_NAME);                           \
        if (this->size == 0)                                                     \
            error("erase called on empty " ERROR_NAME);                          \
        if (this->size <= idx)                                                   \
            error(ERROR_NAME " erase out of bounds");                            \
                                                                                 \
        List_node_##N **next = &this->head;                                      \
        for (size_t i = 0; i < idx; i++)                                         \
            next = &((*next)->next);                                             \
        List_node_##N *temp = *next;                                             \
        *next = temp->next;                                                      \
        this->size--;                                                            \
                                                                                 \
        free(temp);                                                              \
    }

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define List(N) List_##N
/**
 * @brief constructor for a new container.
 * @param 1. Container(T) *new_container(N);
 * @param 2. Container(T) *new_container(N, size_t size);
 * @param 3. Container(T) *new_container(N, size_t size, T data);
 * @return pointer to newly constructed container
 */
#define new_list(...) GET_MACRO(__VA_ARGS__, new_list_5, new_list_4, new_list_3, new_list_2, new_list_1)(__VA_ARGS__)
#define new_list_1(N) list_new_list_1_##N()
#define new_list_2(N, arg) list_new_list_2_##N(arg)
#define new_list_3(N, arg1, arg2) list_new_list_3_##N(arg1, arg2)
/**
 * @brief copy constructor for a new container
 * @param N typename
 * @param other container to copy
 * @return pointer to newly constructed container
 */
#define copy_list(N, other) list_copy_list_##N(other)
/**
 * @brief move constructor for a new container
 * @param N typename
 * @param other container to move
 * @return pointer to newly constructed container
 */
#define move_list(N, other) list_move_list_##N(other)
/**
 * @brief destructor
 * @param N typename
 * @param this container to destruct
 */
#define delete_list(N, this) list_delete_list_##N(this)

#include "macros.h"
