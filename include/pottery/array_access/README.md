# Array Access

This is a helper template for other Pottery containers. It is not intended to be used directly.

The array access template wraps a configured set of array access expressions over a generalized array. These make it possible for Pottery algorithms to operate efficiently on abstract arrays that do not need to be contiguous in memory and do not need to be in memory at all.

The functions instantiated by this template provide abstract array access and iteration. The main functions are:

- `select()` -- Get the ref at an index, or the end ref if the index is the end of the array
- `index()` -- Get the index of a ref
- `shift()` -- Shifts a ref forwards or backwards by a signed offset
- `offset()` -- Calculates the offset (difference in index) between two refs
- `next()` -- Get the ref following a given ref
- `previous()` -- Get the ref preceding a given ref
- `equal()` -- Compare refs for equality (true if they refer to the same element)

In addition, if the context has an inherent range of elements (like a container for example), the template can instantiate functions to access that range:

- `begin()` -- Get a ref to the first element, or the end ref if the context is empty
- `end()` -- Get the end ref
- `count()` -- Get the total number of elements
- `exists()` -- Check whether a ref exists (false if it is the end ref, true otherwise)



## Description



### Inherent Base and Count

The array access context may have an inherent base ref and/or an inherent element count. For example, if the context is a container, it has an inherent range of elements. In this case a separate base ref does not need to be passed to array access functions because it can be retrieved from the context.

Defining `BEGIN` enables "inherent base" mode and defines `POTTERY_ARRAY_ACCESS_INHERENT_BASE` to 1. When this is disabled (the default), all configuration options and all instantiated functions take an additional base ref parameter (after the context, if any.)

Defining `COUNT` or `END` (or both) enables "inherent count" mode and defines `POTTERY_ARRAY_ACCESS_INHERENT_COUNT` to 1. This instantiates additional functions `end()`, `count()` and `exists()` for interacting with the inherent count of the context.

If you want to instantiate a sort template to sort a [vector](../vector) for example, you can make the vector the context and define `BEGIN` and `END`/`COUNT`, giving it an inherent range and enabling both of the above modes. This will instantiate a sort function that takes only the vector itself as argument and sorts its entire contents.

Note that the context is still optional even if there is an inherent base and count. You could use this for example to define a hash table or sort function that operates on static storage.



### End Ref

The configured ref type must support an "end ref" for any valid range of elements. This is a ref whose index is one past the end of the range. All configured operations must work on such a ref.

The ref doesn't actually have to "be" one past the end. The end ref of a container can be null for example. It just has to work as though it is one past the end:

- `SELECT` on the total number of elements must return the end ref;
- `INDEX` on the end ref must return the total number of elements;
- `NEXT` on the last element must return the end ref;
- `PREVIOUS` on the end ref must return the last ref;
- `EXISTS` must return false on the end ref and true on all other refs;
- `EQUAL` must return true if both refs are the end ref and false if only one is the end ref.

This is why the template expects `SELECT` and provides a `select()` function rather than an `at()` function. A `select()` on the total number of elements is valid and returns the (unique) non-existent end ref.



### Ref Comparisons

The array access template must be able to compare refs for equality. You can define a custom comparison expression via `EQUAL`. If this is not defined, the template will compare refs by their index in the array.

Any two refs that have the same index must compare equal. This includes the end ref. Equality on two end ref values must be true, no matter how the end ref is obtained (for example if a ref is repeatedly shifted via `next()`, it must eventually compare equal to the ref obtained by `end()`.)



## Configuration Options

Many of these can be synthesized automatically if not defined. For example if `EQUAL` is not defined it will be synthesized by comparing the `INDEX` of the refs. However you can often improve performance by defining more of them.

For example if the array is a weight-balanced tree, you should define `NEXT` and `PREVIOUS` (especially if the tree has next and previous pointers.) Otherwise `next()` and `previous()` will have to walk up to the root of the tree and back down again just to shift the absolute index of a ref by 1.

Documentation of configuration options and API reference is incomplete.
