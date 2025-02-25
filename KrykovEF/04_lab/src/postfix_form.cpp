#include "postfix_form.h"

using namespace std;



PosfixForm::PosfixForm(const string& input, STACK_IMPL impl1) : impl(impl1) {
    string origin = input;

    string operand_name;
    for (int i = 0; i < origin.length(); i++) {
        string c;
        c.push_back(origin[i]);
        if (c == "(" || c == ")") {
            if (is_op(operand_name) && c == ")") {
                throw "wrong expr";
            }
            if ((!operand_name.empty())) {
                expr.push_back(operand_name);
                operand_name.clear();
            }
            expr.push_back(c);
            continue;
        }
        if (is_op(c)) {
            if (!operand_name.empty()) {
                expr.push_back(operand_name);
            }

            if (expr.empty()) {
                if (c != "-") {
                    throw "wrong expression";
                }
                operand_name += c;
                continue;
            }
            if (is_op(expr[expr.size() - 1])) {
                if (i == (origin.length() - 1)) {
                    throw "wrong expression";
                }
                if ('0' <= origin[i + 1] && origin[i + 1] <= '9') {
                    operand_name.clear();
                    operand_name += c;
                    continue;
                }
                else {
                    throw "wrong expression";
                }

            }
            expr.push_back(c);
            operand_name.clear();
            continue;
        }
        operand_name += c;
    }
    if (!operand_name.empty()) {
        expr.push_back(operand_name);
    }
    config();
}

bool PosfixForm::is_op(string el) {
    return el == "*" || el == "/" || el == "+" || el == "-";
}



int op_priority(string el) {
    if (el == "*" || el == "/") {
        return 3;
    }
    else if (el == "-" || el == "+") {
        return 2;
    }
    return 1;

}


double make_op(double a, double b, string op) {
    switch (op[0])
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default:
        break;
    }
}


unordered_map<string, double> PosfixForm::fill_variables() {
    unordered_map<string, double> values;
    for (string s : expr) {
        if (is_op(s) || s == "(" || s == ")") {
            continue;
        }
        if (values.find(s) == values.end()) {
            if (s[0] == '-' || '0' <= s[0] && s[0] <= '9') {
                values[s] = stoi(s);
                continue;
            }

            cout << "Variable: \n";
            cout << s << " = ";
            double val;
            cin >> val;
            values[s] = val;
        }
    }
    return values;
}


double PosfixForm::solve() {
    unordered_map<string, double> vals;
    vals = fill_variables();

    double answ = 0;

    TStack<double>* variables;
    if (impl == ARRAY_STACK) {
        variables = new TArrayStack<double>();
    }
    else {
        variables = new TListStack<double>();
    }

    for (string el : expr) {
        if (is_op(el)) {
            double b = variables->Top();
            variables->pop();
            if (variables->IsEmpty()) {
                variables->push(-b);
                continue;
            }
            double a = variables->Top();
            variables->pop();
            variables->push(make_op(a, b, el));
            continue;
        }
        variables->push(vals[el]);

    }
    answ = variables->Top();
    return answ;
}

double PosfixForm::solve(const unordered_map<string, double>& values) {
    unordered_map<string, double> vals;
    vals = values;

    double answ = 0;

    TStack<double>* variables;
    if (impl == ARRAY_STACK) {
        variables = new TArrayStack<double>();
    }
    else {
        variables = new TListStack<double>();
    }

    for (string el : expr) {
        if (is_op(el)) {
            double b = variables->Top();
            variables->pop();
            if (variables->IsEmpty()) {
                variables->push(-b);
                continue;
            }
            double a = variables->Top();
            variables->pop();
            variables->push(make_op(a, b, el));
            continue;
        }
        variables->push(vals[el]);

    }
    answ = variables->Top();
    return answ;
}



void PosfixForm::config() {
    TStack<string>* op;
    vector<string> pf;
    if (impl == ARRAY_STACK) {
        op = new TArrayStack<string>();
    }
    else {
        op = new TListStack<string>();
    }
    for (string el : expr) {
        if (!is_op(el) && el != "(" && el != ")") {
            pf.push_back(el);
            continue;
        }

        if (is_op(el)) {
            if (op->IsEmpty()) {
                op->push(el);
                continue;
            }
            else {


                while (!op->IsEmpty() && op_priority(el) <= op_priority(op->Top())) {
                    pf.push_back(op->Top());
                    op->pop();
                }
                op->push(el);
                continue;
            }
        }

        if (el == "(") {
            op->push(el);
            continue;
        }
        if (el == ")") {
            while (op->Top() != "(") {
                pf.push_back(op->Top());
                op->pop();
            }
            op->pop();
            continue;
        }

    }
    while (!op->IsEmpty()) {
        pf.push_back(op->Top());
        op->pop();
    }
    expr = pf;
}



string PosfixForm::return_expr() {
    string answ;
    for (string el : expr) answ += el;
    return answ;
}