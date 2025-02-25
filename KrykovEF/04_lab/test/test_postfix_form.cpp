#include "postfix_form.h"
#include <gtest.h>

TEST(PosfixForm, postfixform_config_correctly_array_1)
{
    string s = "A+B";
    PosfixForm expr(s, ARRAY_STACK); 
    EXPECT_EQ("AB+", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_array_1)
{
    string s = "A+B";
    PosfixForm expr(s, ARRAY_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    EXPECT_EQ(3, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_list_1)
{
    string s = "A+B";
    PosfixForm expr(s, LIST_STACK);
    EXPECT_EQ("AB+", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_list_1)
{
    string s = "A+B";
    PosfixForm expr(s, LIST_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    EXPECT_EQ(3, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_array_2)
{
    string s = "A-B";
    PosfixForm expr(s, ARRAY_STACK);
    EXPECT_EQ("AB-", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_array_2)
{
    string s = "A-B";
    PosfixForm expr(s, ARRAY_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    EXPECT_EQ(-1, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_list_2)
{
    string s = "A-B";
    PosfixForm expr(s, LIST_STACK);
    EXPECT_EQ("AB-", expr.return_expr());

}
TEST(PosfixForm, postfixform_performs_solve_list_2)
{
    string s = "A-B";
    PosfixForm expr(s, LIST_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    EXPECT_EQ(-1, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_array_3)
{
    string s = "A-B*(A+C)";
    PosfixForm expr(s, ARRAY_STACK);
    EXPECT_EQ("ABAC+*-", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_array_3)
{
    string s = "A-B*(A+C)";
    PosfixForm expr(s, ARRAY_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    values["C"] = 3;
    EXPECT_EQ(-7, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_list_3)
{
    string s = "A-B*(A+C)";
    PosfixForm expr(s, LIST_STACK);
    EXPECT_EQ("ABAC+*-", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_list_3)
{
    string s = "A-B*(A+C)";
    PosfixForm expr(s, LIST_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 2;
    values["C"] = 3;
    EXPECT_EQ(-7, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_array_4)
{
    string s = "(A-B)/(C-A)*(K+B)+A";
    PosfixForm expr(s, ARRAY_STACK);
    EXPECT_EQ("AB-CA-/KB+*A+", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_array_4)
{
    string s = "(A-B)/(C-A)*(K+B)+A";
    PosfixForm expr(s, ARRAY_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 3;
    values["C"] = 2;
    values["K"] = -2;
    EXPECT_EQ(-1, expr.solve(values));

}

TEST(PosfixForm, postfixform_config_correctly_list_4)
{
    string s = "(A-B)/(C-A)*(K+B)+A";
    PosfixForm expr(s, LIST_STACK);
    EXPECT_EQ("AB-CA-/KB+*A+", expr.return_expr());

}
TEST(PosfixForm, postfixform_solve_correctly_list_4)
{
    string s = "(A-B)/(C-A)*(K+B)+A";
    PosfixForm expr(s, LIST_STACK);
    unordered_map<string, double> values;
    values["A"] = 1;
    values["B"] = 3;
    values["C"] = 2;
    values["K"] = -2;
    EXPECT_EQ(-1, expr.solve(values));

}
