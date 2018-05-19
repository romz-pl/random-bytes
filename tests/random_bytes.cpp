#include <gtest/gtest.h>
#include "random_bytes.h"
#include <set>
#include <thread>
#include <functional>
#include <algorithm>


static std::uint32_t count_set_bits( std::uint8_t n );
static std::uint32_t count_set_bits( const std::vector< std::uint8_t >& bytes );
static void collect( std::vector< std::vector< std::uint8_t > >& byte_seq, const std::uint32_t item_no );

//
//
//
TEST( random_bytes, get )
{
    for( std::size_t byte_no = 0; byte_no <= 1024; byte_no++ )
    {
        std::vector< std::uint8_t > bytes( byte_no );
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
    }
}

//
//
//
TEST( random_bytes, uniqueness )
{
    constexpr std::size_t item_no = 100 * 1000;
    constexpr std::size_t byte_no = 16;
    std::vector< std::uint8_t > bytes( byte_no );
    std::set< std::vector< std::uint8_t > > set;

    for( std::size_t i = 0; i < item_no; i++ )
    {
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
        ASSERT_TRUE( set.insert( bytes ).second );
    }
}

//
//
//
TEST( random_bytes, randomness )
{
    constexpr std::size_t item_no = 100 * 1000;
    constexpr std::size_t byte_no = 16;
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
//
TEST( random_bytes, two_threads )
{
    std::vector< std::vector< std::uint8_t > > seq_a;
    std::vector< std::vector< std::uint8_t > > seq_b;

    const std::uint32_t item_no_a = 1000;
    const std::uint32_t item_no_b = 2000;

    std::thread ta( collect, std::ref( seq_a ), item_no_a );
    std::thread tb( collect, std::ref( seq_b ), item_no_b );

    ta.join();
    tb.join();

    ASSERT_TRUE( std::find_first_of( seq_a.begin(), seq_a.end(), seq_b.begin(), seq_b.end() ) == seq_a.end() );
}

//
//
//
void collect( std::vector< std::vector< std::uint8_t > >& seq, const std::uint32_t item_no )
{
    constexpr std::size_t byte_no = 16;
    std::vector< std::uint8_t > bytes( byte_no );

    for( std::uint32_t i = 0; i < item_no; i++ )
    {
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
        seq.push_back( bytes );

    }
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

