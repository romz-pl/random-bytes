#ifndef ROMZ_RANDOM_BYTES_H
#define ROMZ_RANDOM_BYTES_H

#include <vector>
#include <cstdint>


class random_bytes
{
public:

    static void get( std::vector< std::uint8_t >& bytes );

};


#endif

