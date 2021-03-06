#ifndef GC_OBJECT_H
#define GC_OBJECT_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t size;
    uint8_t marked;
    uint8_t atomic;
} Object;

//static inline void Object_init(Object* object) {
//    object->size = 0;
//    object->marked = 0;
//    object->atomic = 0;
//}

static inline void Object_allocate(Object* object, size_t size, int atomic) {
    object->size = size;
    object->atomic = atomic;
}

static inline void* Object_mutatorAddress(Object* object) {
    return (char *)object + sizeof(Object);
}

// Returns the mutator size, not counting the object metadata.
static inline size_t Object_mutatorSize(Object* object) {
    return object->size - sizeof(Object);
}

// Returns the object size, counting the object metadata and the mutator size.
static inline size_t Object_size(Object* object) {
    return object->size;
}

static inline size_t Object_isMarked(Object* object) {
    return object->marked == 1;
}

static inline size_t Object_mark(Object* object) {
    return object->marked = 1;
}

static inline size_t Object_unmark(Object* object) {
    return object->marked = 0;
}

static inline size_t Object_contains(Object* object, char *pointer) {
    return pointer >= (char *)Object_mutatorAddress(object) &&
        pointer < (char *)object + object->size;
}

#endif
