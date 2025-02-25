#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#include "stack.h"
#pragma once
using namespace std;

template <typename T>
class TArrayStack : public TStack<T> {
private:
    int maxSize;
    int top;
    T* arr;
public:
    TArrayStack(int sz = 10) : top(-1) {
        if (sz <= 0)
            throw "negative size";
        maxSize = sz;
        arr = new T[maxSize];
    };
    TArrayStack(const TArrayStack<T>& s) {
        top = s.top;
        maxSize = s.maxSize;
        arr = new T[maxSize];
        for (int i = 0; i < maxSize; i++) {
            arr[i] = s.arr[i];
        }
    };
    ~TArrayStack() {
        delete[] arr;
    }
    void push(const T& elem) {
        if (IsFull()) {
            T* tmp = arr;
            arr = new T[(maxSize + 1) * 3];
            std::copy(tmp, tmp + maxSize, arr);
            maxSize = (maxSize + 1) * 3;
        }
        top++;
        arr[top] = elem;
    };
    void pop() {
        if (IsEmpty())
            throw "stack is empty";
        top--;
    };
    T Top() {
        if (IsEmpty())
            throw "stack is empty";
        return arr[top];
    };
    bool IsEmpty() { return (top == -1); };
    bool IsFull() { return (top == maxSize - 1); };
    int size() { return maxSize; };


    const TArrayStack<T>& operator=(const TArrayStack<T>& s) {
        if (this == &s)
            return *this;
        if (maxSize != s.maxSize) {
            delete[] arr;
            maxSize = s.maxSize;
            arr = new T[maxSize];
        }
        top = s.top;
        for (int i = 0; i <= top; i++) {
            arr[i] = s.arr[i];
        }
        return *this;
    };

    bool operator==(const TArrayStack<T>& s) const {
        if (maxSize != s.maxSize || top != s.top) {
            return 0;
        }
        for (int i = 0; i < maxSize; i++) {
            if (arr[i] != s.arr[i]) {
                return 0;
            }
        }
        return 1;
    };

    bool operator!=(const TArrayStack<T>& s) const {
        return !((*this) == s);
    };
};






#endif
