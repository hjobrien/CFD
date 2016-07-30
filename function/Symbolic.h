//
// Created by Hank O'Brien on 2/23/16.
//

#ifndef CFD_SYMBOLIC_H
#define CFD_SYMBOLIC_H

#include <iostream>

class Symbolic {
    double value;
    bool hasBeenSet;
public:
    Symbolic();
    Symbolic(double value);

    void operator*=(double a);
    void operator/=(double a);
    void operator+=(double a);
    void operator-=(double a);

    void operator*=(Symbolic &s);
    void operator/=(Symbolic &s);
    void operator+=(Symbolic &s);
    void operator-=(Symbolic &s);

    void operator=(double a);



//    void setValue(double a){
//        value = a;
//    }
    double getValue() const{
        return value;
    }

    double hasValue() const{
        return hasBeenSet;
    }
};

std::ostream& operator<<(std::ostream& str, const Symbolic& v);
double operator+(double a, const Symbolic &s);
double operator-(double a, const Symbolic &s);
double operator*(double a, const Symbolic &s);
double operator/(double a, const Symbolic &s);

double operator+(Symbolic &s1, const Symbolic &s2);
double operator-(Symbolic &s1, const Symbolic &s2);
double operator*(Symbolic &s1, const Symbolic &s2);
double operator/(Symbolic &s1, const Symbolic &s2);

#endif //CFD_SYMBOLIC_H
