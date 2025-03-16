#pragma once
#ifndef RING_HEAD_LIST_H
#define RING_HEAD_LIST_H
#include "Head_list.h"

template <typename T>
class TRingHeadList : public THeadList<T> {
public:
	TRingHeadList(){
		pHead = new TNode<T>(-1, T());
		pHead->pNext = pFirst;
		pLast = pFirst;
		pCurr = pFirst;
		pStop = pHead;
		pPrev = pHead;
	}
	TRingHeadList(const THeadList<T>& list) {
        pFirst = nullptr;
        pStop = nullptr;
        if (list.pFirst == pStop)
            return;
        pFirst = new TNode<T>{ *list.pFirst };
        TNode<T>* pNew = pFirst;
        while (pNew->pNext != pStop)
        {
            pNew->pNext = new TNode<T>{ *pNew->pNext };
            pLast = pNew->pNext;
            pNew = pNew->pNext;
        }
        pCurr = pFirst;
        pHead = new TNode<T>(-1, T());
        pHead->pNext = pFirst;
        if (pCurr == pFirst && pFirst != nullptr)
            pPrev = pHead;
        if (pLast != nullptr)   
            pLast->pNext = pHead;
        

	}
    ~TRingHeadList() {}
    void pushFront(int key, T val) {
        TNode<T>* newNode = new TNode<T>(key, val);
        if (pFirst == nullptr) {
            pFirst = newNode;
            pLast = pFirst;
            pCurr = pFirst;
            pHead->pNext = pFirst;
            pPrev = pHead;
            pFirst->pNext = pHead;
            return;
        }
        pPrev = pHead;
        newNode->pNext = pFirst;
        pFirst = newNode;
        pHead->pNext = pFirst;
        pCurr = pFirst;
    }
    void pushBack(int key, T val) {
        TNode<T>* newNode = new TNode<T>(key, val);
        if (pFirst == nullptr) {
            pFirst = newNode;
            pLast = pFirst;
            pCurr = pFirst;
            pHead->pNext = pFirst;
            pPrev = pHead;
            pFirst->pNext = pHead;
            return;
        }
        pCurr = pFirst;
        while (pCurr->pNext != pStop) {
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        pCurr->pNext = newNode;
        pLast = pCurr->pNext;
        pLast->pNext = pHead;
        pPrev = pCurr;
        pCurr = pLast;
    }
    void popFront() {
        pFirst = pFirst->pNext;
        pHead->pNext = pFirst;
    }
    void popBack() {
        pCurr = pFirst;
        while (pCurr->pNext != pStop) {
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        pLast = pPrev;
        pLast->pNext = pHead;        
    }
    const TRingHeadList& operator=(const TRingHeadList<T> &s) { //чекнуть потом
        pHead = new TNode<T>(-1, T());
        pStop = pHead;
        if (this == &s)
            return *this;
        if (s.pFirst == nullptr) {
            pFirst = nullptr;
            return *this;
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
        pHead->pNext = pFirst;
        pLast->pNext = pHead;
        return *this;
    }
};

#endif