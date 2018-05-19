#include "random_bytes.h"

#include <openssl/rand.h>
#include <openssl/err.h>
#include <stdexcept>

// Static member of class random_bytes
std::mutex random_bytes::m_mutex;

void random_bytes::get( std::vector< std::uint8_t >& bytes )
{
    std::lock_guard< std::mutex > lock( m_mutex, std::adopt_lock );

    const int rc = RAND_bytes( bytes.data(), bytes.size() );
    if( rc != 1 )
    {
        const unsigned long err = ERR_get_error();
        const std::string txt = "OpenSSL: RAND_bytes. Error: " + std::to_string( err );
        throw std::runtime_error( txt );
    }
}
