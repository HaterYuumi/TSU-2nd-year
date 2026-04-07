#include <iostream>
#include<cmath>
using namespace std;

struct complex{
  double re, im;
  void complexInput();
  void complexPrint();
  bool isEqual(complex);
  double mod();
  complex sum(complex);
  complex sub(complex);
  complex mul(complex);
  complex divi(complex);
};

void complex::complexInput(){
    cout << "re = ";
    cin >> re;
    cout << "im = ";
    cin >> im;
}

complex complex::sum(complex x){
    complex res;
    res.re = re + x.re;
    res.im = im + x.im;
    return res;
}

complex complex::sub(complex x){
    complex res;
    res.re = re - x.re;
    res.im = im - x.im;
    return res;
}

complex complex::mul(complex x){
    complex res;
    res.re = re * x.re - (im * x.im);
    res.im = im * x.re + re * x.im;
    return res;
}

complex complex::divi(complex x){
    complex res;
    res.re = re;
    res.im = im;
    if ((x.re && x.im) == 0){
      cout << "err" << endl;
      res.re = 0;
      res.im = 0;
      return res;
    } 
    complex tmp = x;
    tmp.im *= -1;
    x = x.mul(tmp);
    res.re = (re * tmp.re - (im * tmp.im)) / x.re;
    res.im = (im * tmp.re + re * tmp.im) / x.re;
    return res;
}

void complex::complexPrint(){
    cout << "re = " << re;
    cout << " ";
    cout << "im = " << im;
}

bool complex::isEqual(complex x){
    if (re == x.re && im == x.im) return true;
    return false;
}

double complex::mod(){
    complex res;
    res.re = re*re - im*im;
    double tmp = sqrt(res.re);
    return tmp;
}

int main() {
    complex c1, c2, c3;
    c1.complexInput();
    c2.complexInput();
    cout << endl;
    cout << "mod c1 = " << c1.mod() << endl;
    cout << "sum c1 and c2:" << endl;
    c3 = c1.sum(c2);
    c3.complexPrint();
    cout << endl;
    cout << endl;
    cout << "sub c1 and c2:" << endl;
    c3 = c1.sub(c2);
    c3.complexPrint();
    cout << endl;
    cout << endl;
    cout << "mul c1 and c2:" << endl;
    c3 = c1.mul(c2);
    c3.complexPrint();
    cout << endl;
    cout << endl;
    cout << "div c1 and c2:" << endl;
    c3 = c1.divi(c2);
    c3.complexPrint();
    cout << endl;
    cout << endl;
    if (c1.isEqual(c2)) cout << "c1 is Equal c2" << endl;
    else cout << "c1 isn`t Equal c2" << endl;
}
