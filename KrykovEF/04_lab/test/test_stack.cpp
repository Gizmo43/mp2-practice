#include "Array_stack.h"
#include "List_stack.h"

#include <gtest.h>

TEST(TArrayStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TArrayStack<int> st(5));
}

TEST(TArrayStack, cant_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TArrayStack<int> st(-1));
}

TEST(TArrayStack, can_push_element)
{
    TArrayStack<int> st(5);
    for (int i = 0; i < 5; i++)
        st.push(i);
    EXPECT_EQ(4, st.Top());
}

TEST(TArrayStack, can_pop_element)
{
    TArrayStack<int> st(5);
    for (int i = 0; i < 5; i++)
        st.push(i);
    st.pop();
    EXPECT_EQ(3, st.Top());
}

TEST(TArrayStack, cant_pop_element_from_empty_stack)
{
    TArrayStack<int> st(5);
    ASSERT_ANY_THROW(st.pop());
}

TEST(TArrayStack, can_get_top)
{
    TArrayStack<int> st(5);
    st.push(4);
    EXPECT_EQ(4, st.Top());
}

TEST(TArrayStack, cant_get_top_from_empty_stack)
{
    TArrayStack<int> st(5);
    ASSERT_ANY_THROW(st.Top());
}

TEST(TArrayStack, can_check_empty)
{
    TArrayStack<int> st(5);
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TArrayStack, can_check_full)
{
    TArrayStack<int> st(5);
    for (int i = 0; i < 5; i++)
        st.push(i);

    EXPECT_TRUE(st.IsFull());
}

TEST(TArrayStack, copied_stack_is_equal_to_source_one)
{
    TArrayStack<int> st(1);
    st.push(1);
    TArrayStack<int> st_c(st);
    EXPECT_TRUE(st == st_c);
}

TEST(TArrayStack, copied_stack_has_its_own_memory)
{
    TArrayStack<int> st(2);
    st.push(1);
    st.push(2);
    TArrayStack<int> st_c(st);
    st_c.pop();
    st_c.push(3);
    EXPECT_NE(st, st_c);
}

TEST(TArrayStack, can_assign_stack_to_itself)
{
    TArrayStack<int> st(2);
    for (int i = 0; i < 2; i++)
        st.push(i);
    ASSERT_NO_THROW(st = st);
}

TEST(TArrayStack, can_assign_stacks_with_diff_size)
{
    TArrayStack<int> st1(4);
    TArrayStack<int> st2(5);
    st1 = st2;
    EXPECT_TRUE(st1 == st2);
}

TEST(TArrayStack, compare_equal_stacks_return_true)
{
    TArrayStack<int> st1(2);
    st1.push(1);
    st1.push(2);
    TArrayStack<int> st2(2);
    st2.push(1);
    st2.push(2);
    EXPECT_TRUE(st1 == st2);
}

TEST(TArrayStack, compare_stacks_with_diff_size_return_false)
{
    TArrayStack<int> st1(1);
    TArrayStack<int> st2(2);
    EXPECT_FALSE(st1 == st2);
}

TEST(TArrayStack, compare_not_equal_stacks_return_false)
{
    TArrayStack<int> st1(2);
    st1.push(1);
    st1.push(2);
    TArrayStack<int> st2(2);
    st2.push(3);
    st2.push(4);
    EXPECT_FALSE(st1 == st2);
}


TEST(TListStack, can_create_stack)
{
    ASSERT_NO_THROW(TListStack<int> st());
}

TEST(TListStack, can_push_element)
{
    TListStack<int> st;
    for (int i = 0; i < 5; i++)
        st.push(4);
    EXPECT_EQ(41, 41);
}

TEST(TListStack, can_pop_element)
{
    TListStack<int> st;

    for (int i = 0; i < 5; i++)
        st.push(i);
    st.pop();
    EXPECT_EQ(3, st.Top());
}

TEST(TListStack, cant_pop_element_from_empty_stack)
{
    TListStack<int> st;
    ASSERT_ANY_THROW(st.pop());
}


TEST(TListStack, can_get_top)
{
    TListStack<int> st;
    st.push(4);
    EXPECT_EQ(4, st.Top());
}

TEST(TListStack, cant_get_top_from_empty_stack)
{
    TListStack<int> st;
    ASSERT_ANY_THROW(st.Top());
}

TEST(TListStack, can_check_empty)
{
    TListStack<int> st;
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TListStack, copied_stack_is_equal_to_source_one)
{
    TListStack<int> st;
    st.push(1);
    st.push(2);
    TListStack<int> st_c(st);
    EXPECT_TRUE(st == st_c);
}

TEST(TListStack, copied_stack_has_its_own_memory)
{
    TListStack<int> st;
    st.push(1);
    st.push(2);
    TListStack<int> st_c(st);
    st_c.pop();
    st_c.push(3);
    EXPECT_NE(st.Top(), st_c.Top());
}

TEST(TListStack, can_assign_stack_to_itself)
{
    TListStack<int> st;
    for (int i = 0; i < 2; i++)
        st.push(i);
    ASSERT_NO_THROW(st = st);
}

TEST(TListStack, compare_equal_stacks_return_true)
{
    TListStack<int> st1;
    st1.push(1);
    st1.push(2);
    TListStack<int> st2;
    st2.push(1);
    st2.push(2);
    EXPECT_TRUE(st1 == st2);
}

TEST(TListStack, compare_not_equal_stacks_return_false)
{
    TListStack<int> st1;
    st1.push(1);
    st1.push(2);
    TListStack<int> st2;
    st2.push(3);
    st2.push(4);
    EXPECT_FALSE(st1 == st2);
}






