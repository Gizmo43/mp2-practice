﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be lesser than MAX");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
      {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept //для матрицы
  {
      v.sz = 0;
      this->pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz){
          delete[]this->pMem;
          this->sz = v.sz;
          this->pMem = new T[v.sz];
      }
      for (int i = 0; i < sz; i++)
          this->pMem[i] = v.pMem[i];                                             
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          this->sz = v.sz;
          v.sz = 0;
          this->pMem = v.pMem;
          v.pMem = nullptr;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return (pMem[ind]);
  }
  const T& operator[](size_t ind) const
  {
      return (pMem[ind]);
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind<0 || ind>sz - 1)
          throw std::exception("Incorrect index");
      return(this->pMem[ind]);
  }
  const T& at(size_t ind) const
  {
      if (ind<0 || ind>sz - 1)
          throw std::exception("Incorrect index");
      return(this->pMem[ind]);
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)//needs check!
          return 0;
      for (int i = 0; i < v.sz; i++)
          if (this->pMem[i] != v.pMem[i])
              return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)  //need fix, add tmp
  {
      //TDynamicVector<T> tmp(size());
      for (int i = 0; i < size(); i++) {
          pMem[i] = pMem[i] + val;
      }
      //cout << tmp.size();
      return *this;

  }
  TDynamicVector operator-(T val)
  {
      //TDynamicVector<T> tmp(size());
      for (int i = 0; i < size(); i++) {
          pMem[i] = pMem[i] - val;
      }
      //cout << tmp.size();
      return *this;
  }
  TDynamicVector operator*(T val)
  {
      //TDynamicVector<T> tmp(size());
      for (int i = 0; i < size(); i++) {
          pMem[i] = pMem[i] * val;
      }
      //cout << tmp.size();
      return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw std::exception("Incorrect size");
      }
      //TDynamicVector<T> tmp(this->size());
      for (int i = 0; i < this->size(); i++) {
          pMem[i] = pMem[i] + v.pMem[i];
      }
      return *this;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw std::exception("Incorrect size");
      }
      //TDynamicVector<T> tmp(this->size());
      for (int i = 0; i < this->size(); i++) {
          pMem[i] = pMem[i] - v.pMem[i];
      }
      return *this;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw std::exception("Incorrect size");
      }
      T ans = 0;
      for (int i = 0; i < sz; i++){
          ans = ans + (pMem[i] * v.pMem[i]);
      }
      return ans;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz <= 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (sz > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size should be lesser than MAX");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  T& at(size_t i1, size_t i2)
  {
      if (i1 < 0 || i1 >= sz || i2 < 0 || i2 >= sz)
          throw "incorrect index";
      return this->pMem[i1][i2];
  }
  const T& at(size_t i1, size_t i2) const
  {
      if (i1 < 0 || i1 >= sz || i2 < 0 || i2 >= sz)
          throw "incorrect index";
      return this->pMem[i1][i2];
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)//needs check!
          return 0;
      for (int i = 0; i < m.sz; i++)
          if (this->pMem[i] != m.pMem[i])
              return 0;
      return 1;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      //TDynamicMatrix<T> tmp(size());
      for (int i = 0; i < size(); i++) {
          pMem[i] = pMem[i] * val;
      }
      //cout << tmp.size();
      return *this;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      throw "Method is not implemented";
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::exception("Incorrect size");
      }
      //TDynamicVector<T> tmp(this->size());
      for (int i = 0; i < this->size(); i++) {
          for (int j = 0; j < this->size(); j++) {
              pMem[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
      return *this;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::exception("Incorrect size");
      }
      //TDynamicVector<T> tmp(this->size());
      for (int i = 0; i < this->size(); i++) {
          for (int j = 0; j < this->size(); j++) {
              pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return *this;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix answ(sz);
      if (sz != m.sz) {
          throw std::exception("Incorrect size");
      }
      for (int i = 0; i < sz; i++){
          for (int j = 0; j < sz; j++){
              answ.pMem[i] = answ.pMem[i] + pMem[j] * m.pMem[i][j];
          }
      }
      return answ;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
};

#endif
