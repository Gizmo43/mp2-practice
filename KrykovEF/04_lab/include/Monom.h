#ifndef MONOM_H
#define MONOM_H
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Monom {
public:
	double coef;
	int degree;
	Monom() : coef(0), degree(0) {};
	Monom(double coef, int degree) :coef(coef), degree(degree) {};
    Monom operator+(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        return Monom(coef + m.coef, degree);
    }
    Monom operator-(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        return Monom(coef - m.coef, degree);
    }
    Monom operator*(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        return Monom(coef * m.coef, degree * 2);
    }
    Monom operator*(double m) {
        return Monom(coef * m, degree);
    }
    const Monom& operator=(const Monom& m) {
        return Monom(m.coef, m.degree);
    }
    bool operator==(const Monom& m) const
    {
        return ((coef == m.coef) && (degree == m.degree));
    }
    bool operator!=(const Monom& m) const
    {
        return(!(operator==(m)));
    }
};



#endif