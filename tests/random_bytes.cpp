#include <gtest/gtest.h>
#include "random_bytes.h"
#include <set>

static std::uint32_t count_set_bits( std::uint8_t n );
static std::uint32_t count_set_bits( const std::vector< std::uint8_t >& bytes );

TEST( random_bytes, get )
{
    for( std::size_t byte_no = 0; byte_no <= 1024; byte_no++ )
    {
        std::vector< std::uint8_t > bytes( byte_no );
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
    }
}

TEST( random_bytes, uniqueness )
{
    const std::size_t item_no = 10 * 1000;
    constexpr std::size_t byte_no = 128 / 8;
    std::vector< std::uint8_t > bytes( byte_no );
    std::set< std::vector< std::uint8_t > > set;

    for( std::size_t i = 0; i < item_no; i++ )
    {
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
        ASSERT_TRUE( set.insert( bytes ).second );
    }
}

TEST( random_bytes, randomness )
{
    const std::size_t item_no = 100 * 1000;
    constexpr std::size_t byte_no = 32;
    constexpr std::size_t bit_no = byte_no * 8;
    std::vector< std::uint8_t > bytes( byte_no );

    std::size_t count = 0;
    std::size_t total = 0;

    for( std::size_t i = 0; i < item_no; i++ )
    {
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
        count += count_set_bits( bytes );
        total += bit_no;
    }

    // std::cout << count << " " << total << "\n";

    const double fact = count / static_cast< double >( total );
    // std::cout << fact << "\n";
    ASSERT_TRUE( fact > 0.45 && fact < 0.55 );
}

//
//
// Return number of set bits in vector of positive integer
//
std::uint32_t count_set_bits( const std::vector< std::uint8_t >& bytes )
{
    std::uint32_t count = 0;
    for( const auto n : bytes )
    {
        count += count_set_bits( n );
    }
    return count;
}

//
//
// Return number of set bits in binary representation of positive integer n
//
std::uint32_t count_set_bits( std::uint8_t n )
{
    std::uint32_t count = 0;
    while( n )
    {
        count += n & 1U;
        n >>= 1U;
    }
    return count;
}

