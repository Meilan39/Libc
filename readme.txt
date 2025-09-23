List

List(T)* new_list(T);
List(T)* new_list(T, size_t size);
List(T)* new_list(T, size_t size, T data);
List(T)* copy_list(T, const List(T)* other);
List(T)* move_list(T, List(T)* other);
void delete_list(List(T) *this);

int empty(List(T) *this);
size_t size(List(T) *this);
T at(List(T) *this, size_t idx);
T front(List(T) *this);

void clear(List(T) *this);
void push_front(List(T) *this, T data);
void pop_front(List(T) *this);
void insert(List(T) *this, size_t idx, T data);
void erase(List(T) *this, size_t idx);

vector

Vector(T)* new_vector(T);
Vector(T)* new_vector(T, size_t size);
Vector(T)* new_vector(T, size_t size, T data);
Vector(T)* copy_vector(T, const Vector(T)* other);
Vector(T)* move_vector(T, Vector(T)* other);
void delete_vector(Vector(T) *this);

int empty(Vector(T) *this);
void reserve(Vector(T) *this, size_t size);
void shrink(Vector(T) *this);
size_t size(Vector(T) *this);
size_t capacity(Vector(T) *this);
T at(Vector(T) *this, size_t idx);
T front(Vector(T) *this);
T back(Vector(T) *this);

void clear(Vector(T) *this);
void push_back(Vector(T) *this, T data);
void pop_back(Vector(T) *this);
void insert(Vector(T) *this, size_t idx, T data);
void insert(Vector(T) *this, size_t idx, const T *arr, size_t size);
void erase(Vector(T) *this, size_t idx);
void erase(Vector(T) *this, size_t idx, size_t size);

String

String(T)* new_string(T);
String(T)* new_string(T, const char *cstr);
String(T)* new_stirng(T, size_t size, char data);
String(T)* copy_string(T, const String(T) *other);
String(T)* move_string(T, String(T) *other);
void delete_string(String(T) *this);

int empty(String(T) *this);
void reserve(String(T) *this, size_t size);
void shrink(String(T) *this);
size_t size(String(T) *this);
size_t capacity(String(T) *this);
char at(String(T) *this, size_t idx);
char front(String(T) *this);
char back(String(T) *this);

void clear(String(T) *this);
void push_back(String(T) *this, char data);
char pop_back(String(T) *this);
void insert(String(T) *this, size_t idx, const char* chr);
void erase(String(T) *this, size_t idx, size_t size);
void append(String(T) *this, const char *cstr);
void detach(String(T) *this, size_t size);
void replace(String(T) *this, size_t idx, size_t size, const char* cstr);

size_t find(String(T) *this, const char *cstr, size_t idx);
size_t rfind(String(T) *this, const char *cstr, size_t idx);

String(T) *substr(String(T) *this, size_t idx, size_t size);
const char *c_str(String(T) *this);

int compare(String(T) *this, String(T) *other);

Ring

Ring(T)* new_ring(T);
Ring(T)* copy_ring(T, const Ring(T)* other);
Ring(T)* move_ring(T, Ring(T)* other);
void delete_ring(Ring(T) *this);

int empty(Ring(T) *this);
void reserve(Ring(T) *this);
size_t size(Ring(T) *this);
size_t capacity(Ring(T) *this);
T front(Ring(T) *this);
T back(Ring(T) *this); 

void clear(Ring(T) *this);
void push_back(Ring(T) *this, T data);
void push_front(Ring(T) *this, T data);
T pop_back(Ring(T) *this);
T pop_front(Ring(T) *this);

Stack

Stack(T)* new_stack(T);
Stack(T)* copy_stack(T, const Stack(T)* other);
Stack(T)* move_stack(T, Stack(T)* other);
void delete_stack(Stack(T) *this);

int empty(Stack(T) *this);
void reserve(Stack(T) *this, size_t size);
size_t size(Stack(T) *this);
size_t capacity(Stack(T) *this);
T *top(Stack(T) *this);

void clear(Stack(T) *this);
void push(Stack(T) *this, T data);
char pop(Stack(T) *this);

Queue

Queue(T)* new_queue(T);
Queue(T)* copy_queue(T, const Queue(T)* other);
Queue(T)* move_queue(T, Queue(T)* other);
void delete_queue(Queue(T) *this);

int empty(Queue(T) *this);
void reserve(Queue(T) *this, size_t size);
size_t size(Queue(T) *this);
size_t capacity(Queue(T) *this);
T *front(Queue(T) *this);
T *back(Queue(T) *this);

void clear(Queue(T) *this);
void push(Queue(T) *this, T data);
char pop(Queue(T) *this);
