#include "gtest/gtest.h"
#include "random_bytes.h"


TEST( random_bytes, get )
{
    random_bytes rb;

    ASSERT_NO_THROW( rb.get() );
	
}

