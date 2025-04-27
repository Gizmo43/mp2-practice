#include "Polinom.h"
#include <gtest.h>


TEST(Monom, can_create_monom)
{
    ASSERT_NO_THROW(Monom mn(3,3));
}

TEST(Monom, can_add_monom)
{
    Monom mn1(3, 3);
    Monom mn2(3, 4);
    Monom mn3(3, 7);
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
    Monom mn2(3, 4);
    Monom mn3(3, 7);
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
    Monom mn2(3, 4);
    Monom mn3(6, 12);
    EXPECT_EQ(mn1 * mn2, mn3);
}

TEST(Monom, can_mult_monom_2)
{
    Monom mn1(3, 3);
    Monom mn2(3, 12);
    EXPECT_EQ(mn1 * 4, mn2);
}

TEST(Monom, cant_mult_monom_with_wrong_deg)
{
    Monom mn1(666, 3);
    Monom mn2(444, 4);
    ASSERT_ANY_THROW(mn2 * mn1);
}


TEST(Polinom, can_create_empty_Polinom)
{
    ASSERT_NO_THROW(Polinom pl());
}

TEST(Polinom, can_create_Polinom_1)
{
    Polinom pl("2x1y2z3+x3z4-7.5");
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-7.50+2.00x1y2z3+x3z4", pl.get_polinom_str());
}

TEST(Polinom, can_create_Polinom_2)
{
    Polinom pl("-5+3.2x1y1z1+2x1y2z3+x3z4+6x1y1z1-2x3z4+7x2y3");
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-5.00+9.20x1y1z1+2.00x1y2z3+7.00x2y3-x3z4", pl.get_polinom_str());
}
TEST(Polinom, can_create_Polinom_3)
{
    Polinom pl("4");
    //cout << pl.get_polinom_str();
    EXPECT_EQ("4.00", pl.get_polinom_str());
}

TEST(Polinom, can_create_Polinom_4)
{
    Polinom pl("4+2.00x1y2z3-2.00x1y2z3");
    //cout << pl.get_polinom_str();
    EXPECT_EQ("4.00", pl.get_polinom_str());
}

TEST(Polinom, cant_create_Polinom_with_wrong_deg)
{
    ASSERT_ANY_THROW(Polinom pl("2x10y2z3+x3z4-5"));
}


TEST(Polinom, can_calculate_Polinom_1)
{
    Polinom pl("2x1y2z3+x3z4-7.5");
    EXPECT_EQ(289.5, pl(1, 2, 3));
}

TEST(Polinom, can_calculate_Polinom_2)
{
    Polinom pl("-5+3.2x1y1z1+2x1y2z3+x3z4+6x1y1z1-2x3z4+7x2y3");
    EXPECT_EQ(241.2, pl(1, 2, 3));
}

TEST(Polinom, can_calculate_Polinom_3)
{
    Polinom pl("2x1y2z3+x3z4");
    EXPECT_EQ(0, pl(0, 0, 0));
}

TEST(Polinom, can_calculate_Polinom_4)
{
    Polinom pl("7.5");
    EXPECT_EQ(7.5, pl(10, 10, 10));
}





TEST(Polinom, can_add_Polinom_1)
{
    Polinom pl1("2x1y2z3+x3z4-7.5");
    Polinom pl2("3x1y2z3+2x3z4-1.5");
    Polinom pl3 = pl1 + pl2;
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-9.00+5.00x1y2z3+3.00x3z4", pl3.get_polinom_str());
}



TEST(Polinom, can_add_Polinom_2)
{
    Polinom pl1("2x1y2z3+x3z4-7.5");
    Monom mn2(123,4);
    Polinom pl3 = pl1 + mn2;
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-7.50+6.00x1y2z3+x3z4", pl3.get_polinom_str());
}

TEST(Polinom, can_mult_Polinom_1)
{
    Polinom pl("2x1y2z3+x3z4-7.5");
    Polinom res = pl * 2;
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-15.00+4.00x1y2z3+2.00x3z4", res.get_polinom_str());
}

TEST(Polinom, can_sub_Polinom_1) //не работает из-за нерабочего умножения
{
    Polinom pl1("2x1y2z3+x3z4-7.5");
    Polinom pl2("3x1y2z3+2x3z4-1.5");
    Polinom pl3 = pl2 - pl1;
    //cout << pl.get_polinom_str();
    EXPECT_EQ("6.00+x1y2z3+x3z4", pl3.get_polinom_str());
}



TEST(Polinom, can_sub_Polinom_2)
{
    Polinom pl1("2x1y2z3+x3z4-7.5");
    Monom mn2(123, 4);
    Polinom pl3 = pl1 - mn2;
    //cout << pl.get_polinom_str();
    EXPECT_EQ("-7.50-2.00x1y2z3+x3z4", pl3.get_polinom_str());
}

TEST(Polinom, sub_equal_polinoms_returns_empty) {
    Polinom pl1("3x2y-5z");
    Polinom pl2("3x2y-5z");
    Polinom res = pl1 - pl2;
    EXPECT_TRUE(res.get_polinom_str().empty());
}

TEST(Polinom, can_mult_two_polinoms) {
    Polinom pl1("2x1y2z3+x3z4-7.5+x4y4z4");
    Polinom pl2("3x1y2z3+2x3z4-1.5");
    Polinom res = pl1 * pl2;
    EXPECT_EQ("11.25-25.50x1y2z3+6.00x2y4z6-16.50x3z4+7.00x4y2z7-1.50x4y4z4+3.00x5y6z7+2.00x6z8+2.00x7y4z8", res.get_polinom_str());
}





