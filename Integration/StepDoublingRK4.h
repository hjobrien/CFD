//
// Created by Hank O'Brien on 3/29/16.
//

#ifndef CFD_STEPDOUBLINGRK4_H
#define CFD_STEPDOUBLINGRK4_H


#include <vector>

using std::vector;

const double INIIAL_STEP_SIZE = 0.1;

template <typename F> double getYIncrease(double x, double y, double stepSize, const F& function){
    double k1,k2,k3,k4;
    k1 = function(x, y);
    k2 = function(x + stepSize, y + stepSize * k1);
    k3 = function(x + stepSize, y + stepSize * k2);
    k4 = function(x + 2 * stepSize, y + 2 * stepSize * k3);
    double yIncrement = (stepSize / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    return yIncrement;
}

template<typename F> std::vector<double> doublingIntegrate(double startX, double startY, double endX,
                                                           double maxErrorFrac, const F &function){
    double stepSize = INIIAL_STEP_SIZE;
    double halfStep = stepSize / 2;
    std::vector<double> points;
    points.push_back(startY);
    double x = startX;
    double y = startY;
    double halfYJump;
    double secondHalfYJump;
    double fullYJump;
    while(x <= endX) {
        halfYJump = getYIncrease(x, y, halfStep, function);
//        secondHalfYJump = getYIncrease(x + halfStep, y + halfYJump, halfStep, function);
        fullYJump = getYIncrease(x, y, stepSize, function);
        if(fullYJump / y < maxErrorFrac){
            y += fullYJump;
            x += stepSize;
            points.push_back(y);
//            stepSize *= 2;
        }
        else if(halfYJump / y < maxErrorFrac){
            y += halfYJump;
            x += halfStep;
            points.push_back(y);
            stepSize /= 2;
        }
        else{
            halfStep /= 2;
        }

    }
    return points;
}




#endif //CFD_STEPDOUBLINGRK4_H
