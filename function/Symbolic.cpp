//
// Created by Hank O'Brien on 2/23/16.
//

#include "Symbolic.h"
#include "no_value.h"

Symbolic::Symbolic() {
    hasBeenSet = false;
}

Symbolic::Symbolic(double value) {
    hasBeenSet = true;
    this->value = value;
}

void Symbolic::operator*=(double a) {
    if(hasBeenSet){
        this->value*=a;
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator/=(double a) {
    if(hasBeenSet){
        this->value/=a;
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator+=(double a) {
    if(hasBeenSet){
        this->value+=a;
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator-=(double a) {
    if(hasBeenSet){
        this->value-=a;
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator*=(Symbolic &s) {
    if(s.hasValue()){
        this->value*=s.getValue();
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator/=(Symbolic &s) {
    if(s.hasValue()){
        this->value/=s.getValue();
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator+=(Symbolic &s) {
    if(s.hasValue()){
        this->value+=s.getValue();
    }
    else{
        no_value e;
        throw e;
    }
}

void Symbolic::operator-=(Symbolic &s) {
    if(s.hasValue()){
        this->value-=s.getValue();
    }
    else{
        no_value e;
        throw e;
    }
}








void Symbolic::operator=(double a) {
    hasBeenSet = true;
    this->value = a;
}

double operator+(double a, const Symbolic &s) {
    return a+=s.getValue();
}


double operator-(double a, const Symbolic &s) {
    return a-=s.getValue();
}

double operator*(double a, const Symbolic &s) {
    return a*=s.getValue();
}

double operator/(double a, const Symbolic &s) {
    return a/=s.getValue();
}

double operator+(Symbolic &s1, const Symbolic &s2){
    if(s1.hasValue()){
        return s1.getValue()+s2;
    }
    else{
        no_value e;
        throw e;
    }
}

double operator-(Symbolic &s1, const Symbolic &s2){
    if(s1.hasValue()){
        return s1.getValue()-s2;
    }
    else{
        no_value e;
        throw e;
    }
}

double operator*(Symbolic &s1, const Symbolic &s2){
    if(s1.hasValue()){
        return s1.getValue()*s2;
    }
    else{
        no_value e;
        throw e;
    }
}

double operator/(Symbolic &s1, const Symbolic &s2){
    if(s1.hasValue()){
        return s1.getValue()/s2;
    }
    else{
        no_value e;
        throw e;
    }
}




std::ostream &operator<<(std::ostream &str, const Symbolic &v) {
    return str << v.getValue();
}


