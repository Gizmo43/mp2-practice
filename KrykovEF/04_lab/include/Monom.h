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
};


#endif