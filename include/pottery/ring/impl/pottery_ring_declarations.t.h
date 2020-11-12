/*
 * MIT License
 *
 * Copyright (c) 2020 Nicholas Fraser
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef POTTERY_RING_IMPL
#error "This is an internal header. Do not include it."
#endif

#if !POTTERY_LIFECYCLE_CAN_MOVE
#error "A move expression is required so that the ring can grow."
#endif

typedef POTTERY_RING_VALUE_TYPE pottery_ring_value_t;

typedef pottery_ring_value_t* pottery_ring_entry_t;

/**
 * A double-ended queue of values implemented as a circular array.
 *
 * This has nearly the same interface as the paged deque, but it has different
 * performance characteristics and invalidation rules.
 *
 * When the ring changes for any reason (insert, extract, commit, drop, etc.), all
 * pointers to any elements in the ring are invalidated and any ongoing
 * emplace or access is invalidated at both ends. This is because the ring
 * may shrink or grow which may move all elements. This is different from the
 * paged deque; see the documentation on deque for more details.
 *
 * The ring is (by default) growable. When the ring needs to grow, all
 * values are copied.
 */
typedef struct pottery_ring_t {
    pottery_ring_value_t* values;
    size_t capacity;
    size_t start;
    size_t count;

    #ifdef POTTERY_RING_INTERNAL_COUNT
    pottery_ring_value_t internal[POTTERY_RING_INTERNAL_COUNT];
    #endif

    #ifdef POTTERY_RING_ENABLE_EXTERNAL
    pottery_ring_value_t* external;
    size_t external_capacity;
    #endif
} pottery_ring_t;

static inline void pottery_ring_sanity_check(pottery_ring_t* ring) {
    pottery_assert((ring->capacity == 0) == (ring->values == NULL));
}

POTTERY_RING_EXTERN
void pottery_ring_init(pottery_ring_t* ring);
POTTERY_RING_EXTERN
void pottery_ring_destroy(pottery_ring_t* ring);

static inline
size_t pottery_ring_count(pottery_ring_t* ring) {
    return ring->count;
}

static inline
bool pottery_ring_is_empty(pottery_ring_t* ring) {
    return ring->count == 0;
}

POTTERY_RING_EXTERN
void pottery_ring_displace_all(pottery_ring_t* ring);

#if POTTERY_LIFECYCLE_CAN_DESTROY
POTTERY_RING_EXTERN
void pottery_ring_remove_all(pottery_ring_t* ring);
#endif

POTTERY_RING_EXTERN
pottery_error_t pottery_ring_emplace_first(pottery_ring_t* ring, pottery_ring_entry_t* entry);
POTTERY_RING_EXTERN
pottery_error_t pottery_ring_emplace_last(pottery_ring_t* ring, pottery_ring_entry_t* entry);

#if POTTERY_LIFECYCLE_CAN_PASS
static inline
pottery_error_t pottery_ring_insert_first(pottery_ring_t* ring, pottery_ring_value_t value) {
    pottery_ring_entry_t entry;
    pottery_error_t error = pottery_ring_emplace_first(ring, &entry);
    if (error == POTTERY_OK)
        *entry = value;
    return error;
}

static inline
pottery_error_t pottery_ring_insert_last(pottery_ring_t* ring, pottery_ring_value_t value) {
    pottery_ring_entry_t entry;
    pottery_error_t error = pottery_ring_emplace_last(ring, &entry);
    if (error == POTTERY_OK)
        *entry = value;
    return error;
}
#endif

static inline
pottery_ring_value_t* pottery_ring_at(pottery_ring_t* ring, size_t index) {
    pottery_ring_sanity_check(ring);
    pottery_assert(index < pottery_ring_count(ring));

    size_t offset = (ring->start + index) % ring->capacity;
    //fprintf(stderr, "at index %i offset %i\n", (int)index, (int)offset);
    return ring->values + offset;
}

static inline
size_t pottery_ring_index(pottery_ring_t* ring, pottery_ring_value_t* value) {
    return (pottery_cast(size_t, value - ring->values) + ring->count - ring->start) % ring->capacity;
}

static inline
pottery_ring_value_t* pottery_ring_first(pottery_ring_t* ring) {
    pottery_assert(!pottery_ring_is_empty(ring));
    return ring->values + ring->start;
}

static inline
pottery_ring_value_t* pottery_ring_last(pottery_ring_t* ring) {
    pottery_assert(!pottery_ring_is_empty(ring));
    return pottery_ring_at(ring, ring->count - 1);
}

static inline
pottery_ring_value_t* pottery_ring_begin(pottery_ring_t* ring) {
    if (ring->count == 0)
        return pottery_null;
    return ring->values + ring->start;
}

static inline
pottery_ring_value_t* pottery_ring_end(pottery_ring_t* ring) {
    (void)ring;
    return pottery_null;
}

static inline
bool pottery_ring_ref_exists(pottery_ring_t* ring, pottery_ring_value_t* ref) {
    (void)ring;
    return ref != pottery_null;
}

static inline
pottery_ring_value_t* pottery_ring_next(pottery_ring_t* ring, pottery_ring_value_t* ref) {
    if (ref == pottery_ring_last(ring))
        return pottery_null;
    ++ref;
    if (ref == ring->values + ring->count)
        ref = ring->values;
    return ref;
}

static inline
pottery_ring_value_t* pottery_ring_previous(pottery_ring_t* ring, pottery_ring_value_t* ref) {
    // It is an error to call this on the first element.
    pottery_assert(ref != pottery_ring_first(ring));
    if (ref == pottery_null)
        return pottery_ring_last(ring);

    if (ref == ring->values)
        ref = ring->values + ring->count - 1;
    else
        --ref;

    return ref;
}

POTTERY_RING_EXTERN
void pottery_ring_displace_first(pottery_ring_t* ring);
POTTERY_RING_EXTERN
void pottery_ring_displace_last(pottery_ring_t* ring);

#if POTTERY_LIFECYCLE_CAN_DESTROY
static inline
void pottery_ring_remove_first(pottery_ring_t* ring) {
    pottery_ring_lifecycle_destroy(pottery_ring_first(ring));
    pottery_ring_displace_first(ring);
}

static inline
void pottery_ring_remove_last(pottery_ring_t* ring) {
    pottery_ring_lifecycle_destroy(pottery_ring_last(ring));
    pottery_ring_remove_last(ring);
}
#endif

#if POTTERY_LIFECYCLE_CAN_PASS
static inline
pottery_ring_value_t pottery_ring_extract_first(pottery_ring_t* ring) {
    pottery_ring_value_t* ref = pottery_ring_first(ring);
    pottery_ring_value_t element = pottery_move_if_cxx(*ref);
    #ifdef __cplusplus
    // see pottery_vector_extract() for details
    ref->~pottery_ring_value_t();
    #endif
    pottery_ring_displace_first(ring);
    return element;
}

static inline
pottery_ring_value_t pottery_ring_extract_last(pottery_ring_t* ring) {
    pottery_ring_value_t* ref = pottery_ring_last(ring);
    pottery_ring_value_t element = pottery_move_if_cxx(*ref);
    #ifdef __cplusplus
    // see pottery_vector_extract() for details
    ref->~pottery_ring_value_t();
    #endif
    pottery_ring_displace_last(ring);
    return element;
}

POTTERY_RING_EXTERN
void pottery_ring_insert_last_bulk(pottery_ring_t* ring, const pottery_ring_value_t* values, size_t count);

/**
 * Pushes each element from the given array in reverse order into the front of
 * the ring. (The last element of the given array will end up at the front
 * of the ring.)
 *
 * This is the opposite operation of pottery_ring_extract_first_bulk();
 * inserting an array of bulk data and then extracting it again is functionally
 * idempotent.
 */
POTTERY_RING_EXTERN
void pottery_ring_insert_first_bulk(pottery_ring_t* ring, const pottery_ring_value_t* values, size_t count);

POTTERY_RING_EXTERN
void pottery_ring_extract_first_bulk(pottery_ring_t* ring, pottery_ring_value_t* values, size_t count);

/**
 * Pops elements from the end of the ring one-by-one in into the given array
 * in reverse order. (The element at the end of the ring will be placed at the
 * start of the array.)
 *
 * This is the opposite operation of pottery_ring_insert_last_bulk(); inserting
 * an array of bulk data and then extracting it again is functionally
 * idempotent.
 */
POTTERY_RING_EXTERN
void pottery_ring_extract_last_bulk(pottery_ring_t* ring, pottery_ring_value_t* values, size_t count);
#endif