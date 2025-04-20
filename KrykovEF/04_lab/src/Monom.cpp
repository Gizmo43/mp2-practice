#include "Monom.h"




Monom::Monom() : coef(0), degree(0) {};
Monom::Monom(const std::string& monom) {
    int i = 0, x = 0, y = 0, z = 0;
    double coeff_sign = 1.0;
    if ((monom[i] == '+') || (monom[i] == '-')) {
        coeff_sign = 1.0;
        if (monom[i] == '-') {
            coeff_sign = -1.0;
        }
        i++;
    }

    //Коэффициент
    double coeff = 0.0;
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

    coef = coeff;
    degree = x * 100 + y * 10 + z;

};
Monom::Monom(int degree, double coef) :coef(coef), degree(degree) {};
string Monom::get_str() const { // get_str
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
double Monom::operator()(double x_val, double y_val, double z_val) const {
    int x = degree / 100;
    int y = (degree / 10) % 10;
    int z = degree % 10;
    double res = coef * pow(x_val, x) * pow(y_val, y) * pow(z_val, z);
    return res;
};
Monom Monom::operator+(const Monom& m) {
    if (degree != m.degree)
        throw exception("wrong degree");
    return Monom(degree, coef + m.coef);
}
Monom Monom::operator+=(const Monom& m) {
    if (degree != m.degree)
        throw exception("wrong degree");
    coef += m.coef;
    return *this;
}
Monom Monom::operator-(const Monom& m) {
    if (degree != m.degree)
        throw exception("wrong degree");
    return Monom(degree, coef - m.coef);
}
Monom Monom::operator*(const Monom& m) {
    if (degree + m.degree > 999) // TODO: error
        throw exception("wrong degree");
    return Monom(degree + m.degree, coef * m.coef);
}
Monom Monom::operator*(double m) {
    Monom res = Monom(degree, (coef * m));
    return res;
}
const Monom& Monom::operator=(const Monom& m) {
    degree = m.degree;
    coef = m.coef;
    return *this;
}
bool Monom::operator==(const Monom& m) const
{
    return ((coef == m.coef) && (degree == m.degree));
}
bool Monom::operator!=(const Monom& m) const
{
    return(!(operator==(m)));
}
bool Monom::operator>(const Monom& m) const
{
    return (degree > m.degree);
}
bool Monom::operator<(const Monom& m) const
{
    return (degree < m.degree);
}

