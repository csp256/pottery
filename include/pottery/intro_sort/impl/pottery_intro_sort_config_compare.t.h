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

#define POTTERY_COMPARE_PREFIX POTTERY_CONCAT(POTTERY_INTRO_SORT_PREFIX, _compare)



// Forward types
//!!! AUTOGENERATED:container/types.m.h SRC:POTTERY_INTRO_SORT DEST:POTTERY_COMPARE
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Forwards container type configuration from POTTERY_INTRO_SORT to POTTERY_COMPARE

    // Forward the value and ref
    // (TODO temporarily forwarding both. Once entry and ref are fully separated
    // this will only forward one or the other.)
    #if defined(POTTERY_INTRO_SORT_REF_TYPE)
        #define POTTERY_COMPARE_REF_TYPE POTTERY_INTRO_SORT_REF_TYPE
    #endif
    #if defined(POTTERY_INTRO_SORT_VALUE_TYPE)
        #define POTTERY_COMPARE_VALUE_TYPE POTTERY_INTRO_SORT_VALUE_TYPE
    #endif

    // Forward the entry
    #if defined(POTTERY_INTRO_SORT_ENTRY_TYPE)
        #define POTTERY_COMPARE_ENTRY_TYPE POTTERY_INTRO_SORT_ENTRY_TYPE
    #endif

    // Forward the entry dereference mechanism
    #if defined(POTTERY_INTRO_SORT_ENTRY_VALUE)
        #define POTTERY_COMPARE_ENTRY_VALUE POTTERY_INTRO_SORT_ENTRY_VALUE
    #endif

    // Forward the context
    #ifdef POTTERY_INTRO_SORT_CONTEXT_TYPE
        #define POTTERY_COMPARE_CONTEXT_TYPE POTTERY_INTRO_SORT_CONTEXT_TYPE
    #endif
//!!! END_AUTOGENERATED



// Forward compare configuration
//!!! AUTOGENERATED:compare/forward.m.h SRC:POTTERY_INTRO_SORT_COMPARE DEST:POTTERY_COMPARE
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Forwards compare configuration from POTTERY_INTRO_SORT_COMPARE to POTTERY_COMPARE

    #ifdef POTTERY_INTRO_SORT_COMPARE_BY_VALUE
        #define POTTERY_COMPARE_BY_VALUE POTTERY_INTRO_SORT_COMPARE_BY_VALUE
    #endif

    #ifdef POTTERY_INTRO_SORT_COMPARE_EQUAL
        #define POTTERY_COMPARE_EQUAL POTTERY_INTRO_SORT_COMPARE_EQUAL
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_NOT_EQUAL
        #define POTTERY_COMPARE_NOT_EQUAL POTTERY_INTRO_SORT_COMPARE_NOT_EQUAL
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_LESS
        #define POTTERY_COMPARE_LESS POTTERY_INTRO_SORT_COMPARE_LESS
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_LESS_OR_EQUAL
        #define POTTERY_COMPARE_LESS_OR_EQUAL POTTERY_INTRO_SORT_COMPARE_LESS_OR_EQUAL
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_GREATER
        #define POTTERY_COMPARE_GREATER POTTERY_INTRO_SORT_COMPARE_GREATER
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_GREATER_OR_EQUAL
        #define POTTERY_COMPARE_GREATER_OR_EQUAL POTTERY_INTRO_SORT_COMPARE_GREATER_OR_EQUAL
    #endif
    #ifdef POTTERY_INTRO_SORT_COMPARE_THREE_WAY
        #define POTTERY_COMPARE_THREE_WAY POTTERY_INTRO_SORT_COMPARE_THREE_WAY
    #endif
//!!! END_AUTOGENERATED
