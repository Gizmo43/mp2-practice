#include "Polinom.h"
#include <gtest.h>


TEST(Monom, can_create_monom)
{
    ASSERT_NO_THROW(Monom mn(3,3));
}

