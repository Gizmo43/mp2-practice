#include "Ring_head_list.h"
#include <gtest.h>


TEST(TRingHeadList, can_create_list)
{
    ASSERT_NO_THROW(TRingHeadList<float> list());
}


TEST(TRingHeadList, can_push_element_front)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    EXPECT_EQ(4, list.get_pFirst()->Key);
}

TEST(TRingHeadList, can_push_element_back)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    EXPECT_EQ(4, list.get_pCurr()->Key);
}
TEST(TRingHeadList, can_push_element_both)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(0, i);
        list.pushFront(0, i);
    }
    EXPECT_EQ(4, list.get_pCurr()->Data);
    EXPECT_EQ(4, list.get_pFirst()->Data);
}

TEST(TRingHeadList, can_pop_element_front)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.popFront();
    EXPECT_EQ(3, list.get_pFirst()->Key);
}

TEST(TRingHeadList, can_pop_element_back)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.popBack();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}


TEST(TRingHeadList, compare_equal_lists_return_true)
{
    TRingHeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TRingHeadList<int> list2;
    list2.pushFront(0, 1);
    list2.pushFront(1, 2);
    EXPECT_TRUE(list1 == list2);
}

TEST(TRingHeadList, compare_not_equal_lists_return_false_1)
{
    TRingHeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TRingHeadList<int> list2;
    list2.pushFront(0, 3);
    list2.pushFront(1, 4);
    EXPECT_FALSE(list1 == list2);
}

TEST(TRingHeadList, compare_not_equal_lists_return_false_2)
{
    TRingHeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TRingHeadList<int> list2;
    list2.pushFront(2, 1);
    list2.pushFront(3, 2);
    EXPECT_FALSE(list1 == list2);
}



TEST(TRingHeadList, can_copy)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    TRingHeadList<int> copy(list);
    EXPECT_EQ(list, copy);
}

TEST(TRingHeadList, copy_have_memory)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    TRingHeadList<int> copy(list);
    copy.pushFront(10, 0);
    EXPECT_FALSE(list == copy);
}

TEST(TRingHeadList, search_test)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.search_key(3);
    EXPECT_FALSE(list.get_pCurr()->Data == 3);
}

TEST(TRingHeadList, can_push_element_before_1)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(TRingHeadList, can_push_element_before_2)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 3);
    list.popFront();
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(TRingHeadList, can_push_element_after_1)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pCurr()->Key);
}

TEST(TRingHeadList, can_push_element_after_2)
{
    TRingHeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 3);
    list.popBack();
    EXPECT_EQ(10, list.get_pCurr()->Key);
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
    list1.pushBack(3, 4);
    EXPECT_FALSE(list1 == list2);
}

TEST(TRingHeadList, navigtion_test)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.reset();
    list.next();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}