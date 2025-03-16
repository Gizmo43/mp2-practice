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
    TList(const TList<T>& list) {
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
    };
    ~TList() {
        if (pFirst == nullptr) {
            return;
        }
        pPrev = pFirst;
        pCurr = pPrev->pNext;
        while (pCurr != pStop) {
            delete pPrev;
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        delete pPrev;
        pFirst = nullptr;
        pCurr = nullptr;
        pPrev = nullptr;
        pLast = nullptr;
    };
    TNode<T>* search_key(T s_key) {
        pCurr = pFirst;
        while ((pCurr != pStop) && (pCurr->Key != s_key)) {
            pCurr = pCurr->pNext;
        }
        return pCurr;
    };
    TNode<T>* search_data(T s_data) {
        pCurr = pFirst;
        while ((pCurr != pStop) && (tmp->Data != s_data)) {
            pCurr = pCurr->pNext;
        }
        return pCurr;
    };

    void pushFront(TNode<T>* newNode) {
        if (pFirst == nullptr) {
            pFirst = newNode;
            pLast = pFirst;
            pCurr = pFirst;
            return;
        }
        newNode->pNext = pFirst;
        pFirst = newNode;
    };

    void pushBack(TNode<T>* newNode) {
        if (newNode == nullptr)
            throw "nullptr push";

        pCurr = pFirst;
        while (pCurr->pNext != pStop) {
            pCurr = pCurr->pNext;
        }
        pCurr->pNext = newNode;
        pLast = newNode;
    };

    void InsertAfterKey(TNode<T>* newNode, T pKey) {
        pCurr = search_key(pKey);
        if (pCurr == nullptr)
            throw "no element";

        newNode->pNext = pCurr->pNext;
        pCurr->pNext = newNode;
        if (newNode->pNext = pStop)
            pLast = newNode;

    };

    void InsertBeforeKey(TNode<T>* newNode, T pKey) {
        pPrev = nullptr, pCurr = pFirst;
        while ((pCurr != pStop) && (pCurr->Key != pKey)) {
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        if (pCurr == nullptr)
            throw "no element";

        if (pPrev == nullptr) {
            pushFront(newNode);
            return;
        }
        newNode->pNext = pCurr;
        pPrev->pNext = newNode;
    };

    void removeKey(T pKey) {
        pPrev = nullptr, pCurr = pFirst;
        while ((pPrev != pStop) && (pCurr->Key != pKey)) {
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        if (pCurr == nullptr)
            throw "no element";
        if (pPrev == nullptr) {
            pFirst = pFirst->pNext;
            delete pCurr;
        }
        pPrev->pNext = pCurr->pNext;
        delete pPrev;
    };

    void remove_first() {
        pFirst = pFirst->pNext;
    };

    int size() {
        pCurr = pFirst;
        int size = 0;
        while (pCurr != pStop) {
            size++;
            pCurr = pCurr->pNext;
        }
        return size;
    };

    void reset() {
        pCurr = pFirst;
    }
    void next() {
        pCurr = pCurr->pNext;
    }

    const TList<T>& operator=(const TList<T>& s) {
        if (this == &s)
            return *this;
        if (s.pFirst == nullptr)
            pFirst = nullptr;
        pFirst = nullptr;
        TNode<T>* tmp1 = s.pFirst;
        TNode<T>* tmp2 = nullptr;
        while (tmp1 != pStop) {
            TNode<T>* newNode = new TNode<T>(tmp1->Key,tmp1->Data);
            if (pFirst == nullptr) {
                pFirst = newNode;
            }
            else {
                tmp2->pNext = newNode;
            }
            tmp2 = newNode;
            tmp1 = tmp1->pNext;
        }

        return *this;
    };

    bool operator==(const TList<T>& s) {
        TNode<T>* curr1 = pFirst;
        TNode<T>* curr2 = s.pFirst;
        while (curr1 != pStop) {
            if ((curr1->Data != curr2->Data)|| (curr1->Key != curr2->Key))
                return 0;
            curr1 = curr1->pNext;
            curr2 = curr2->pNext;
        }
        return 1;
    };

    bool IsEmpty() {
        if (pFirst == nullptr)
            return 1;
        return 0;
    };
    bool IsFull() { return 0; };

    T get_first_key() const {
        return pFirst->Key;
    }

    T get_first_data() const {
        return pFirst->Data;
    }
    T get_last_key() const {
        return pLast->Key;
    }

    T get_last_data() const {
        return pLast->Data;
    }

};

#endif