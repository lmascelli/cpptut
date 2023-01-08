#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include <cassert>
#include <initializer_list>
using namespace std;

class polynomial
{
public:
  polynomial(unsigned int degree): degree{degree} {
    coefficients.resize(degree + 1);
  }

  polynomial(std::initializer_list<double> values) {
    degree = values.size()-1;
    copy(begin(values), end(values), back_inserter(coefficients));
  }
  
  polynomial(const polynomial &o) = default;
  
  polynomial(polynomial&& o) {
    cout << "moving constructor" << endl;
    degree = o.degree;
    coefficients.clear();
    std::move(std::begin(o.coefficients),
	      std::end(o.coefficients),
	      std::back_inserter(coefficients));
    o.coefficients.clear();
    o.degree = 0;
  }
  
  ~polynomial(){}

  polynomial& operator=(polynomial& src) noexcept {
    cout << "copy assignement" << endl;
    coefficients = src.coefficients;
    degree = src.degree;
    return *this;
  }

  polynomial& operator=(initializer_list<double> values) {
    degree = values.size()-1;
    coefficients.clear();
    copy(begin(values), end(values), back_inserter(coefficients));
    return *this;
  }
  
  polynomial& operator=(polynomial&& src) noexcept {
    cout << "moving assignement" << endl;
    coefficients.clear();
    std::move(std::begin(src.coefficients),
	      std::end(src.coefficients),
	      std::back_inserter(coefficients));
    degree = src.degree;
    src.coefficients = {0};
    src.degree = 0;
    return *this;
  }

  void set_coefficients(vector<double> coefficients) {
    assert(coefficients.size() == this->coefficients.size() &&
	   "coefficients must be of the same size");

    this->coefficients = coefficients;
  }
  
private:
  unsigned int degree;
  std::vector<double> coefficients;
  friend std::ostream &operator<<(std::ostream &os, const polynomial &r);
};

std::ostream &operator<<(std::ostream &os, const polynomial &r) {
  if (r.degree > 1) {
    for (unsigned int i=r.degree; i>1; i--) {
      os << r.coefficients[i] << "x^" << i << " + ";
    }
  }
  if (r.degree > 0)
    os << r.coefficients[1] << "x + ";
  os << r.coefficients[0];
  return os;
}

polynomial f(double c2, double c1, double c0) {
  polynomial ret(2);
  ret.set_coefficients({c2, c1, c0});
  return ret;
}
