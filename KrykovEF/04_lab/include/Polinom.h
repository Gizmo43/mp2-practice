#pragma once
#ifndef POLINOM_H
#define POLINOM_H
#include "Monom.h"
#include "Ring_head_list.h"
#include <vector>
#include <algorithm>

using namespace std;

class Polinom {
protected:
	TRingHeadList<Monom> polinom_lst;
	string polinom_str;

    void orderPush(int key, double val) {
        Monom monom(key, val);
        if (polinom_lst.IsEmpty()) {
            polinom_lst.pushBack(key, monom);
            return;
        }
        TNode<Monom>* curr = polinom_lst.get_pFirst();
        TNode<Monom>* prev = nullptr;
        while (curr != polinom_lst.get_pStop() && curr->Key < key) {
            prev = curr;
            curr = curr->pNext;
        }
        if (curr != polinom_lst.get_pStop() && curr->Key == key) {
            curr->Data.coef += val;
        }
        else {
            if (prev == nullptr) {
                polinom_lst.pushFront(key, monom);
            }
            else {
                polinom_lst.InsertAfterKey(key, monom, prev->Key);
            }
        }
    }

    void parseMonom(const std::string& monom, double& coeff, int& x, int& y, int& z) {
        int i = 0;
        double coeff_sign = 1.0;
        if ((monom[i] == '+') || (monom[i] == '-')) {
            coeff_sign = 1.0;
            if (monom[i] == '-') {
                coeff_sign = -1.0;
            }
            i++;
        }

        //Коэффициент
        coeff = 0.0;
        string tmp;
        while ((i < monom.length()) && ((isdigit(monom[i])) || (monom[i] == '.'))) {// "." для дробных коэффициентов
            if (monom[i] == '.') {
                i++;
                double fr = 0.1;
                while ((i < monom.length()) && (isdigit(monom[i]))) {
                    tmp = monom[i];
                    coeff += (stod(tmp)) * fr;
                    fr *= 0.1;
                    i++;
                }
            }
            else {
                tmp = monom[i];
                coeff = coeff * 10 + (stod(tmp));
                i++;
            }
        }
        coeff *= coeff_sign;
        if (coeff == 0.0)
            coeff = 1.0 * coeff_sign;

        // Степени
        while (i < monom.length()) {
            char var = monom[i];
            if (var == 'x' || var == 'y' || var == 'z') {
                if (var == 'x') {
                    x = 1;
                }
                else if (var == 'y') {
                    y = 1;
                }
                else if (var == 'z') {
                    z = 1;
                }
                i++;
                int deg = 0;
                while ((i < monom.length()) && (isdigit(monom[i]))) {
                    tmp = monom[i];
                    deg = deg * 10 + (stod(tmp));
                    i++;
                }
                if (var == 'x') {
                    x = deg;
                }
                else if (var == 'y') {
                    y = deg;
                }
                else if (var == 'z') {
                    z = deg;
                }
            }
            else {
                i++;
            }
        }

        if ((x > 9) || (y > 9) || (z > 9)) {
            throw exception("wrong degree");
        }
    }


    //не актуально
    void sortPolinom() {
        vector<Monom> monoms;

        TNode<Monom>* curr = polinom_lst.get_pFirst();
        while (curr != polinom_lst.get_pStop()) {
            monoms.push_back(curr->Data); 
            curr = curr->pNext;
        }
        sort(begin(monoms), end(monoms));

        while (!polinom_lst.IsEmpty()) {
            polinom_lst.popFront();
        }

        for (int i = 0; i < monoms.size(); i++) {
            Monom current = monoms[i];
            polinom_lst.pushBack(current.degree, current);
        }
    }  //не актуально
    void simplify() {
        TRingHeadList<Monom> tmp;
        tmp = polinom_lst;
        TNode<Monom>* curr = tmp.get_pFirst();
        TNode<Monom>* prev = nullptr;
        prev = curr;
        curr = curr->pNext;
        while (curr != tmp.get_pStop())
        {
            if (prev->Key == curr->Key) {
                curr->Data = Monom(curr->Key, curr->Data.coef + prev->Data.coef);
                tmp.popKey(prev->Key);
            }
            prev = curr;
            curr = curr->pNext;
        }
        polinom_lst = tmp;
    } //не актуально


    string convertPolinom() const {
        string result;
        bool firstMonom = true; TRingHeadList<Monom> tmp;
        tmp = polinom_lst;
        TNode<Monom>* curr = tmp.get_pFirst();
        while (curr != tmp.get_pStop()) {
            Monom monom = curr->Data;

            if (monom.coef >= 0 && !firstMonom) {
                result += "+";
            }
            result += monom.convertMonom();
            firstMonom = false; 
            curr = curr->pNext;
        }
        return result;
    }
public:
	Polinom() {
		polinom_lst = TRingHeadList<Monom>();
	}
	Polinom(string source) {
        string str = source;
        //str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        string tmp;
        double coeff = 1.0;
        int x = 0, y = 0, z = 0, i = 0;

        for (i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (ch == '+' || ch == '-') {
                if (!tmp.empty()) {
                    parseMonom(tmp, coeff, x, y, z);
                    int degree = x * 100 + y * 10 + z;
                    orderPush(degree, coeff);
                    tmp.clear();
                    coeff = 1.0;
                    x = 0;
                    y = 0;
                    z = 0;
                }
            }
            tmp += ch;
        }
        if (!tmp.empty()) {
            parseMonom(tmp, coeff, x, y, z);
            int degree = x * 100 + y * 10 + z;
            orderPush(degree, coeff);
        }
        //sortPolinom();
        //simplify();
        polinom_str = convertPolinom();
	}

    double calculate_polinom(double x_val, double y_val, double z_val) const {
        TNode<Monom>* curr = polinom_lst.get_pFirst();
        double res = 0;
        while (curr != polinom_lst.get_pStop()){
            res += curr->Data.calculate_monom(x_val, y_val, z_val);
            curr = curr->pNext;
        }
        return res;
    }

    string get_polinom_str() const { return polinom_str; }

};




#endif