#ifndef LIST_H
#define LIST_H

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
    TNode(int new_key, T new_data, TNode<T>* next) : Key(new_key), pNext(next), Data(new_data) {};
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
    TList() : pFirst(nullptr), pCurr(nullptr), pPrev(nullptr),
        pLast(nullptr), pStop(nullptr) {};
    TList(const TList<T>& list);
    virtual ~TList();

    virtual void clearList();


    TNode<T>* search_key(int s_key);

    virtual void pushFront(int key, T val);
    virtual void pushBack(int key, T val);

    void InsertAfterKey(int key, T val, int pKey);
    void InsertBeforeKey(int key, T val, int pKey);

    void popKey(int pKey);
    virtual void popFront();
    virtual void popBack();

    int size() const;

    void reset() { pCurr = pFirst; pPrev = nullptr; }
    virtual void next();

    virtual const TList<T>& operator=(const TList<T>& s);
    bool operator==(const TList<T>& s) const;

    bool IsEmpty() const { return (pFirst == nullptr);};
    bool IsFull() const { return 0; };
    bool isEnded() const { return (pCurr == pStop); };

    TNode<T>* get_pFirst() const { return pFirst; }
    TNode<T>* get_pCurr() const { return pCurr; }
};

template <typename T>
TList<T>::TList(const TList<T>& list) :  pCurr(nullptr), pPrev(nullptr),
        pLast(nullptr) {
    pFirst = nullptr;
    pStop = list.pStop; 
    pPrev = nullptr;
    if(list.pFirst == nullptr)
        return;
    pFirst = new TNode<T>(*list.pFirst);
    TNode<T>* pNew = pFirst;
    pCurr = pFirst;
    while (pNew->pNext != pStop){
        pPrev = pCurr;
        pNew->pNext = new TNode<T>(*pNew->pNext);
        pNew = pNew->pNext;
        pCurr = pNew;
    }
    pLast = pCurr;
}

template <typename T>
TList<T>::~TList() {
    clearList();
}

template <typename T>
TNode<T>* TList<T>::search_key(int s_key) {
    if (IsEmpty())
        return nullptr;
    reset();
    while (pCurr != pStop){
        if (pCurr->Key == s_key)
            return pCurr;
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }
    return nullptr;
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
    if (pFirst == nullptr) {
        pushFront(key, val);
        return;
    }
    TNode<T>* newNode = new TNode<T>(key, val);
    pLast->pNext = newNode;
    pPrev = pLast;
    pLast = newNode;
    pCurr = pLast;
    pLast->pNext = pStop;
}

template <typename T>
void TList<T>::InsertAfterKey(int key, T val, int pKey) {
    if (search_key(pKey) == nullptr)
        throw exception("no such key");
    if (pCurr == pLast){
        pushBack(key, val);
        return;
    }
    TNode<T>* newNode = new TNode<T>(key, val, pCurr->pNext);
    pCurr->pNext = newNode;
}

template <typename T>
void TList<T>::InsertBeforeKey(int key, T val, int pKey) {
    if (search_key(pKey) == nullptr)
        throw exception("no such key");
    if (pCurr == pFirst) {
        pushFront(key, val);
        return;
    }
    TNode<T>* newNode = new TNode<T>(key, val);
    pPrev->pNext = newNode;
    newNode->pNext = pCurr;
}

template <typename T>
void TList<T>::popKey(int pKey){
    if (IsEmpty())
        throw exception("list empty");
    TNode<T>* tmp;
    if (search_key(pKey) == nullptr)
        throw exception("no such key");
    if (pCurr == pFirst) {
        popFront();
        return;
    }
    if (pCurr == pLast) {
        delete pCurr;
        pPrev->pNext = pStop;
        pLast = pPrev;
        return;
    }
    pPrev->pNext = pCurr->pNext;
    delete pCurr;
    pCurr = nullptr;
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
    if (pFirst->pNext == pStop){
        popFront();
        return;
    }
    while (pCurr != pLast) {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }
    delete pCurr;
    pPrev->pNext = pStop;
    pCurr = pPrev;
    pLast = pPrev;
}

template <typename T>
int TList<T>::size() const {
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
    if (list.pFirst == nullptr)    {
        return TList<T>();
    }
    if (this != &list){
        this->clearList();
        pFirst = new TNode<T>(*list.pFirst);
        TNode<T>* pNew = pFirst;
        while (pNew->pNext != list.pStop)
        {
            pNew->pNext = new TNode<T>(*pNew->pNext);
            pNew = pNew->pNext;
        }
        pLast = pNew;
        pLast->pNext = pStop;
    }
    return *this;
}



template <typename T>
void TList<T>::clearList()
{
    if (pFirst == nullptr){
        return;
    }
    pCurr = pFirst;
    TNode<T>* tmp;
    while (pCurr->pNext != pStop){
        tmp = pCurr->pNext;
        delete pCurr;
        pCurr = tmp;
    }
    tmp = pCurr->pNext;
    delete pCurr;
    pCurr = nullptr;;
    pFirst = nullptr;
    pPrev = nullptr;
    pLast = nullptr;
    pStop = nullptr;
}

template <typename T>
void TList<T>::next() {
    if (pCurr == pStop){
        reset();
    }
    pPrev = pCurr;
    pCurr = pCurr->pNext;
}

#endif