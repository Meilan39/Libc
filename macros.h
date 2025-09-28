#ifndef MACROS
#define MACROS

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
/**
 * @brief manually specify the compare method 
 * @param this container
 * @param cmp function pointer to type int (cmp*)(const T*, const T*)
 * @note Availability: heap
 */
#define set_compare(this, cmp) this->functions->set_compare(this, cmp); 
/**
 * @brief check if container is empty
 * @param this container
 * @return 0 if not empty, not 0 if empty
 * @note Availability: vector, list, string, stack
 */
#define empty(this) this->functions->empty(this)
/**
 * @brief reserve memory for container
 * @param this container
 * @param capacity memory to reserve passed as container size
 * @note Availability: vector, string, stack
 */
#define reserve(this, capacity) this->functions->reserve(this, capacity)
/**
 * @brief shrink capacity to container size
 * @param this container
 * @note Availability: vector, string, stack
 */
#define shrink(this) this->functions->shrink(this)
/**
 * @brief get size of container
 * @param this container
 * @return size of the container
 * @note Availability: vector, list, string, stack
 */
#define size(this) this->functions->size(this)
/**
 * @brief get memory capacity of container
 * @param this container
 * @return capacity of the container
 * @note Availability: vector, string, stasck
 */
#define capacity(this) this->functions->capacity(this)
/**
 * @brief access an element of the container with bounds checking
 * @param this container
 * @param idx index of element
 * @return element at the index
 * @note Availability: vector, list, string
 */
#define at(this, idx) *(this->functions->at(this, idx))
/**
 * @brief access front most element of the container
 * @param this container
 * @return element at the front
 * @note Availability: vector, list, string
 */
#define front(this) *(this->functions->front(this))
/**
 * @brief access rear most element of the container
 * @param this container
 * @return element at the back
 * @note Availability: vector, string
 */
#define back(this) *(this->functions->back(this))
/**
 * @brief get the top element of the stack
 * @return top element of the stack
 * @note Availability: stack
 */
#define top(this) *(this->functions->top(this))
/**
 * @brief clear the container
 * @param this container
 * @note size is set to zero, but maintains its capacity
 * @note Availability: vector, list, string
 */
#define clear(this) (this->functions->clear(this))
/**
 * @brief push element to the front of the container
 * @param this container
 * @param data data to push
 * @note Availability: vector, string, stack
 */
#define push_front(this, data) this->functions->push_front(this, data)
/**
 * @brief push element to the back of the container
 * @param this container
 * @param data data to push
 * @note Availability: list
 */
#define push_back(this, data) this->functions->push_back(this, data)
/**
 * @brief push a value to the stack
 * @param this stack
 * @note Availability: stack
 */
#define push(this, data) this->functions->push(this, data)
/**
 * @brief pop an element from the front of the container
 * @param this container
 * @note Availability: vector, string
 */
#define pop_front(this) this->functions->pop_front(this)
/**
 * @brief pop an element from the back of the container
 * @param this container
 * @note Availability: list
 */
#define pop_back(this) this->functions->pop_back(this)
/**
 * @brief pop an element from the stack
 * @note Availability: stack
 */
#define pop(this) this->functions->pop(this)
/**
 * @brief insert element at index
 * @param this container
 * @param idx index to insert
 * @param data data to insert
 * @note Availability: vector, string
 */
#define insert(...) GET_MACRO(__VA_ARGS__, insert_5, insert_4, insert_3, insert_2, insert_1)(__VA_ARGS__)
#define insert_3(this, idx, data) this->functions->insert_3(this, idx, data)
#define insert_4(this, idx, arr, size) this->functions->insert_4(this, idx, arr, size)
/**
 * @brief erase element at index
 * @param this container
 * @param idx index to erase
 * @param size number of elements to erase
 * @return data of erased element
 * @note Availability: vector, list, string
 */
#define erase(...) GET_MACRO(__VA_ARGS__, erase_5, erase_4, erase_3, erase_2, erase_1)(__VA_ARGS__)
#define erase_2(this, idx) this->functions->erase_2(this, idx)
#define erase_3(this, idx, size) this->functions->erase_3(this, idx, size)
/**
 * @brief append a null-terminated character array to a string
 * @param this string
 * @param cstr null-terminated character array
 * @note Availability: string
 */
#define append(this, cstr) this->functions->append(this, cstr)
/**
 * @brief shrink a container to a new size
 * @param this container
 * @param size size to shrink to
 * @note Availability: string
 */
#define resize(this, size) this->functions->resize(this, size)
/**
 * @brief replace a sub-string with a null-terminated character array
 * @param this string
 * @param idx starting index for sub-string
 * @param size size of sub-string
 * @param cstr null-terminated character array
 * @note Availability: string
 */
#define replace(this, idx, size, cstr) this->functions->replace(this, idx, size, cstr)
/**
 * @brief find a null-terminated character array in a string
 * @param this string
 * @param cstr null-terminated character array
 * @param idx index to start search from
 * @note Availability: string
 */
#define find(this, cstr, idx) this->functions->find(this, cstr, idx)
/**
 * @brief find a null-terminated character array from the back of a string
 * @param this string
 * @param cstr null-terminated character array
 * @param idx index to start search from
 * @note Availability: string
 */
#define rfind(this, cstr, idx) this->functions->rfind(this, cstr, idx)
/**
 * @brief get a substring
 * @param this string
 * @param idx starting index of substring
 * @param size size of substring
 * @return pointer to a new string container
 * @note Availability: string
 */
#define substr(this, idx, size) this->functions->substr(this, idx, size)
/**
 * @brief get a c-string
 * @param this string
 * @return const pointer to a c-string
 * @note Availability: string
 */
#define c_str(this) this->functions->c_str(this)
/**
 * @brief compare one string with another
 * @param this string
 * @param other string to compare against
 * @return as given by strcmp
 * @note Availability: string
 */
#define compare(this, other) this->functions->compare(this, other)
/**
 * @brief construct a heap in O(n)
 * @param this heap
 * @note Availability: heap
 */
#define heapify(this) this->functions->heapify(this)

#endif // MACROS