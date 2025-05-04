#include "Monom.h"




Monom::Monom() : coef(0), degree(0) {};
Monom::Monom(const std::string& monom) {
    int i = 0, x = 0, y = 0, z = 0;
    double coeff = 1.0;
    bool has_coeff = false;

    if (i < monom.length() && (monom[i] == '+' || monom[i] == '-')) {
        if (monom[i] == '-') 
            coeff = -1.0;
        i++;
    }


    string coeff_str;
    while (i < monom.length() && (isdigit(monom[i]) || monom[i] == '.')) {
        coeff_str += monom[i];
        has_coeff = true;
        i++;
    }

    if (!coeff_str.empty()) {
        coeff *= stod(coeff_str);
    }


    while (i < monom.length()) {
        char var = monom[i];
        if (var == 'x' || var == 'y' || var == 'z') {
            i++;
            int deg = 1;

            if (i < monom.length() && isdigit(monom[i])) {
                deg = 0;
                while (i < monom.length() && isdigit(monom[i])) {
                    deg = deg * 10 + (monom[i] - '0');
                    i++;
                }
            }

            switch (var) {
            case 'x': x = deg; break;
            case 'y': y = deg; break;
            case 'z': z = deg; break;
            }
        }
        else {
            i++;
        }
    }


    if (x > 9 || y > 9 || z > 9) {
        throw invalid_argument("wrong deg");
    }

    coef = coeff;
    degree = x * 100 + y * 10 + z;

};
Monom::Monom(int degree, double coef) :coef(coef), degree(degree) {};
string Monom::get_str() const { 
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
    if (degree + m.degree > 999) 
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

