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

//!!! END_LICENSE
// Un-renames array identifiers with prefix "{PREFIX}"

// types
#undef {PREFIX}_t
#undef {PREFIX}_value_t
#undef {PREFIX}_ref_t
#undef {PREFIX}_entry_t
#undef {PREFIX}_context_t

// fundamental operations
#undef {PREFIX}_copy
#undef {PREFIX}_destroy
#undef {PREFIX}_init
#undef {PREFIX}_init_copy
#undef {PREFIX}_init_steal
#undef {PREFIX}_move
#undef {PREFIX}_steal
#undef {PREFIX}_swap

// entry operations
#undef {PREFIX}_entry_exists
#undef {PREFIX}_entry_equal
#undef {PREFIX}_entry_value

// lookup
#undef {PREFIX}_count
#undef {PREFIX}_is_empty
#undef {PREFIX}_at
#undef {PREFIX}_first
#undef {PREFIX}_last
#undef {PREFIX}_any

// iteration
#undef {PREFIX}_select
#undef {PREFIX}_index
#undef {PREFIX}_begin
#undef {PREFIX}_end
#undef {PREFIX}_next
#undef {PREFIX}_previous

// misc
#undef {PREFIX}_reserve
#undef {PREFIX}_shrink

// insert
#undef {PREFIX}_insert_at
#undef {PREFIX}_insert_first
#undef {PREFIX}_insert_last
#undef {PREFIX}_insert_before
#undef {PREFIX}_insert_after
#undef {PREFIX}_insert_at_bulk
#undef {PREFIX}_insert_first_bulk
#undef {PREFIX}_insert_last_bulk
#undef {PREFIX}_insert_before_bulk
#undef {PREFIX}_insert_after_bulk

// emplace
#undef {PREFIX}_emplace_at
#undef {PREFIX}_emplace_first
#undef {PREFIX}_emplace_last
#undef {PREFIX}_emplace_before
#undef {PREFIX}_emplace_after
#undef {PREFIX}_emplace_at_bulk
#undef {PREFIX}_emplace_first_bulk
#undef {PREFIX}_emplace_last_bulk
#undef {PREFIX}_emplace_before_bulk
#undef {PREFIX}_emplace_after_bulk

// construct
#undef {PREFIX}_construct_at
#undef {PREFIX}_construct_first
#undef {PREFIX}_construct_last
#undef {PREFIX}_construct_before
#undef {PREFIX}_construct_after

// extract
#undef {PREFIX}_extract
#undef {PREFIX}_extract_at
#undef {PREFIX}_extract_first
#undef {PREFIX}_extract_last
#undef {PREFIX}_extract_and_next
#undef {PREFIX}_extract_and_previous

// remove
#undef {PREFIX}_remove
#undef {PREFIX}_remove_at
#undef {PREFIX}_remove_first
#undef {PREFIX}_remove_last
#undef {PREFIX}_remove_and_next
#undef {PREFIX}_remove_and_previous
#undef {PREFIX}_remove_all
#undef {PREFIX}_remove_at_bulk
#undef {PREFIX}_remove_first_bulk
#undef {PREFIX}_remove_last_bulk
#undef {PREFIX}_remove_at_bulk

// displace
#undef {PREFIX}_displace
#undef {PREFIX}_displace_at
#undef {PREFIX}_displace_first
#undef {PREFIX}_displace_last
#undef {PREFIX}_displace_and_next
#undef {PREFIX}_displace_and_previous
#undef {PREFIX}_displace_all
#undef {PREFIX}_displace_at_bulk
#undef {PREFIX}_displace_first_bulk
#undef {PREFIX}_displace_last_bulk
