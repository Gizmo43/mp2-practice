#include "Ring_head_list.h"
#include <gtest.h>

TEST(THeadList, can_create_list)
{
    ASSERT_NO_THROW(THeadList<float> list());
}

TEST(THeadList, can_push_element)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(0,i);
    EXPECT_EQ(4, list.get_first_data());
}


TEST(THeadList, compare_equal_lists_return_true)
{
    THeadList<int> list1;
    list1.pushFront(0,1);
    list1.pushFront(1,2);
    THeadList<int> list2;
    list2.pushFront(0, 1);
    list2.pushFront(1, 2);
    EXPECT_TRUE(list1 == list2);
}

TEST(THeadList, compare_not_equal_lists_return_false_1)
{
    THeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    THeadList<int> list2;
    list2.pushFront(0, 3);
    list2.pushFront(1, 4);
    EXPECT_FALSE(list1 == list2);
}

TEST(THeadList, compare_not_equal_lists_return_false_2)
{
    THeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    THeadList<int> list2;
    list2.pushFront(2, 1);
    list2.pushFront(3, 2);
    EXPECT_FALSE(list1 == list2);
}

TEST(THeadList, test_op)
{
    THeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    THeadList<int> list2 = list1;
    EXPECT_TRUE(list1 == list2);
}

TEST(TRingHeadList, can_create_list)
{
    ASSERT_NO_THROW(TRingHeadList<float> list());
}

TEST(TRingHeadList, can_push_element_front)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(0, i);
    EXPECT_EQ(4, list.get_first_data());
}

TEST(TRingHeadList, can_push_element_back)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(0, i);
    EXPECT_EQ(4, list.get_last_data());
}

TEST(TRingHeadList, can_push_element_both)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(0, i);
        list.pushFront(0, i);
    }
    EXPECT_EQ(4, list.get_last_data());
    EXPECT_EQ(4, list.get_first_data());
}

TEST(TRingHeadList, can_pop_element_back)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(0, i);
    }
    list.popBack();
    EXPECT_EQ(3, list.get_last_data());
}
TEST(TRingHeadList, can_pop_element_front)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushFront(0, i);
    }
    list.popFront();
    EXPECT_EQ(3, list.get_first_data());
}

TEST(TRingHeadList, test_op_1)
{
    TRingHeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TRingHeadList<int> list2;
    list2 = list1;
    EXPECT_TRUE(list1 == list2);
}

TEST(TRingHeadList, test_op_2)
{
    TRingHeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TRingHeadList<int> list2;
    list2 = list1;
    list2.pushBack(2, 3);
    list1.pushBack(2, 4);
    EXPECT_FALSE(list1 == list2);
}



