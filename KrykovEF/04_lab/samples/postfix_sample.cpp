#include "postfix_form.h"

int main()
{
    char stack_type = '2';
    while (stack_type != '0' && stack_type != '1') {
        cout << "Stack type(0 - ArrayStack   1 - ListStack):\n";
        cin >> stack_type;
    }


    string s;
    cin >> s;

    STACK_IMPL stack_impl;
    switch (stack_type)
    {
    case '0': 
        stack_impl = ARRAY_STACK;
        break;
    case '1':
        stack_impl = LIST_STACK;
        break;
    }
    PosfixForm expr(s, stack_impl);
    cout << "\nPostfix form:\n";
    cout << expr.return_expr() << " ";
    cout << '\n';
    double Res = expr.solve();
    cout << Res;


    return 0;
}
