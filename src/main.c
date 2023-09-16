#include "buffer.h"

int main(void)
{

    int* temp_buf = NULL;

    size_t N = 1024;

    for (int i = 0; i < N; ++i)
    {
        buffer_push(temp_buf, i);
    }

    buffer_free(temp_buf);

    return 0;
}
