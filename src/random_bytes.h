#ifndef ROMZ_RANDOM_BYTES_H
#define ROMZ_RANDOM_BYTES_H

#include <vector>
#include <cstdint>
#include <mutex>



class random_bytes
{
public:

    static void get( std::vector< std::uint8_t >& bytes );

private:
    static std::mutex m_mutex;

};


#endif

