#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Monom { 
public:
	double coef;
	int degree;

	Monom();
    Monom(const string& str);
	Monom(int degree, double coef);
    string get_str() const;

    double operator()(double x_val, double y_val, double z_val) const;
    Monom operator+(const Monom& m);
    Monom operator+=(const Monom& m);
    Monom operator-(const Monom& m);
    Monom operator*(const Monom& m);
    Monom operator*(double m);
    
    const Monom& operator=(const Monom& m);
    
    bool operator==(const Monom& m) const;
    bool operator!=(const Monom& m) const;
    bool operator>(const Monom& m) const;
    bool operator<(const Monom& m) const;
};

#endif