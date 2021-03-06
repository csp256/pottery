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

#ifndef POTTERY_INTRO_SORT_IMPL
#error "This is header internal to Pottery. Do not include it."
#endif

#include "pottery/pottery_dependencies.h"

#define POTTERY_QUICK_SORT_PREFIX POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _quick_sort)

// We'll be using our own helper templates
#define POTTERY_QUICK_SORT_EXTERNAL_LIFECYCLE POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _lifecycle)
#define POTTERY_QUICK_SORT_EXTERNAL_COMPARE POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _compare)
#define POTTERY_QUICK_SORT_EXTERNAL_ARRAY_ACCESS POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _array_access)

// Switch to insertion_sort when partition is too small
#define POTTERY_QUICK_SORT_COUNT_LIMIT_FALLBACK POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _insertion_sort)

// Switch to heap_sort when recursion is too deep
#define POTTERY_QUICK_SORT_DEPTH_LIMIT_FALLBACK POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _heap_sort)


// Forward types
//!!! AUTOGENERATED:container/types.m.h SRC:POTTERY_INTRO_SORT DEST:POTTERY_QUICK_SORT
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Forwards container type configuration from POTTERY_INTRO_SORT to POTTERY_QUICK_SORT

    // Forward the value or ref
    #if defined(POTTERY_INTRO_SORT_REF_TYPE) && !defined(POTTERY_INTRO_SORT_VALUE_TYPE)
        #define POTTERY_QUICK_SORT_REF_TYPE POTTERY_INTRO_SORT_REF_TYPE
    #elif defined(POTTERY_INTRO_SORT_VALUE_TYPE) && !defined(POTTERY_INTRO_SORT_REF_TYPE)
        #define POTTERY_QUICK_SORT_VALUE_TYPE POTTERY_INTRO_SORT_VALUE_TYPE
    #else
        #error "Exactly one of POTTERY_INTRO_SORT_REF_TYPE or POTTERY_INTRO_SORT_VALUE_TYPE must be defined."
    #endif

    // Forward the entry
    #if defined(POTTERY_INTRO_SORT_ENTRY_TYPE)
        #define POTTERY_QUICK_SORT_ENTRY_TYPE POTTERY_INTRO_SORT_ENTRY_TYPE
    #endif

    // Forward the entry dereference mechanism
    #if defined(POTTERY_INTRO_SORT_ENTRY_REF)
        #define POTTERY_QUICK_SORT_ENTRY_REF POTTERY_INTRO_SORT_ENTRY_REF
    #endif

    // Forward the context
    #ifdef POTTERY_INTRO_SORT_CONTEXT_TYPE
        #define POTTERY_QUICK_SORT_CONTEXT_TYPE POTTERY_INTRO_SORT_CONTEXT_TYPE
    #endif
//!!! END_AUTOGENERATED
