//
// Created by Hank O'Brien on 2/2/16.
//

#ifndef CFD_VECTOR_H
#define CFD_VECTOR_H
#include <iostream>

class Vector {


    double x, y, z;
public:

    Vector(double x, double y, double z);
    Vector(double x, double y);
    Vector();
    Vector(const Vector& alt);

    void operator*=(double a);
    void operator/=(double a);
    void operator+=(const Vector &a);
    void operator-=(const Vector &v);

    void operator=(const Vector &a);




    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }
};

std::ostream& operator<<(std::ostream& str, const Vector& v);
Vector operator+(Vector &v1, const Vector &v2);
Vector operator-(Vector &v1, const Vector &v2);
Vector operator*(Vector &v1, double s);
Vector operator/(Vector &v1, double s);




#endif //CFD_VECTOR_H
