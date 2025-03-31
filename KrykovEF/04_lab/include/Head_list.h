#ifndef HEAD_LIST_H
#define HEAD_LIST_H

#include "List.h"

template <typename T>
class THeadList :public TList<T>{
protected:
    TNode<T>* pHead;
public:
    THeadList();
    THeadList(const THeadList<T>& list);
    ~THeadList();
    virtual void pushFront(int key, T val);
    virtual void popFront();
    virtual const THeadList<T>& operator=(const THeadList<T>& s);
};

template <typename T>
THeadList<T>::THeadList() : TList<T>() {
    pHead = new TNode<T>(-1, T());
    pHead->pNext = pFirst;
};

template <typename T>
THeadList<T>::THeadList(const THeadList<T>& list) : TList<T>(list) {
    pHead = new TNode<T>(-1, T());
    pHead->pNext = pFirst;
};

template <typename T>
THeadList<T>::~THeadList() {
    delete pHead;
    pHead = nullptr;
};

template <typename T>
void THeadList<T>::pushFront(int key, T val){
    TList<T>::pushFront(key, val);
    pHead->pNext = pFirst;
};

template <typename T>
void THeadList<T>::popFront(){
    TList<T>::popFront();
    pHead->pNext = pFirst;
};

template <typename T>
const THeadList<T>& THeadList<T>::operator=(const THeadList<T>& list) { // TODO: call List::operator=(list)
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
    return *this;
}

#endif