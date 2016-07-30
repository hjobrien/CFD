//
// Created by Hank O'Brien on 3/26/16.
//

#ifndef CFD_ADAPTIVERUNGEKUTTA_H
#define CFD_ADAPTIVERUNGEKUTTA_H

#include <iostream>
#include <vector>
#include <math.h>

//following constants refer to Cash-Karp constants found in the book 'Numerical Recipes' pg 717
const double A[6] = {0, 1.0 / 5.0, 3.0 / 10.0, 3.0 / 5.0, 1.0, 7.0 / 8.0};
const double B[6][5] = {
        {0, 0, 0, 0, 0},
        {1.0 / 5.0, 0, 0, 0, 0},
        {3.0 / 40.0, 9.0 / 40.0, 0, 0, 0},
        {3.0 / 10.0, -9.0 / 10.0, 6.0 / 5.0, 0 ,0},
        {-11.0 / 54.0, 5.0 / 2.0, -70.0 / 27.0, 35.0 / 27.0, 0},
        {1631.0 / 55296.0, 175.0 / 512.0, 575.0 / 13824.0, 44275.0 / 110592.0, 253.0 / 4096.0}
};
const double C[6] = {37.0 / 378.0, 0, 250.0 / 621.0, 125.0 / 594.0, 0, 512.0 / 1771.0};
const double CSTAR[6] = {2825.0 / 27648.0, 0, 18575.0 / 48384.0, 13525.0 / 55296.0, 277.0 / 14336.0, 1.0 / 4.0};
//end Cash-Karp constants

const double INITIAL_STEP_LENGTH = 0.1;


using std::cout;
using std::endl;


template <typename F> std::vector<double> embeddedIntegrate(double startX, double endX, double startY,
                                                            double maxErrorFrac, const F &function){
    double x = startX;
    double y = startY;
    double stepLength = INITIAL_STEP_LENGTH;
    long predictedSteps = (long)((endX - startX)/stepLength);
//    double halfStep = stepLength / 2;
    std::vector<double> points;
    points.reserve((unsigned long) predictedSteps);
    points.push_back(y);
    double k[6];        //refers to the 6 k-constants used in the algorithm
    double error = 0;
    while(x < endX){
        error = 0;
        //these k variables are set corresponding to the math behind the embedded runge-kutta method
        k[0] = stepLength * function(x, y);
        k[1] = stepLength * function(x + A[1] * stepLength, y + B[1][0] * k[0]);
        k[2] = stepLength * function(x + A[2] * stepLength, y + B[2][0] * k[0] + B[2][1] * k[1]);
        k[3] = stepLength * function(x + A[3] * stepLength, y + B[3][0] * k[0] + B[3][1] * k[1] + B[3][2] * k[2]);
        k[4] = stepLength * function(x + A[4] * stepLength, y + B[4][0] * k[0] + B[4][1] * k[1] + B[4][2] * k[2]
                                                            + B[4][3] * k[3]);
        k[5] = stepLength * function(x + A[5] * stepLength, y + B[5][0] * k[0] + B[5][1] * k[1] + B[5][2] * k[2]
                                                            + B[5][3] * k[3] + B[5][4] * k[4]);
        double yIncrement = C[0] * k[0] + C[1] * k[1] + C[2] * k[2] + C[3] * k[3] + C[4] * k[4] + C[5] * k[5];

        //6 because of the 6 k variables
        for(int j = 0; j < 6; j++){
            double cDiff = C[j] - CSTAR[j];     //to facilitate debugging
            double prod = cDiff * k[j];         //as above
            error += prod;
        }
        double maxError = maxErrorFrac * yIncrement;


        //if the error is allowable, advance x, save y and re-calculate, otherwise recalculate the y for a new stepsize
        if(fabs(error) <= fabs(maxError)){
            x += stepLength;
            y += yIncrement;
            points.push_back(y);
            if(error != 0) {
                //error scales as O(h^5), so we use it to make the algorithm scale on O(h^4) quickly
                //lets us increase or decrease stepSize as needed
                double errorFrac = fabs(maxError / error);
                stepLength *= pow(errorFrac, 0.2);

            }
            else{
                //attempt to speed up integration when error is 0
                stepLength *= 2;
            }
        }
        else{
            stepLength *= pow(fabs(maxError / error), 0.2);
        }
    }
//    std::cout << x << ", " << endX << std::endl;
    return points;
}

#endif //CFD_ADAPTIVERUNGEKUTTA_H
