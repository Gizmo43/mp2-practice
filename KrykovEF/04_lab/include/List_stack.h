#pragma once
#ifndef LIST_STACK_H
#define LIST_STACK_H
#include "stack.h"
#include "List.h"
using namespace std;

template <typename T>
class TListStack : public TStack<T> {
private:
    TList<T> stack;
public:
    TListStack() {};

    TListStack(const TListStack<T>& s) :stack(s.stack) {};
    ~TListStack() {};

    void push(const T& elem) {
        TNode<T>* newNode = new TNode<T>(elem);
        this->stack.pushFront(newNode);
    };
    void pop() {
        if (IsEmpty())
            throw "stack is empty";
        stack.remove_first();
    };
    T Top() {
        if (IsEmpty())
            throw "stack is empty";
        return stack.get_first_key();

    };
    bool IsEmpty() { return (stack.IsEmpty()); };
    bool IsFull() { return 0; };

    const TListStack<T>& operator=(const TListStack<T>& s)
    {
        stack = s.stack;
        return *this;
    }
    bool operator==(const TListStack<T>& s)
    {
        return (stack == s.stack);
    }
};

#endif