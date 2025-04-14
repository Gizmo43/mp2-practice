#include "Polinom.h"

void Polinom::orderPush(int key, double val) {
    Monom monom(key, val);
    if (polinom_lst.IsEmpty()) {
        polinom_lst.pushBack(key, monom);
        return;
    }
    polinom_lst.reset();
    while (!(polinom_lst.isEnded()) && polinom_lst.get_pCurr()->Key < key) {
        polinom_lst.next();
    }
    if (!(polinom_lst.isEnded()) && polinom_lst.get_pCurr()->Key == key) {
        polinom_lst.get_pCurr()->Data.coef += val;

        if (polinom_lst.get_pCurr()->Data.coef == 0.0) {
            if (polinom_lst.get_pPrev() == nullptr) { // TODO: pPrev
                polinom_lst.popFront();
            }
            else {
                polinom_lst.popKey(key);
            }
        }
    }
    else {
        if (polinom_lst.get_pPrev() == nullptr) { // TODO: pPrev
            polinom_lst.pushFront(key, monom);
        }
        else {
            polinom_lst.InsertAfterKey(key, monom, polinom_lst.get_pPrev()->Key);
        }
    }
    polinom_str = get_str();
}



string Polinom::get_str() const { // get_str
    string result;
    bool firstMonom = true; TRingHeadList<Monom> tmp;
    tmp = polinom_lst;
    tmp.reset();
    while (!(tmp.isEnded())) {
        Monom monom = tmp.get_pCurr()->Data;
        if (monom.coef >= 0 && !firstMonom) {
            result += "+";
        }
        result += monom.get_str();
        firstMonom = false;
        tmp.next();
    }
    return result;
}

Polinom::Polinom() {
    polinom_lst = TRingHeadList<Monom>();
}

Polinom::Polinom(const Polinom& p) {
    polinom_str = p.polinom_str;
    polinom_lst = p.polinom_lst;
}
Polinom::Polinom(const std::string& source) {
    string str = source;
    //str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    int i = 0;
    string tmp;

    for (i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch == '+' || ch == '-') {
            if (!tmp.empty()) {
                Monom tmp_mn(tmp);
                orderPush(tmp_mn.degree, tmp_mn.coef);
                tmp.clear();
            }
        }
        tmp += ch;
    }
    if (!tmp.empty()) {
        Monom tmp_mn(tmp);
        orderPush(tmp_mn.degree, tmp_mn.coef);
    }
    polinom_str = get_str();
}

double Polinom::operator()(double x_val, double y_val, double z_val) const {
    TRingHeadList<Monom> tmp;
    tmp = polinom_lst;
    tmp.reset();
    double res = 0;
    while (!(tmp.isEnded())) {
        Monom monom = tmp.get_pCurr()->Data;
        res += monom(x_val, y_val, z_val);
        tmp.next();
    }
    return res;
}

string Polinom::get_polinom_str() const { return polinom_str; }

const Polinom& Polinom::operator=(const Polinom& p) {
    if (this != &p) return *this;
    polinom_lst = p.polinom_lst;
    polinom_str = p.polinom_str;
    return *this;
}


Polinom Polinom::operator+(const Monom& m) {
    if (m.coef == 0) {
        return *this;
    }
    Polinom tmp(*this);
    tmp.orderPush(m.degree,m.coef);
    return tmp;
}


Polinom Polinom::operator-(const Monom& m) {
    if (m.coef == 0) {
        return *this;
    }
    Polinom tmp(*this);
    tmp.orderPush(m.degree, ((-1.0) * m.coef));
    return tmp;
}


Polinom Polinom::operator*(const Monom& m) { // ? monom с нулевым коэффициентом
    polinom_lst.reset();
    Polinom tmp;
    Monom mon;
    while (!(polinom_lst.isEnded())) {
        mon = polinom_lst.get_pCurr()->Data * m;
        tmp.polinom_lst.pushBack(mon.degree, mon);
        polinom_lst.next();
    }
    return tmp;
}


Polinom Polinom::operator+(double c)
{
    return *this + Monom(0, c);
}


Polinom Polinom::operator-(double c)
{
    return Polinom::operator+((-1.0) * c);
}


Polinom Polinom::operator*(double c)
{
    polinom_lst.reset();
    Polinom tmp;
    Monom mon = polinom_lst.get_pCurr()->Data;
    while (!(polinom_lst.isEnded())) {
        mon = mon * c;
        tmp.polinom_lst.pushBack(mon.degree, mon);
        polinom_lst.next();
        mon = polinom_lst.get_pCurr()->Data;
    }
    return tmp;
}



Polinom Polinom::operator+(const Polinom& p1)
{
    Polinom p = p1;

    polinom_lst.reset();
    p.polinom_lst.reset();
    Polinom answ;
    while (!(polinom_lst.isEnded()) && !(p.polinom_lst.isEnded())) { // TODO: слияние упорядоченных списков с проверкой, что степени совпали у мономов
        answ.orderPush(polinom_lst.get_pCurr()->Key, polinom_lst.get_pCurr()->Data.coef);
        answ.orderPush(p.polinom_lst.get_pCurr()->Key, p.polinom_lst.get_pCurr()->Data.coef);
        polinom_lst.next();
        p.polinom_lst.next();
    }
    while (!(polinom_lst.isEnded()))
    {
        answ.orderPush(polinom_lst.get_pCurr()->Key, polinom_lst.get_pCurr()->Data.coef);
        polinom_lst.next();
    }
    while (!(p.polinom_lst.isEnded()))
    {
        answ.orderPush(p.polinom_lst.get_pCurr()->Key, p.polinom_lst.get_pCurr()->Data.coef);
        p.polinom_lst.next();
    }

    answ.polinom_str = answ.get_str();
    return answ;

}


Polinom Polinom::operator-(const Polinom& p)
{
    if (*this == p) {
        return Polinom();
    }
    Polinom tmp = p;
    tmp = tmp * (-1.0);
    tmp.polinom_str = tmp.get_str();
    return Polinom::operator+(tmp);
}




Polinom Polinom::operator*(const Polinom& p1)
{
    Polinom p = p1;
    polinom_lst.reset();
    p.polinom_lst.reset();

    Polinom answ;
    while (!(polinom_lst.isEnded())) {
        while (!(p.polinom_lst.isEnded())) {
            Monom mon = polinom_lst.get_pCurr()->Data * p.polinom_lst.get_pCurr()->Data;
            answ.orderPush(mon.degree, mon.coef);
            p.polinom_lst.next();
        }
        polinom_lst.next();
        p.polinom_lst.next();
    }
    answ.polinom_str = answ.get_str();

    return answ;
}





bool Polinom::operator==(const Polinom& p) const {
    return this->polinom_lst == p.polinom_lst;
}

bool Polinom::operator!=(const Polinom& p) const {
    return !(Polinom::operator==(p));
}




ostream& operator<<(std::ostream& out, Polinom& p) {
    out << p.polinom_str << "\n";
    return out;
}

istream& operator>>(std::istream& in, Polinom& p) {
    string strPolinom;
    getline(in, strPolinom);
    p = Polinom(strPolinom);
    return in;
}


