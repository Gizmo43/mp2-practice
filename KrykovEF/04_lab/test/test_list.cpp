#include "List.h"
#include <gtest.h>



TEST(TList, can_create_list)
{
    ASSERT_NO_THROW(TList<float> list());
}


TEST(TList, can_push_element_front)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    EXPECT_EQ(4, list.get_pFirst()->Key);
}

TEST(TList, can_push_element_back)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    EXPECT_EQ(4, list.get_pCurr()->Key);
}

TEST(TList, can_push_element_both)
{
    TList<int> list;
    for (int i = 0; i < 5; i++) {
        list.pushBack(0, i);
        list.pushFront(0, i);
    }
    EXPECT_EQ(4, list.get_pCurr()->Data);
    EXPECT_EQ(4, list.get_pFirst()->Data);
}

TEST(TList, can_pop_element_front)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.popFront();
    EXPECT_EQ(3, list.get_pFirst()->Key);
}

TEST(TList, can_pop_element_back)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.popBack();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}


TEST(TList, compare_equal_lists_return_true)
{
    TList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TList<int> list2;
    list2.pushFront(0, 1);
    list2.pushFront(1, 2);
    EXPECT_TRUE(list1 == list2);
}

TEST(TList, compare_not_equal_lists_return_false_1)
{
    TList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TList<int> list2;
    list2.pushFront(0, 3);
    list2.pushFront(1, 4);
    EXPECT_FALSE(list1 == list2);
}

TEST(TList, compare_not_equal_lists_return_false_2)
{
    TList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TList<int> list2;
    list2.pushFront(2, 1);
    list2.pushFront(3, 2);
    EXPECT_FALSE(list1 == list2);
}

TEST(TList, test_op)
{
    TList<int> list1;
    list1.pushFront(0, 1);
    list1.pushFront(1, 2);
    TList<int> list2 = list1;
    EXPECT_TRUE(list1 == list2);
}


TEST(TList, can_copy)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    TList<int> copy(list);
    EXPECT_EQ(list, copy);
}

TEST(TList, copy_have_memory)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    TList<int> copy(list);
    copy.pushFront(10, 0);
    EXPECT_FALSE(list == copy);
}

TEST(TList, search_test)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.search_key(3);
    EXPECT_FALSE(list.get_pCurr()->Data == 3);
}

TEST(TList, can_push_element_before_1)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(TList, can_push_element_before_2)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.InsertBeforeKey(10, 0, 3);
    list.popFront();
    EXPECT_EQ(10, list.get_pFirst()->Key);
}

TEST(TList, can_push_element_after_1)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 4);
    EXPECT_EQ(10, list.get_pCurr()->Key);
}

TEST(TList, can_push_element_after_2)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushBack(i, 0);
    list.InsertAfterKey(10, 0, 3);
    list.popBack();
    EXPECT_EQ(10, list.get_pCurr()->Key);
}


TEST(TList, navigtion_test)
{
    TList<int> list;
    for (int i = 0; i < 5; i++)
        list.pushFront(i, 0);
    list.reset();
    list.next();
    EXPECT_EQ(3, list.get_pCurr()->Key);
}


