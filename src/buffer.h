#ifndef _BUFFER_H
#define _BUFFER_H

#include <stddef.h>
#include <stdlib.h>

struct _buffer
{
    size_t length;
    size_t capacity;
    char data[0];
};
typedef struct _buffer Buffer;

/**
 * @internal - Calculate the buffer header
 *
 * b {buffer} - The buffer itself
 *
 * returns {size_t} - The offset of the buffer header
 *
 */
#define __buffer_hdr(b) ((Buffer*)((char*)(b)-offsetof(Buffer, data)))

/**
 * @internal -  Check if the `buffer` can fit a `n` amount of elements
 *
 * b {buffer} - The buffer itself
 * n {size_t} - Number of elements to fit
 *
 * returns {bool} - `true` if the buffer can fit `n` elements otherwise `false`
 *
 */
#define __buffer_fits_n(b, n) ((buffer_len(b) + (n)) <= buffer_cap(b))

/**
 * @internal -  Check if the `buffer` can fit a `n` amount of elements using
 *  using @internal __buffer_fits_n, if it can't resize the buffer
 *
 * b {buffer} - The buffer itself
 * n {size_t} - Number of elements to fit
 *
 * returns {void} - No return but it does generate a side-effect
 *
 */
#define __buffer_fit(b, n)                                                     \
    (__buffer_fits_n(b, n)                                                     \
         ? 0                                                                   \
         : ((b) = __buffer_grow(b, buffer_len(b) + (n), sizeof(*(b)))))

/**
 * @public - Returns the buffer length
 *
 * b {buffer} - The buffer itself
 *
 * returns {size_t} - The length of the buffer itself
 *
 */
#define buffer_len(b) ((b) ? __buffer_hdr(b)->length : 0)

/**
 * @public - Returns the buffer capacity
 *
 * b {buffer} - The buffer itself
 *
 * returns {size_t} - The capacity of the buffer itself
 *
 */
#define buffer_cap(b) ((b) ? __buffer_hdr(b)->capacity : 0)

/**
 * @public - Pushes a new element onto the buffer
 *
 * b {buffer} - The buffer itself
 *
 * returns {void} - No return but it does generate a side-effect
 *
 */
#define buffer_push(b, ...)                                                    \
    (__buffer_fit(b, 1), b[buffer_len(b)] = (__VA_ARGS__),                     \
     __buffer_hdr(b)->length++)

/**
 * @public - Returns the end of the buffer
 *
 * b {buffer} - The buffer itself
 *
 * returns {size_t} - End of the buffer
 *
 */
#define buffer_end(b) ((b) + buffer_len(b))

/**
 * @public - Free the buffer
 *
 * b {buffer} - The buffer itself
 *
 * returns {void} - No return but it does generate a side-effect
 *
 */
#define buffer_free(b) ((b) ? (free(__buffer_hdr(b)), (b) = NULL) : 0)

/**
 * @internal - Grows the buffer by a `x` amount
 */
void* __buffer_grow(const void* buffer, size_t new_len, size_t elem_size);

#endif // _BUFFER_H
