#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Monom { // TODO: split .h + .cpp
public:
	double coef;
	int degree;
	Monom() : coef(0), degree(0) {};
    Monom(const std::string& str);
	Monom(int degree, double coef) :coef(coef), degree(degree) {};
    string convertMonom() const{ // get_str
        string result;
        if (coef != 1 && coef != -1) {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%.2f", coef);
            result += buffer;
        }
        else if (coef == -1) {
            result += "-";
        }

        int x = degree / 100;
        int y = (degree / 10) % 10;
        int z = degree % 10;

        if (x > 0) {
            result += "x";
            if (x > 0) {
                result += to_string(x);
            }
        }
        if (y > 0) {
            result += "y";
            if (y > 0) {
                result += to_string(y);
            }
        }
        if (z > 0) {
            result += "z";
            if (z > 0) {
                result += to_string(z);
            }
        }


        if (x == 0 && y == 0 && z == 0 && coef == 1) {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%.2f", coef);
            result += buffer;
        }
        return result;
    }
    double operator()(double x_val, double y_val, double z_val) const {
        int x = degree / 100;
        int y = (degree / 10) % 10;
        int z = degree % 10;
        double res = coef * pow(x_val,x) * pow(y_val, y) * pow(z_val, z);
        return res;
    };
    Monom operator+(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        return Monom(degree, coef + m.coef);
    }
    Monom operator+=(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        coef += m.coef;
        return *this;
    }
    Monom operator-(const Monom& m) {
        if (degree != m.degree)
            throw exception("wrong degree");
        return Monom(degree, coef - m.coef);
    }
    Monom operator*(const Monom& m) {
        if (degree != m.degree) // TODO: error
            throw exception("wrong degree");
        return Monom(degree * 2, coef * m.coef);
    }
    Monom operator*(double m) {
        return Monom(degree, coef * m);
    }
    const Monom& operator=(const Monom& m) {
        return Monom(m.degree, m.coef);
    }
    bool operator==(const Monom& m) const
    {
        return ((coef == m.coef) && (degree == m.degree));
    }
    bool operator!=(const Monom& m) const
    {
        return(!(operator==(m)));
    }
    bool operator>(const Monom& m) const
    {
        return (degree > m.degree);
    }
    bool operator<(const Monom& m) const
    {
        return (degree < m.degree);
    }

};

#endif