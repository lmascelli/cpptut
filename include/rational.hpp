#pragma once
#include "exceptions.hpp"
#include <ostream>

class rational
{
public:
  rational(int p=0, int q=1): p{p}, q{q} {
    if (q==0) throw zero_division {};
    normalize();
  }

  rational operator+(rational r2){
    return {p*r2.q+q*r2.p, q*r2.q};
  }
  rational operator+=(rational r2){
    p = p*r2.q+q*r2.p;
    q = q*r2.q;
    return {p, q};
  }
  rational operator-(rational r2){
    return {p*r2.q-q*r2.p, q*r2.q};
  }
  rational operator-=(rational r2){
    p = p*r2.q-q*r2.p;
    q = q*r2.q;
    return {p, q};
  }
  rational operator*(rational r2){
    return {p*r2.p, q*r2.q};
  }
  rational operator*=(rational r2){
    p = p*r2.p;
    q = q*r2.q;
    return {p, q};
  }
  rational operator/(rational r2){
    if (r2.p == 0) throw zero_division {};
    return {p*r2.q, q*r2.p};
  }
  rational operator/=(rational r2){
    if (r2.p == 0) throw zero_division {};
    p = p*r2.q;
    q = q*r2.p;
    return {p, q};
  }
  
private:
  friend std::ostream &operator<<(std::ostream &os, const rational &r);
  void normalize(){
    int p=this->p, q=this->q;
    if (p%q == 0) {
      p /= q;
      q = 1;
    } else if (q%p == 0) {
      q /= p;
      p = 1;
    }
    if (q < 0) {
      q *= -1;
      p *= -1;
    }
    this->p = p;
    this->q = q;    
  }
  
  int p, q;
};

std::ostream &operator<<(std::ostream &os, const rational &r) {
  if (r.q > 1) {
    os << r.p << "/" << r.q;
  } else {
    os << r.p;
  }
  return os;
}
