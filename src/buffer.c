#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "buffer.h"
#include "utils.h"

/**
 * @internal - Grows the buffer by a `x` amount
 *
 * buffer {const void*} - A pointer to a generic buffer NULL initialized or not
 * new_len {size_t} - The new len of the buffer
 * elem_size {size_t} - The size of the elements that the buffer holds
 *
 * returns {void*} - Pointer to the new buffer head
 *
 */
void* __buffer_grow(const void* buffer, size_t new_len, size_t elem_size)
{
    size_t new_cap = MAX(1 + 2 * buffer_cap(buffer), new_len);
    assert(new_len <= new_cap);
    size_t new_size = offsetof(Buffer, data) + new_cap * elem_size;
    assert(new_cap <= (SIZE_MAX - offsetof(Buffer, data)) / elem_size);

    Buffer* header;

    if (buffer)
    {
        header = realloc(__buffer_hdr(buffer), new_size);
    }
    else
    {
        header = malloc(new_size);
        header->length = 0;
    }

    header->capacity = new_cap;

    return header->data;
}
