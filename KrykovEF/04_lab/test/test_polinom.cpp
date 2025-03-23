#include "Polinom.h"
#include <gtest.h>


TEST(Monom, can_create_monom)
{
    ASSERT_NO_THROW(Monom mn(3,3));
}

TEST(Monom, can_add_monom)
{
    Monom mn1(3, 3);
    Monom mn2(4, 3);
    Monom mn3(7, 3);
    EXPECT_EQ(mn1 + mn2, mn3);
}

TEST(Monom, cant_add_monom_with_wrong_deg)
{
    Monom mn1(3, 3);
    Monom mn2(4, 4);
    ASSERT_ANY_THROW(mn1 + mn2);
}

TEST(Monom, can_sub_monom)
{
    Monom mn1(3, 3);
    Monom mn2(4, 3);
    Monom mn3(7, 3);
    EXPECT_EQ(mn3 - mn2, mn1);
}

TEST(Monom, cant_sub_monom_with_wrong_deg)
{
    Monom mn1(3, 3);
    Monom mn2(4, 4);
    ASSERT_ANY_THROW(mn2 - mn1);
}

TEST(Monom, can_mult_monom_1)
{
    Monom mn1(3, 3);
    Monom mn2(4, 3);
    Monom mn3(12, 6);
    EXPECT_EQ(mn1 * mn2, mn3);
}

TEST(Monom, can_mult_monom_2)
{
    Monom mn1(3, 3);
    Monom mn2(12, 3);
    EXPECT_EQ(mn1 * 4, mn2);
}

TEST(Monom, cant_mult_monom_with_wrong_deg)
{
    Monom mn1(3, 3);
    Monom mn2(4, 4);
    ASSERT_ANY_THROW(mn2 * mn1);
}


/*TEST(Polinom, can_create_empty_Polinom)
{
    ASSERT_NO_THROW(Polinom pl());
}

TEST(Polinom, can_create_Polinom)
{
    ASSERT_NO_THROW(Polinom pl("2x1y2z3+x3z4-5"));
}

TEST(Polinom, cant_create_Polinom_with_wrong_deg)
{
    ASSERT_ANY_THROW(Polinom pl("2x10y2z3+x3z4-5"));
}*/

TEST(Polinom, tmp)
{
    Polinom pl("-5+2x1y2z3+x3z4-5+6x1y1z1");
    cout << pl.get_polinom_str();
    EXPECT_EQ(1, 1);
}




