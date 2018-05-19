#include <gtest/gtest.h>
#include "random_bytes.h"
#include <set>


TEST( random_bytes, get )
{
    std::vector< std::uint8_t > bytes( 128 );
    ASSERT_NO_THROW( random_bytes::get( bytes ) );
}

TEST( random_bytes, uniqueness )
{
    const std::size_t item_no = 10000;
    std::vector< std::uint8_t > bytes( 128 );
    std::set< std::vector< std::uint8_t > > set;

    for( std::size_t i = 0; i < item_no; i++ )
    {
        ASSERT_NO_THROW( random_bytes::get( bytes ) );
        ASSERT_TRUE( set.insert( bytes ).second );
    }
}

