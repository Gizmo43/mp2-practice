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
    bool IsFull() { return (top == maxSize-1); };
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


template <typename T>
struct TNode{
    T Key;
    TNode* pNext;
    TNode() : Key(0), pNext(nullptr) {};
    TNode(T new_key) : Key(new_key), pNext(nullptr) {};
    ~TNode() {};
};

template <typename T>
class TList
{
private:
    TNode<T>* pFirst;
public:
    TList() : pFirst(nullptr) {};
    TList(const TList<T>& list) {
        pFirst = nullptr;
        if (list.pFirst == nullptr)
            return;
        pFirst = new TNode<T>{ *list.pFirst };
        TNode<T>* pNew = pFirst;
        while (pNew->pNext != nullptr)
        {
            pNew->pNext = new TNode<T>{ *pNew->pNext };
            pNew = pNew->pNext;
        }
    };
    ~TList() {
        while (pFirst != nullptr) {
            TNode<T>* tmp = pFirst;
            pFirst = pFirst->pNext;
            delete tmp;
        }
    };
    TNode<T>* search(T s_key) {
        TNode<T>* tmp = pFirst;
        while ((tmp != nullptr) && (tmp->Key != s_key)) {
            tmp = tmp->pNext;
        }
        return tmp;
    };

    void pushFront(TNode<T>* newNode) {
        if (pFirst == nullptr) {
            pFirst = newNode;
            return;
        }
        newNode->pNext = pFirst;
        pFirst = newNode;
    };

    void pushBack(TNode<T>* newNode) {
        if (newNode == nullptr)
            throw "nullptr push";

        TNode<T>* curr = pFirst;
        while (curr->pNext != nullptr) {
            curr = curr->pNext;
        }
        curr->pNext = newNode;
    };

    void InsertAfter(TNode<T>* newNode, T pKey) {
        TNode<T>* curr = search(pKey);
        if (curr == nullptr)
            throw "no element";

        newNode->pNext = curr->pNext;
        curr->pNext = newNode;

    };

    void InsertBefore(TNode<T>* newNode, T pKey) {
        TNode<T>* prev = nullptr, * curr = pFirst;
        while ((curr != nullptr) && (curr->Key != pKey)) {
            prew = curr;
            curr = curr->pNext;
        }
        if (curr == nullptr)
            throw "no element";

        if (prev == nullptr) {
            pushFront(newNode);
            return;
        }
        newNode->pNext = curr;
        prev->pNext = newNode;
    };

    void remove(T pKey) {
        TNode<T>* prev = nullptr, * curr = pFirst;
        while ((curr != nullptr) && (curr->Key != pKey)) {
            prev = curr;
            curr = curr->pNext;
        }
        if (curr == nullptr)
            throw "no element";
        if (prev == nullptr) {
            pFirst = pFirst->pNext;
            delete curr;
        }
        prev->pNext = curr->pNext;
        delete curr;
    };

    void remove_first() {
        pFirst = pFirst->pNext;
    };

    int size() {
        TNode<T>* curr = pFirst;
        int size = 0;
        while (curr != nullptr) {
            size++;
            curr = curr->pNext;
        }
        return size;
    };

    void reset(TNode<T>* curr) {
        curr = pFirst;
    }
    void next(TNode<T>* curr) {
        curr = curr->pNext;
    }

    const TList<T>& operator=(const TList<T>& s) {
        if (this == &s)
            return *this;
        if (s.pFirst == nullptr)
            pFirst = nullptr;
        pFirst = nullptr;
        TNode<T>* tmp1 = s.pFirst;
        TNode<T>* tmp2 = nullptr;
        while (tmp1 != nullptr) {
            TNode<T>* newNode = new TNode<T>(tmp1->Key);
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
        while (curr1 != nullptr) {
            if (curr1->Key != curr2->Key)
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
    
};


template <typename T>
class TListStack : public TStack<T> {
private:
    TList<T> stack;
public:
    TListStack(){};

    TListStack(const TListStack& s) :stack(s.stack) {};
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
    bool IsEmpty() {return (stack.IsEmpty());};
    bool IsFull() { return 0;};

    const TListStack<T>& operator=(const TListStack<T>& s)
    {
        stack = s.stack;
        return *this;
    }
    bool operator==(const TListStack<T>& s)
    {
        return (stack == s.stack);
    }


    //add to git
};




