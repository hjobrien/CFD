//
// Created by Hank O'Brien on 6/25/16.
//

#ifndef CFD_IMPLICITRK4_H
#define CFD_IMPLICITRK4_H


#include <vector>

const double INITIAL_STEP_LENGTH = 0.1;

template <typename F> std::vector<double> implicitFixedIntegate(double startX, double endX, double startY,
                                                                double maxErrorFrac, const F &function){

    double x = startX;
    double y = startY;
    double stepLength = INITIAL_STEP_LENGTH;
    double halfStep = stepLength / 2;
    long predictedStepCount = (long) ((endX - startX) / stepLength);
    std::vector<double> points;
    points.reserve((unsigned long) predictedStepCount);
    points.push_back(y);
    double bkProduct = 0;
    double k1,k2,k3,k4;
    while(x < endX){
        k1 = function(x, y);
        k2 = function(x + halfStep, y + halfStep * k1);
        k3 = function(x + halfStep, y + halfStep * k2);
        k4 = function(x + stepLength, y + stepLength * k3);
        y = y + stepLength * bkProduct;
        x += stepLength;
    }



}




#endif //CFD_IMPLICITRK4_H
