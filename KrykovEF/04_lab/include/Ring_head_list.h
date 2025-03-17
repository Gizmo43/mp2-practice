#pragma once
#ifndef RING_HEAD_LIST_H
#define RING_HEAD_LIST_H
#include "Head_list.h"

template <typename T>
class TRingHeadList : public THeadList<T> {
public:
    TRingHeadList();
    TRingHeadList(const TRingHeadList<T>& list);
    ~TRingHeadList();
    const TRingHeadList& operator=(const TRingHeadList<T>& s);
    virtual void pushFront(int key, T val);
    virtual void pushBack(int key, T val);
    virtual void popFront();
    virtual void popBack();
};


template <typename T>
TRingHeadList<T>::TRingHeadList() : THeadList<T>() {
    pStop = pHead;
};

template <typename T>
TRingHeadList<T>::TRingHeadList(const TRingHeadList<T>& list) : THeadList<T>(list) {
    if (pLast != nullptr)
        pLast->pNext = pHead;
    pStop = pHead;
};
template <typename T>
TRingHeadList<T>::~TRingHeadList() {
    pStop = nullptr;
    pLast->pNext = nullptr;
    THeadList<T>::~THeadList();
};


template <typename T>
const TRingHeadList<T>& TRingHeadList<T>::operator=(const TRingHeadList<T>& list) {
    if (this == &list)
        return *this;
    while (!IsEmpty()) {
        popFront();
    }
    TNode<T>* curr = list.pFirst;
    while (curr != list.pStop) {
        pushBack(curr->Key, curr->Data);
        curr = curr->pNext;
    }
    pStop = pHead;
    if (pLast != nullptr) {
        pLast->pNext = pHead;
    }
    return *this;
}

template <typename T>
void TRingHeadList<T>::pushFront(int key, T val) {
    THeadList<T>::pushFront(key, val);
    pLast->pNext = pHead;
};

template <typename T>
void TRingHeadList<T>::pushBack(int key, T val) {
    TList<T>::pushBack(key, val);
    pLast->pNext = pHead;
};

template <typename T>
void TRingHeadList<T>::popFront() {
    THeadList<T>::popFront();
    pLast->pNext = pHead;
};

template <typename T>
void TRingHeadList<T>::popBack() {
    TList<T>::popBack();
    pLast->pNext = pHead;
};



#endif