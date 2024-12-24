#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;


enum STACK_IMPL
{
    ARRAY_STACK = 0,
    LIST_STACK = 1
};

class PosfixForm {
private:
    vector<string> expr;
    STACK_IMPL impl = ARRAY_STACK;
public:
    PosfixForm(const string&, STACK_IMPL impl1 = ARRAY_STACK);
    unordered_map<string, double> fill_variables();
    void config();
    double solve();
    bool is_op(string el);
    void print();
};