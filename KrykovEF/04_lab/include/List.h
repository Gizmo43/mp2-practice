#ifndef LIST_H
#define LIST_H
#pragma once
#include <iostream>
#include <string>
#include "List.h"
using namespace std;


template <typename T>
struct TNode {
    int Key;
    T Data;
    TNode* pNext;
    TNode() : Key(0), pNext(nullptr), Data(T()) {};
    TNode(int new_key, T new_data) : Key(new_key), pNext(nullptr),Data(new_data) {};
    ~TNode() {};
};

template <typename T>
class TList
{
protected:
    TNode<T>* pFirst;
    TNode<T>* pCurr;
    TNode<T>* pPrev;
    TNode<T>* pLast;
    TNode<T>* pStop;
public:
    TList() : pFirst(nullptr), pCurr(nullptr), pPrev(nullptr), pLast(nullptr), pStop(nullptr) {};
    TList(const TList<T>& list);
    ~TList();


    TNode<T>* search_key(T s_key);
    TNode<T>* search_data(T s_data);

    virtual void pushFront(int key, T val);
    virtual void pushBack(int key, T val);

    void InsertAfterKey(int key, T val, int pKey);
    void InsertBeforeKey(int key, T val, int pKey);

    void popKey(int pKey);
    virtual void popFront();
    virtual void popBack();

    int size();

    void reset() { pCurr = pFirst; pPrev = nullptr; }
    void next() { pPrev = pCurr; pCurr = pCurr->pNext; }

    virtual const TList<T>& operator=(const TList<T>& s);
    bool operator==(const TList<T>& s) const;

    bool IsEmpty() { return (pFirst == nullptr);};
    bool IsFull() { return 0; };

    T get_first_key() const {return pFirst->Key;}
    T get_first_data() const {return pFirst->Data;}
    T get_last_key() const {return pLast->Key;}
    T get_last_data() const {return pLast->Data;}
    T get_curr_key() const { return pCurr->Key; }
    T get_curr_data() const { return pCurr->Data; }
    TNode<T>* get_pStop() const { return pStop; }
    TNode<T>* get_pFirst() const { return pFirst; }


};

template <typename T>
TList<T>::TList(const TList<T>& list) :  pCurr(nullptr), pPrev(nullptr), pLast(nullptr) {
    pFirst = nullptr;
    pStop = nullptr; 
    pPrev = nullptr;
    if(list.pFirst == nullptr)
        return;
    pFirst = new TNode<T>{ *list.pFirst };
    TNode<T>* pNew = pFirst;
    pCurr = pFirst;
    while (pNew->pNext != pStop){
        pPrev = pCurr;
        pNew->pNext = new TNode<T>{ *pNew->pNext };
        pNew = pNew->pNext;
        pCurr = pNew;
    }
    pLast = pCurr;
}

template <typename T>
TList<T>::~TList() {
    if (pFirst == nullptr)    
        return;    
    pCurr = pFirst;
    TNode<T>* tmp;
    while (pCurr != pStop)
    {
        tmp = pCurr->pNext;
        delete pCurr;
        pCurr = tmp;
    }
    delete pCurr;
    pCurr = nullptr;;
    pFirst = nullptr;
    pPrev = nullptr;
    pLast = nullptr;
    pStop = nullptr;
}

template <typename T>
TNode<T>* TList<T>::search_key(T s_key) {
    TNode<T>* curr = pFirst;
    while ((curr != pStop) && (curr->Key != s_key)) {
        curr = curr->pNext;
    }
    return curr;
}
template <typename T>
TNode<T>*  TList<T>::search_data(T s_data) {
    TNode<T>* curr = pFirst;
    while ((curr != pStop) && (curr->Data != s_data)) {
        curr = curr->pNext;
    }
    return curr;
}

template <typename T>
void TList<T>::pushFront(int key, T val) {
    TNode<T>* newNode = new TNode<T>(key, val);
    if (pFirst == nullptr) {
        pFirst = newNode;
        pLast = pFirst;
        pLast->pNext = pStop;
        pCurr = pFirst;
        pPrev = nullptr;
        return;
    }
    newNode->pNext = pFirst;
    pFirst = newNode;
    pCurr = pFirst;
    pPrev = nullptr;
}

template <typename T>
void TList<T>::pushBack(int key, T val) {
    TNode<T>* newNode = new TNode<T>(key, val);
    if (pFirst == nullptr) {
        pFirst = newNode;
        pLast = pFirst;
        pLast->pNext = pStop;
        pCurr = pFirst;
        pPrev = nullptr;
        return;
    }
    pLast->pNext = newNode;
    pPrev = pLast;
    pLast = newNode;
    pCurr = pLast;
    pLast->pNext = pStop;
}

template <typename T>
void TList<T>::InsertAfterKey(int key, T val, int pKey) {
    TNode<T>* curr = pFirst;
    while ((curr != pStop) && (curr->Key != pKey)){
        curr = curr->pNext;
    }
    if (curr->Key != pKey)
        throw exception("no such key");
    if (curr == pLast){
        pushBack(key, val);
        return;
    }
    TNode<T>* newNode = new TNode<T>(key, val);
    TNode<T>* tmp = curr->pNext;
    curr->pNext = newNode;
    newNode->pNext = tmp;
}
template <typename T>
void TList<T>::InsertBeforeKey(int key, T val, int pKey) {
    TNode<T>* curr = pFirst;
    TNode<T>* prev = nullptr;
    while ((curr != pStop) && (curr->Key != pKey)) {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr->Key != pKey)
        throw exception("no such key");
    if (curr == pFirst) {
        pushFront(key, val);
        return;
    }
    TNode<T>* newNode = new TNode<T>(key, val);
    prev->pNext = newNode;
    newNode->pNext = curr;
}

template <typename T>
void TList<T>::popKey(int pKey){
    if (IsEmpty())
        throw exception("list empty");
    TNode<T>* curr = pFirst;
    TNode<T>* prev = nullptr;
    TNode<T>* tmp;
    while ((curr != pStop) && (curr->Key != pKey)) {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr->Key != pKey)
        throw exception("no such key");
    if (curr == pFirst) {
        popFront();
        return;
    }
    if (curr == pLast) {
        delete curr;
        prev->pNext = pStop;
        pLast = prev;
        return;
    }
    prev->pNext = curr->pNext;
    delete curr;
    curr = nullptr;
}

template <typename T>
void TList<T>::popFront() {
    if (IsEmpty())
        throw exception("list empty");
    TNode<T>* tmp = pFirst->pNext;
    if (pFirst->pNext == pStop){
        pLast = nullptr;
        pPrev = nullptr;
        pCurr = nullptr;
        tmp = nullptr;
    }
    delete pFirst;
    pFirst = tmp;
}

template <typename T>
void TList<T>::popBack() {
    if (IsEmpty())
        throw exception("list empty");

    TNode<T>* tmp;
    if (pFirst->pNext == pStop){
        popFront();
        return;
    }
    TNode<T>* curr = pFirst;
    TNode<T>* prev = nullptr;
    while (curr != pLast) {
        prev = curr;
        curr = curr->pNext;
    }
    delete curr;
    prev->pNext = pStop;
    pLast = prev;
}

template <typename T>
int TList<T>::size() {
    TNode<T>* curr = pFirst;
    int size = 0;
    while (curr != pStop) {
        size++;
        curr = curr->pNext;
    }
    return size;
}

template <typename T>
bool TList<T>::operator==(const TList<T>& list) const {
    TNode<T>* curr1 = pFirst;
    TNode<T>* curr2 = list.pFirst;
    while ((curr1 != pStop) || (curr2 != list.pStop)) {
        if ((curr1->Data != curr2->Data) || (curr1->Key != curr2->Key))
            return 0;
        curr1 = curr1->pNext;
        curr2 = curr2->pNext;
    }
    if (((curr1 == pStop) && (curr2 != list.pStop)) || ((curr1 != pStop) && (curr2 == list.pStop)))
        return 0;
    return 1;
};
template <typename T>
const TList<T>& TList<T>::operator=(const TList<T>& list) {
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