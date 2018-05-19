#include "random_bytes.h"

#include <openssl/rand.h>
#include <openssl/err.h>


std::vector< std::uint8_t > random_bytes::get()
{
    unsigned char buffer[128];
    int rc = RAND_bytes(buffer, sizeof(buffer));
    unsigned long err = ERR_get_error();

    if(rc != 1) {
        /* RAND_bytes failed */
        /* `err` is valid    */
    }

    return std::vector< std::uint8_t >();
}


