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

#include "pottery/pottery_dependencies.h"
#include "pottery/platform/pottery_platform_pragma_push.t.h"

#ifndef POTTERY_RING_PREFIX
#error "POTTERY_RING_PREFIX is not defined."
#endif
#ifndef POTTERY_RING_VALUE_TYPE
#error "POTTERY_RING_VALUE_TYPE is not defined."
#endif

#ifndef POTTERY_RING_EXTERN
#define POTTERY_RING_EXTERN /*nothing*/
#endif

#define POTTERY_RING_NAME(name) POTTERY_CONCAT(POTTERY_RING_PREFIX, name)

// ring definition

#define pottery_ring_t POTTERY_RING_NAME(_t)
#define pottery_ring_value_t POTTERY_RING_NAME(_value_t)
#define pottery_ring_entry_t POTTERY_RING_NAME(_entry_t)
#define pottery_ring_page_t POTTERY_RING_NAME(_page_t)

#define pottery_ring_at POTTERY_RING_NAME(_at)
#define pottery_ring_select POTTERY_RING_NAME(_select)
#define pottery_ring_index POTTERY_RING_NAME(_index)
#define pottery_ring_first POTTERY_RING_NAME(_first)
#define pottery_ring_last POTTERY_RING_NAME(_last)
#define pottery_ring_next POTTERY_RING_NAME(_next)
#define pottery_ring_previous POTTERY_RING_NAME(_previous)
#define pottery_ring_begin POTTERY_RING_NAME(_begin)
#define pottery_ring_end POTTERY_RING_NAME(_end)
#define pottery_ring_ref_exists POTTERY_RING_NAME(_ref_exists)

#define pottery_ring_displace_all POTTERY_RING_NAME(_displace_all)
#define pottery_ring_remove_all POTTERY_RING_NAME(_remove_all)
#define pottery_ring_impl_destroy_all POTTERY_RING_NAME(_impl_destroy_all)

#define pottery_ring_init POTTERY_RING_NAME(_init)
#define pottery_ring_destroy POTTERY_RING_NAME(_destroy)
#define pottery_ring_count POTTERY_RING_NAME(_count)
#define pottery_ring_is_empty POTTERY_RING_NAME(_is_empty)
#define pottery_ring_emplace_first POTTERY_RING_NAME(_emplace_first)
#define pottery_ring_emplace_last POTTERY_RING_NAME(_emplace_last)
#define pottery_ring_insert_first POTTERY_RING_NAME(_insert_first)
#define pottery_ring_insert_last POTTERY_RING_NAME(_insert_last)
#define pottery_ring_insert POTTERY_RING_NAME(_insert)
#define pottery_ring_insert_first_bulk POTTERY_RING_NAME(_insert_first_bulk)
#define pottery_ring_insert_last_bulk POTTERY_RING_NAME(_insert_last_bulk)
#define pottery_ring_insert_bulk POTTERY_RING_NAME(_insert_bulk)
#define pottery_ring_displace_first POTTERY_RING_NAME(_displace_first)
#define pottery_ring_displace_last POTTERY_RING_NAME(_displace_last)
#define pottery_ring_remove_first POTTERY_RING_NAME(_remove_first)
#define pottery_ring_remove_last POTTERY_RING_NAME(_remove_last)
#define pottery_ring_extract_first POTTERY_RING_NAME(_extract_first)
#define pottery_ring_extract_last POTTERY_RING_NAME(_extract_last)
#define pottery_ring_extract POTTERY_RING_NAME(_extract)
#define pottery_ring_extract_first_bulk POTTERY_RING_NAME(_extract_first_bulk)
#define pottery_ring_extract_last_bulk POTTERY_RING_NAME(_extract_last_bulk)
#define pottery_ring_extract_bulk POTTERY_RING_NAME(_extract_bulk)
#define pottery_ring_emplace_first POTTERY_RING_NAME(_emplace_first)
#define pottery_ring_emplace_last POTTERY_RING_NAME(_emplace_last)
#define pottery_ring_emplace POTTERY_RING_NAME(_emplace)
#define pottery_ring_access_first POTTERY_RING_NAME(_access_first)
#define pottery_ring_access_last POTTERY_RING_NAME(_access_last)
#define pottery_ring_access POTTERY_RING_NAME(_access)
#define pottery_ring_drop_first POTTERY_RING_NAME(_drop_first)
#define pottery_ring_drop_last POTTERY_RING_NAME(_drop_last)
#define pottery_ring_drop POTTERY_RING_NAME(_drop)

// static funcs
#define pottery_ring_sanity_check POTTERY_RING_NAME(_sanity_check)
#define pottery_ring_grow POTTERY_RING_NAME(_grow)



// lifecycle functions
#ifdef POTTERY_RING_EXTERNAL_LIFECYCLE
    #define POTTERY_RING_LIFECYCLE_PREFIX POTTERY_RING_EXTERNAL_LIFECYCLE
#else
    #define POTTERY_RING_LIFECYCLE_PREFIX POTTERY_RING_NAME(_lifecycle)
#endif
//!!! AUTOGENERATED:lifecycle/rename.m.h SRC:pottery_ring_lifecycle DEST:POTTERY_RING_LIFECYCLE_PREFIX
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Renames lifecycle identifiers from pottery_ring_lifecycle to POTTERY_RING_LIFECYCLE_PREFIX

    // types
    #define pottery_ring_lifecycle_value_t POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _value_t)
    #define pottery_ring_lifecycle_ref_t POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _ref_t)
    #define pottery_ring_lifecycle_const_ref_t POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _const_ref_t)
    #define pottery_ring_lifecycle_context_t POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _context_t)

    // fundamental operations
    #define pottery_ring_lifecycle_init_steal POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _init_steal)
    #define pottery_ring_lifecycle_init_copy POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _init_copy)
    #define pottery_ring_lifecycle_init POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _init)
    #define pottery_ring_lifecycle_destroy POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _destroy)
    #define pottery_ring_lifecycle_swap POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _swap)
    #define pottery_ring_lifecycle_move POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move)
    #define pottery_ring_lifecycle_steal POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _steal)
    #define pottery_ring_lifecycle_copy POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _copy)

    // bulk operations
    #define pottery_ring_lifecycle_destroy_bulk POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _destroy_bulk)
    #define pottery_ring_lifecycle_move_bulk POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk)
    #define pottery_ring_lifecycle_move_bulk_restrict POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_restrict)
    #define pottery_ring_lifecycle_move_bulk_restrict_impl POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_restrict_impl)
    #define pottery_ring_lifecycle_move_bulk_up POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_up)
    #define pottery_ring_lifecycle_move_bulk_up_impl POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_up_impl)
    #define pottery_ring_lifecycle_move_bulk_down POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_down)
    #define pottery_ring_lifecycle_move_bulk_down_impl POTTERY_CONCAT(POTTERY_RING_LIFECYCLE_PREFIX, _move_bulk_down_impl)
//!!! END_AUTOGENERATED



// alloc functions
#ifdef POTTERY_RING_EXTERNAL_ALLOC
    #define POTTERY_RING_ALLOC_PREFIX POTTERY_RING_EXTERNAL_ALLOC
#else
    #define POTTERY_RING_ALLOC_PREFIX POTTERY_RING_NAME(_alloc)
#endif
//!!! AUTOGENERATED:alloc/rename.m.h SRC:pottery_ring_alloc DEST:POTTERY_RING_ALLOC_PREFIX
    // This block is auto-generated. Do not modify until END_AUTOGENERATED.
    // Renames alloc identifiers from pottery_ring_alloc to POTTERY_RING_ALLOC_PREFIX

    #define pottery_ring_alloc_free POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _free)
    #define pottery_ring_alloc_impl_free_ea POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_free_ea)
    #define pottery_ring_alloc_impl_free_fa POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_free_fa)

    #define pottery_ring_alloc_malloc POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _malloc)
    #define pottery_ring_alloc_impl_malloc_ea POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_ea)
    #define pottery_ring_alloc_impl_malloc_fa POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_fa)

    #define pottery_ring_alloc_malloc_zero POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _malloc_zero)
    #define pottery_ring_alloc_impl_malloc_zero_ea POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_zero_ea)
    #define pottery_ring_alloc_impl_malloc_zero_fa POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_zero_fa)
    #define pottery_ring_alloc_impl_malloc_zero_fa_wrap POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_zero_fa_wrap)

    #define pottery_ring_alloc_malloc_array_at_least POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _malloc_array_at_least)
    #define pottery_ring_alloc_impl_malloc_array_at_least_ea POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_array_at_least_ea)
    #define pottery_ring_alloc_impl_malloc_array_at_least_fa POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _impl_malloc_array_at_least_fa)

    #define pottery_ring_alloc_malloc_array POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _malloc_array)
    #define pottery_ring_alloc_malloc_array_zero POTTERY_CONCAT(POTTERY_RING_ALLOC_PREFIX, _malloc_array_zero)
//!!! END_AUTOGENERATED
