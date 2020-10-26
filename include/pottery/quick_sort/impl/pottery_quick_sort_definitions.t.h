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

#ifndef POTTERY_QUICK_SORT_IMPL
#error "This is an internal header. Do not include it."
#endif

/*
 * Helpers to wrap configuration
 */

typedef struct pottery_quick_sort_state_t {
    #ifdef POTTERY_QUICK_SORT_CONTEXT_TYPE
    pottery_quick_sort_context_t context;
    #endif
    pottery_quick_sort_ref_t first;
} pottery_quick_sort_state_t;

// Gets the ref for the element at index.
static pottery_always_inline
pottery_quick_sort_ref_t pottery_quick_sort_access(pottery_quick_sort_state_t state, size_t index) {
    (void)state;

    #ifndef POTTERY_QUICK_SORT_ACCESS
        // With no defined access expression, it's a simple array.
        return state.first + index;
    #elif defined(POTTERY_QUICK_SORT_CONTEXT_TYPE)
        return POTTERY_QUICK_SORT_ACCESS(state.context, state.first, index);
    #else
        return POTTERY_QUICK_SORT_ACCESS(state.first, index);
    #endif
}

/*
 * Implementation
 */

// The below implementation uses the Hoare partitioning method, except that it
// keeps the pivot at a fixed position outside of the loop during partitioning,
// that way we can compare it by reference without having to copy it to a
// temporary or track its position changes.

// Chooses a pivot and swaps it with the element at the start of the array.
static inline
void pottery_quicksort_prepare_pivot(pottery_state_t state, size_t start_index, size_t end_index) {
    if (end_index - start_index < 2) {
        // there are less than three elements so it doesn't matter which one
        // is the pivot. just use the first.
        #if 0
        // TODO clean up all these printfs
        printf("\nChose degenerate pivot: %i\n", *pottery_access(state, start_index));
        #endif
        return;
    }

    // choose elements for the median
    size_t middle_index = start_index + (end_index - start_index) / 2; // avoid overflow
    pottery_quick_sort_ref_t start = pottery_access(state, start_index);
    pottery_quick_sort_ref_t middle = pottery_access(state, middle_index);
    pottery_quick_sort_ref_t end = pottery_access(state, end_index);

    // if there is at most some arbitrary threshold of elements, use median
    if (end_index - start_index + 1 <= 128) {
        pottery_quick_sort_ref_t median = pottery_quick_sort_compare_median(
                POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, middle, end);
        if (median != start)
            pottery_quick_sort_lifecycle_swap(POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, median);
        #if 0
        printf("\nChose pivot by median: %i\n", *start);
        #endif
        return;
    }

    // use ninther
    size_t third_offset = (end_index - start_index) / 3;
    size_t sixth_offset = (end_index - start_index) / 6;
    pottery_quick_sort_ref_t left_middle = pottery_access(state, start_index + sixth_offset);
    pottery_quick_sort_ref_t left_end = pottery_access(state, start_index + third_offset);
    pottery_quick_sort_ref_t right_start = pottery_access(state, middle_index + third_offset);
    pottery_quick_sort_ref_t right_middle = pottery_access(state, middle_index + third_offset + sixth_offset);

    pottery_quick_sort_ref_t median = pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state)
            pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, left_middle, left_end),
            pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state) left_end, middle, right_start),
            pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state) right_start, right_middle, end));

    //if (median != pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, middle, end))
    //    printf("found better median %i instead of %i\n", *median, *pottery_quick_sort_compare_median(POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, middle, end));

    if (median != start)
        pottery_quick_sort_lifecycle_swap(POTTERY_QUICK_SORT_CONTEXT_VAL(state) start, median);
    #if 0
    printf("\nChose pivot by ninther: %i\n", *start);
    #endif
}

// There are two implementations of partitioning here, one that moves through a
// temporary and one that swaps. Moving through a temporary is faster, but we
// need a move function and a value type to be able to declare a temporary.
//
// (Moving through a temporary results in roughly one third as many moves. This
// is only a marginal improvement when sorting small stuff like ints and
// pointers but can be huge when sorting large objects, especially ones that
// aren't bitwise movable.

#ifndef POTTERY_QUICK_SORT_USE_MOVE
    #if POTTERY_LIFECYCLE_CAN_MOVE && defined(POTTERY_QUICK_SORT_VALUE_TYPE)
        #define POTTERY_QUICK_SORT_USE_MOVE 1
    #else
        #define POTTERY_QUICK_SORT_USE_MOVE 0
    #endif
#endif

// TODO rename start/end to first/last

#if POTTERY_QUICK_SORT_USE_MOVE
static inline
size_t pottery_quicksort_partition(pottery_state_t state, size_t start_index, size_t end_index) {
    #if 0
    printf("starting partition at %zi-%zi:", start_index, end_index);
    for (size_t i = start_index; i != end_index + 1; ++i)
        printf(" %i", *pottery_access(state, i));
    printf("\n");
    #endif

    pottery_assert(end_index - start_index >= 1);
    pottery_quick_sort_ref_t pivot = pottery_access(state, start_index);

    size_t low_index = start_index;
    size_t high_index = end_index;
    pottery_quick_sort_ref_t high = pottery_access(state, high_index);

    // Start by finding an element from the right that belongs on the left (or
    // is equal to the pivot. It's critical that we don't skip equal elements.)
    while (low_index < high_index && pottery_quick_sort_compare_less(
                POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, high)) {
        high = pottery_access(state, --high_index);
    }

    // If we've found none, the pivot goes at the start. (Either this partition
    // is really short or we've chosen an unfortunate pivot.)
    if (low_index == high_index) {
        #if 0
        printf("Found none larger!\n");
        #endif
        return start_index;
    }
    #if 0
    printf("Found from right at %zi %i, is now hole\n", high_index, *pottery_access(state, high_index));
    #endif

    // Move the element out into a temporary, leaving a hole on the right at
    // this location
    size_t hole_index = high_index;
    pottery_quick_sort_ref_t hole = high;
    pottery_quick_sort_value_t temp;
    pottery_quick_sort_lifecycle_move(POTTERY_QUICK_SORT_CONTEXT_VAL(state) &temp, hole);

    // Now we alternate between low_index and high_index, finding elements on the wrong
    // side and moving them into the hole
    pottery_quick_sort_ref_t low;
    while (true) {

        // Scan from the left
        do {
            low = pottery_access(state, ++low_index);
        } while (low_index < high_index && pottery_quick_sort_compare_greater(
                    POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, low));

        if (low_index == high_index) {
            #if 0
            printf("Converged on hole from left\n");
            #endif
            break;
        }

        // Put this element in the hole; the hole is now on the left.
        #if 0
        printf("Found from left at %zi %i, is now hole\n", low_index, *pottery_access(state, low_index));
        #endif
        pottery_quick_sort_lifecycle_move(POTTERY_QUICK_SORT_CONTEXT_VAL(state) hole, low);
        hole_index = low_index;
        hole = low;

        // Scan from the right
        do {
            high = pottery_access(state, --high_index);
        } while (low_index < high_index && pottery_quick_sort_compare_less(
                    POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, high));

        if (low_index == high_index) {
            #if 0
            printf("Converged on hole from right\n");
            #endif
            break;
        }

        // Put this element in the hole; the hole is now on the right.
        #if 0
        printf("Found from right at %zi %i, is now hole\n", high_index, *pottery_access(state, high_index));
        #endif
        pottery_quick_sort_lifecycle_move(POTTERY_QUICK_SORT_CONTEXT_VAL(state) hole, high);
        hole_index = high_index;
        hole = high;
    }

    // We've converged on the hole, and the temporary belongs on the left of
    // it. The pivot goes here and the temporary goes where the pivot was.
    (void)hole_index;
    pottery_assert(hole_index == high_index);
    pottery_quick_sort_lifecycle_move(POTTERY_QUICK_SORT_CONTEXT_VAL(state) hole, pivot);
    pottery_quick_sort_lifecycle_move(POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, &temp);
    return high_index;
}
#endif

#if !POTTERY_QUICK_SORT_USE_MOVE
static inline
size_t pottery_quicksort_partition(pottery_state_t state, size_t start_index, size_t end_index) {
    #if 0
    printf("starting partition at %zi-%zi:", start_index, end_index);
    for (size_t i = start_index; i != end_index + 1; ++i)
        printf(" %i", *pottery_access(state, i));
    printf("\n");
    #endif

    pottery_assert(end_index - start_index >= 1);

    pottery_quick_sort_ref_t pivot = pottery_access(state, start_index);

    #if 0
    printf("chose pivot %i at %zi\n", *pivot, start_index);
    #endif

    size_t low = start_index;
    size_t high = end_index + 1;
    while (true) {
        // Something to improve here later would be to eliminate some of these
        // redundant accesses. We should be able to hold on to the last access
        // to use in swap.

        // This is Hoare paritioning, except that we've kept the pivot outside
        // of the array so that we can refer to it in our comparisons.
        // Note that we can't skip elements equal to the pivot, otherwise we
        // wouldn't meet in the middle when all elements are equal.
        do {
            ++low;
        } while (low < high && pottery_quick_sort_compare_greater(
                    POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, pottery_access(state, low)));
        do {
            --high;
        } while (low < high && pottery_quick_sort_compare_less(
                    POTTERY_QUICK_SORT_CONTEXT_VAL(state) pivot, pottery_access(state, high)));

        if (low >= high)
            break;

        #if 0
        printf("swapping index %zi (%i) with index %zi (%i)\n", low,
                *pottery_access(state, low), high, *pottery_access(state, high));
        #endif

        pottery_quick_sort_lifecycle_swap(POTTERY_QUICK_SORT_CONTEXT_VAL(state)
                pottery_access(state, low), pottery_access(state, high));
    }

    // It's possible that the above algorithm stopped on an element that was
    // never compared with anything. We compare it to the pivot to decide where
    // the pivot should go.
    #if 0
    printf("finished loop, resulting low: %zi\n", low);
    #endif
    if (low > end_index || pottery_quick_sort_compare_less(POTTERY_QUICK_SORT_CONTEXT_VAL(state)
                pivot, pottery_access(state, low)))
        --low;

    // Unlike in normal Hoare partitioning, we now know where the pivot element
    // goes, so we swap it into place and skip it in the recursion.
    if (low != start_index) {
        #if 0
        printf("swapping pivot %zi with %zi\n", start_index, high);
        #endif
        pottery_quick_sort_lifecycle_swap(POTTERY_QUICK_SORT_CONTEXT_VAL(state)
                pivot, pottery_access(state, low));
    }

    #if 0
    printf("resulting partition:");
    for (size_t i = start_index; i != end_index + 1; ++i)
        printf(" %i", *pottery_access(state, i));
    printf("\n");
    #endif

    return low;
}
#endif

#ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
// We noinline the depth fallback to keep it out of the main implementation
// since it should be rarely used.
pottery_noinline static
void pottery_quick_sort_depth_fallback(pottery_state_t state, size_t first, size_t count) {
    POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK(
            POTTERY_QUICK_SORT_CONTEXT_VAL(state)
            pottery_quick_sort_access(state, first),
            count);
}
#endif

static inline
bool pottery_quick_sort_fallback(pottery_state_t state, size_t first, size_t count
        #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
        , size_t depth, size_t depth_limit
        #endif
) {
    (void)state;
    (void)first;
    (void)count;

    // Switch to the count limit fallback if we don't have enough elements
    #ifdef POTTERY_QUICK_SORT_COUNT_LIMIT_FALLBACK
    #ifdef POTTERY_QUICK_SORT_VALUE_TYPE
    // The limit can apparently be quite high for small elements (e.g. ints).
    // We assume large elements take more effort to compare and swap, so if we
    // know the element size, we make the limit dependent on it (within a sane
    // range) so that we avoid big numbers for big elements.
    size_t count_limit = pottery_clamp_s(64 * 4 / sizeof(pottery_quick_sort_value_t), 8, 64);
    #else
    // If we don't know the element size, we estimate conservatively.
    size_t count_limit = 8;
    #endif
    if (count <= count_limit) {
        POTTERY_QUICK_SORT_COUNT_LIMIT_FALLBACK(
                POTTERY_QUICK_SORT_CONTEXT_VAL(state)
                pottery_quick_sort_access(state, first),
                count);
        return true;
    }
    #endif

    // Switch to the depth limit fallback if we're too deep
    #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
    if (pottery_unlikely(depth == depth_limit)) {
        pottery_quick_sort_depth_fallback(state, first, count);
        return true;
    }
    #endif

    return false;
}

POTTERY_QUICK_SORT_EXTERN
void pottery_quick_sort(
        #ifdef POTTERY_QUICK_SORT_CONTEXT_TYPE
        pottery_quick_sort_context_t context,
        #endif
        pottery_quick_sort_ref_t ref,
        size_t total_count
) {
    pottery_quick_sort_state_t state = {
        #ifdef POTTERY_QUICK_SORT_CONTEXT_TYPE
        context,
        #endif
        ref,
    };
    //printf("=========================\n");
    //printf("starting quicksort count %zi\n", total_count);

    if (total_count <= 1)
        return;

    // set up the stack
    // we push the small partition which is less than half the size of its
    // parent so it's not possible to use more than sizeof(size_t)*8 entries.
    struct {
        size_t first;
        size_t last;
        #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
        size_t depth;
        #endif
    } stack[sizeof(size_t) * 8];
    size_t pos = 0;
    stack[0].first = 0;
    stack[0].last = total_count - 1;
    #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
    stack[0].depth = 0;
    #endif

    // set up depth limit for switching to fallback
    #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
    size_t n = 1;
    size_t depth_limit = 2;
    while (n < total_count) {
        n *= 2;
        depth_limit += 2;
    }
    #endif

    while (true) {
        size_t first = stack[pos].first;
        size_t last = stack[pos].last;
        pottery_assert(last > first);
        size_t count = last - first + 1;
        //printf("pos %zi first %zi last %zi count %zi\n", pos, first, last, count);

        // see if we should use any fallbacks
        if (pottery_quick_sort_fallback(state, first, count
                #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
                , stack[pos].depth, depth_limit
                #endif
                )) {
            if (pos == 0)
                break;
            --pos;
            continue;
        }

        // choose a pivot, swapping it with the start index
        pottery_quicksort_prepare_pivot(state, first, last);

        // do the partition. note that this places the pivot in its correct
        // final position so we exclude it from the resulting partitions.
        size_t pivot = pottery_quicksort_partition(state, first, last);
        size_t left_count = pivot - first;
        size_t right_count = last - pivot;
        //printf("pivot %zi left_count %zi right_count %zi\n", pivot, left_count, right_count);

        #if 0
        printf("done partition");
        for (size_t i = first; i != last + 1; ++i) {
            putchar(' ');
            if (i == pivot)
                printf("-->");
            printf("%i", *pottery_access(state, i));
            if (i == pivot)
                printf("<--");
        }
        printf("\n");
        fflush(stdout);
        #endif

        #if 0
        size_t check;
        for (check = first; check <= pivot; ++check)
            pottery_assert(pottery_quick_sort_compare_less_or_equal(
                POTTERY_QUICK_SORT_CONTEXT_VAL(state) pottery_access(state, check), pottery_access(state, pivot)));
        for (check = pivot; check <= last; ++check)
            pottery_assert(pottery_quick_sort_compare_less_or_equal(
                POTTERY_QUICK_SORT_CONTEXT_VAL(state) pottery_access(state, pivot), pottery_access(state, check)));
        #endif

        // if both sides are degenerate, pop
        if (left_count <= 1 && right_count <= 1) {
            if (pos == 0)
                break;
            --pos;
            continue;
        }

        // push the short side (if needed), loop around to the long side
        #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
        size_t depth = stack[pos].depth + 1;
        #endif
        if (pivot - first < last - pivot) {
            //printf("right partition is bigger\n");
            if (left_count > 1) {
                //printf("pushing left\n");
                stack[pos].first = first;
                stack[pos].last = pivot - 1;
                #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
                stack[pos].depth = depth;
                #endif
                ++pos;
                pottery_assert(pos != pottery_array_count(stack)); // not possible!
            }
            //printf("iterating on right\n");
            stack[pos].first = pivot + 1;
            stack[pos].last = last;
            #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
            stack[pos].depth = depth;
            #endif
        } else {
            //printf("left partition is bigger\n");
            if (right_count > 1) {
                //printf("pushing right\n");
                stack[pos].first = pivot + 1;
                stack[pos].last = last;
                #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
                stack[pos].depth = depth;
                #endif
                ++pos;
                pottery_assert(pos != pottery_array_count(stack)); // not possible!
            }
            //printf("iterating on left\n");
            stack[pos].first = first;
            stack[pos].last = pivot - 1;
            #ifdef POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK
            stack[pos].depth = depth;
            #endif
        }
    }

    #if 0
    printf("done! result:");
    for (size_t i = 0; i < count; ++i)
        printf(" %i", *pottery_access(state, i));
    printf("\n");
    #endif
}
