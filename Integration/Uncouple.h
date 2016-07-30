//
// Created by Hank O'Brien on 4/7/16.
//

#ifndef CFD_UNCOUPLE_H
#define CFD_UNCOUPLE_H


#include <utility>
#include <math.h>
#include <stdio.h>

typedef std::pair<double, double> roots;

roots quad(double a, double b, double c);
double** eigenVector(double** coefficients, roots eigenValues);

void uncouple (double** coefficients, double t, double x, double y){        //for a function f(t,x) = y
    roots eigenValues = quad(1, -1 * coefficients[0][0] - coefficients[1][1], coefficients[0][0] * coefficients[1][1]
                                                                          - coefficients[0][1] * coefficients[1][0]);
    double **eigenVectorMatrix = eigenVector(coefficients, eigenValues);

    //finds constants for exponents
    //original implementation, should be simplified below
//    double c2 = ((y * eigenVectorMatrix[0][0] * exp(eigenValues.first * t)) -
//            (x * (eigenVectorMatrix[1][0] * exp(eigenValues.first * t)))) /
//            (((eigenVectorMatrix[0][0] * exp(eigenValues.first * t)) * (eigenVectorMatrix[1][1] * exp(eigenValues.second * t))) -
//            ((eigenVectorMatrix[1][0] * exp(eigenValues.first * t)) * (eigenVectorMatrix[0][1] * exp(eigenValues.second * t))));

    double c2 = (eigenVectorMatrix[0][0] * y - eigenVectorMatrix[1][0] * x) /
            (exp(eigenValues.second * t) *
            (eigenVectorMatrix[0][0] * eigenVectorMatrix[1][1] - eigenVectorMatrix[1][0] * eigenVectorMatrix[0][1]));

    double c1 = (x - eigenVectorMatrix[0][1] * c2 * exp(eigenValues.second * t)) /
            (eigenVectorMatrix[0][0] * exp(eigenValues.first * t));

    printf("\n   x = %.3fe^%.3ft + %.3fe^%.3ft \n", (eigenVectorMatrix[0][0] * c1), eigenValues.first, (eigenVectorMatrix[0][1] * c2), eigenValues.second);
    printf("\n   y = %.3fe^%.3ft + %.3fe^%.3ft \n\n", (eigenVectorMatrix[1][0] * c1), eigenValues.second, (eigenVectorMatrix[1][1] * c2), eigenValues.second);
    //mem cleanup
    delete [] eigenVectorMatrix[0];
    delete [] eigenVectorMatrix[1];
    delete [] eigenVectorMatrix;
}

//letters refer to coefficients of a quadratic equations ax^2 + bx + c
roots quad(double a, double b, double c) {
    roots eqRoots((-1 * b + pow((b * b - 4 * a * c), 0.5) / (2 * a)),
                  (-1 * b - pow((b * b - 4 * a * c), 0.5) / (2 * a)));
    return eqRoots;
}


double** eigenVector(double** coefficients, roots eigenValues){
    double **eigenVectorMatrix;
    eigenVectorMatrix = new double*[2];
    eigenVectorMatrix[0] = new double[2];
    eigenVectorMatrix[1] = new double[2];
    eigenVectorMatrix[0][0] = 1;
    eigenVectorMatrix[0][1] = 1;
    eigenVectorMatrix[1][0] = (coefficients[0][0] - eigenValues.first) / (-1 * coefficients[0][1]);
    eigenVectorMatrix[1][1] = (coefficients[0][0] - eigenValues.second) / (-1 * coefficients[0][1]);
    return eigenVectorMatrix;
}

#endif //CFD_UNCOUPLE_H
