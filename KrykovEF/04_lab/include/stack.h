#ifndef STACK_H
#define STACK_H

#pragma once

#include <iostream>
#include <string>
using namespace std;



template <typename T>
class TStack {
public:
    void virtual push(const T& elem) = 0;
    void virtual pop() = 0;
    T virtual Top() = 0;
    bool virtual IsEmpty() = 0;
    bool virtual IsFull() = 0;
};







#endif