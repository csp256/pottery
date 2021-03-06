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

#ifndef POTTERY_LIFECYCLE_INTERNAL
#error "This is an internal header. Do not include it."
#endif



/*
 * Configuration
 */

// user configuration

#undef POTTERY_LIFECYCLE_PREFIX
#undef POTTERY_LIFECYCLE_REF_TYPE
#undef POTTERY_LIFECYCLE_VALUE_TYPE
#undef POTTERY_LIFECYCLE_CONTEXT_TYPE
#undef POTTERY_LIFECYCLE_BULK
#undef POTTERY_LIFECYCLE_CONSTRUCT

//!!! AUTOGENERATED:lifecycle/unconfigure.m.h PREFIX:POTTERY_LIFECYCLE
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.

    // Undefines (forwardable/forwarded) lifecycle configuration on POTTERY_LIFECYCLE

    #undef POTTERY_LIFECYCLE_BY_VALUE
    #undef POTTERY_LIFECYCLE_DESTROY
    #undef POTTERY_LIFECYCLE_DESTROY_BY_VALUE
    #undef POTTERY_LIFECYCLE_INIT
    #undef POTTERY_LIFECYCLE_INIT_BY_VALUE
    #undef POTTERY_LIFECYCLE_INIT_COPY
    #undef POTTERY_LIFECYCLE_INIT_COPY_BY_VALUE
    #undef POTTERY_LIFECYCLE_INIT_STEAL
    #undef POTTERY_LIFECYCLE_INIT_STEAL_BY_VALUE
    #undef POTTERY_LIFECYCLE_MOVE
    #undef POTTERY_LIFECYCLE_MOVE_BY_VALUE
    #undef POTTERY_LIFECYCLE_COPY
    #undef POTTERY_LIFECYCLE_COPY_BY_VALUE
    #undef POTTERY_LIFECYCLE_STEAL
    #undef POTTERY_LIFECYCLE_STEAL_BY_VALUE
    #undef POTTERY_LIFECYCLE_SWAP
    #undef POTTERY_LIFECYCLE_SWAP_BY_VALUE
//!!! END_AUTOGENERATED

// helpers

#undef POTTERY_LIFECYCLE_ATTRIBUTES_EXTERNAL
#undef POTTERY_LIFECYCLE_DECLARE_INTERNALS
#undef POTTERY_LIFECYCLE_CONTEXT_ARG
#undef POTTERY_LIFECYCLE_CONTEXT_VAL
#undef POTTERY_LIFECYCLE_CONTEXT_MAYBE_UNUSED
#undef POTTERY_LIFECYCLE_RESTRICT



/*
 * Renaming
 */

//!!! AUTOGENERATED:lifecycle/unrename.m.h PREFIX:pottery_lifecycle
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Un-renames lifecycle identifiers with prefix "pottery_lifecycle"

    // types
    #undef pottery_lifecycle_value_t
    #undef pottery_lifecycle_ref_t
    #undef pottery_lifecycle_entry_t
    #undef pottery_lifecycle_context_t

    #undef pottery_lifecycle_const_ref_t

    // fundamental operations
    #undef pottery_lifecycle_init_steal
    #undef pottery_lifecycle_init_copy
    #undef pottery_lifecycle_init
    #undef pottery_lifecycle_destroy
    #undef pottery_lifecycle_swap
    #undef pottery_lifecycle_move
    #undef pottery_lifecycle_steal
    #undef pottery_lifecycle_copy

    // bulk operations
    #undef pottery_lifecycle_move_bulk
    #undef pottery_lifecycle_move_bulk_restrict
    #undef pottery_lifecycle_move_bulk_restrict_impl
    #undef pottery_lifecycle_move_bulk_up
    #undef pottery_lifecycle_move_bulk_up_impl
    #undef pottery_lifecycle_move_bulk_down
    #undef pottery_lifecycle_move_bulk_down_impl
    #undef pottery_lifecycle_destroy_bulk
//!!! END_AUTOGENERATED



#include "pottery/platform/pottery_platform_pragma_pop.t.h"
