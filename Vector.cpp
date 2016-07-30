#include "Vector.h"



    Vector::Vector(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector::Vector(double x, double y) {
        Vector(x, y, 0);
    }

    Vector::Vector(const Vector& alt) {
        this->x = alt.getX();
        this->y = alt.getY();
        this->z = alt.getZ();
    }

    Vector::Vector(){
        Vector(0,0,0);
    }


    void Vector::operator*=(double a) {
        this->x *= a;
        this->y *= a;
        this->z *= a;
    }

    void Vector::operator+=(const Vector &a) {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
    }

    void Vector::operator=(const Vector& v1){
        this->x = v1.getX();
        this->y = v1.getY();
        this->z = v1.getZ();
    }

    void Vector::operator/=(double a) {
        this->x /= a;
        this->y /= a;
        this->z /= a;
    }

    void Vector::operator-=(const Vector &v) {
        this->x -= v.getX();
        this->y -= v.getY();
        this->z -= v.getZ();
    }



std::ostream& operator<<(std::ostream& out, const Vector& v) {
    return out << v.getX() << " " << v.getY() << " " << v.getZ();
}

Vector operator+(Vector &v1, const Vector &v2) {
    v1+=v2;
    return v1;
}

Vector operator-(Vector &v1, const Vector& v2) {
    v1-=v2;
    return v1;
}

Vector operator*(Vector & v1, double s) {
    v1*=s;
    return v1;
}

Vector operator/(Vector &v1, double s){
    v1/=s;
    return v1;
}