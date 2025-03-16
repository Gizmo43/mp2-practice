#pragma once
#ifndef HEAD_LIST_H
#define HEAD_LIST_H
#include "List.h"
template <typename T>
class THeadList :public TList<T>
{
protected:
    TNode<T>* pHead;
public:
    THeadList(){
        pHead = new TNode<T>(-1,T());
        pHead->pNext = pFirst;
        pPrev = pHead;
    };
    THeadList(const THeadList<T>& list) {
        pFirst = nullptr;
        pStop = nullptr;
        if (list.pFirst == pStop)
            return;
        pFirst = new TNode<T>{ *list.pFirst };
        TNode<T>* pNew = pFirst;
        while (pNew->pNext != pStop)
        {
            pNew->pNext = new TNode<T>{ *pNew->pNext };
            pNew = pNew->pNext;
        }
        pCurr = pFirst;
        pLast = list.pLast;
        pHead = new TNode<T>(-1, T());
        pHead->pNext = pFirst;
        if (pCurr == pFirst && pFirst != nullptr)
            pPrev = pHead;
    };
    ~THeadList(){
        delete pHead;
        pHead = nullptr;
    }

    void pushFront(int key, T val) {
        TNode<T>* newNode = new TNode<T>(key, val);
        if (pFirst == nullptr) {
            pFirst = newNode;
            pLast = pFirst;
            pCurr = pFirst;
            pHead->pNext = pFirst;
            pPrev = pHead;
            return;
        }
        newNode->pNext = pFirst;
        pFirst = newNode;
        pHead->pNext = pFirst;
        pCurr = pFirst;
    }
    void popFront() {
        pFirst = pFirst->pNext;
        pHead->pNext = pFirst;
    }
    const THeadList& operator=(const THeadList<T> &s) { //чекнуть потом
        if (this == &s)
            return *this;
        if (s.pFirst == nullptr) {
            pFirst = nullptr;
            return;
        }
        pFirst = nullptr;
        TNode<T>* tmp1 = s.pFirst;
        TNode<T>* tmp2 = pFirst;
        while (tmp1 != s.pStop) {
            TNode<T>* newNode = new TNode<T>(tmp1->Key, tmp1->Data);
            if (pFirst == nullptr) {
                pFirst = newNode;
            }
            else {
                tmp2->pNext = newNode;
            }
            tmp2 = newNode;
            tmp1 = tmp1->pNext;
        }
        pLast = tmp2;
        pHead = new TNode<T>(-1, T());
        pHead->pNext = pFirst;
        return *this;
    }


};





#endif