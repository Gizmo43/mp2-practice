#include "Head_list.h"
#include <gtest.h>

TEST(THeadList, can_create_list)
{
    ASSERT_NO_THROW(THeadList<float> list());
}


TEST(THeadList, can_push_element_front)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    EXPECT_EQ(4, list.get_pFirst()->Key);
}

TEST(THeadList, can_push_element_back)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    EXPECT_EQ(4, list.get_pCurr()->Key);
}

TEST(THeadList, can_push_element_both)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(0, i);
        list.pushFront(0, i);
    }
    EXPECT_EQ(4, list.get_pCurr()->Data);
    EXPECT_EQ(4, list.get_pFirst()->Data);
}

TEST(THeadList, can_pop_element_front)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.popFront();
    EXPECT_EQ(3, list.get_pFirst()->Key);
}

TEST(THeadList, can_pop_element_back)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.popBack();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}


TEST(THeadList, compare_equal_lists_return_true)
{
    THeadList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
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


TEST(THeadList, can_copy)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    THeadList<int> copy(list);
    EXPECT_EQ(list, copy);
}

TEST(THeadList, copy_have_memory)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    THeadList<int> copy(list);
    copy.pushFront(10, 0);
    EXPECT_FALSE(list == copy);
}

TEST(THeadList, search_test)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.search_key(3);
    EXPECT_FALSE(list.get_pCurr()->Data == 3);
}

TEST(THeadList, can_push_element_before_1)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(THeadList, can_push_element_before_2)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 3);
    list.popFront();
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(THeadList, can_push_element_after_1)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pCurr()->Key);
}

TEST(THeadList, can_push_element_after_2)
{
    THeadList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 3);
    list.popBack();
    EXPECT_EQ(10, list.get_pCurr()->Key);
}

TEST(THeadList, navigtion_test)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.reset();
    list.next();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}


