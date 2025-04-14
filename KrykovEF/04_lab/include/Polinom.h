#ifndef POLINOM_H
#define POLINOM_H

#include "Monom.h"
#include "Ring_head_list.h"

using namespace std;

class Polinom {
protected:
	TRingHeadList<Monom> polinom_lst;
	string polinom_str;

    void orderPush(int key, double val);  
    string get_str() const;
public:
    Polinom();
    Polinom(const Polinom& p);
    Polinom(const std::string& source);

    double operator()(double x_val, double y_val, double z_val) const;
    string get_polinom_str() const;

    const Polinom& operator=(const Polinom& p);

    Polinom operator+(const Polinom& p);
    Polinom operator-(const Polinom& p);
    Polinom operator*(const Polinom& p);

    Polinom operator+(const Monom& p);
    Polinom operator-(const Monom& p);
    Polinom operator*(const Monom& p);

    Polinom operator-(double c);
    Polinom operator+(double c);
    Polinom operator*(double c);

    bool operator==(const Polinom& p) const;
    bool operator!=(const Polinom& p) const;

    friend std::ostream& operator<<(std::ostream&, Polinom&);
    friend std::istream& operator>>(std::istream&, Polinom&);

};




#endif