//
// Created by Hank O'Brien on 3/24/16.
//

#ifndef CFD_RUNGEKUTTA4_H
#define CFD_RUNGEKUTTA4_H

#include <vector>


template<typename F> std::vector<double> integrate(double startX, double startY, long numSteps, double stepSize, const F& function){
    double halfStep = stepSize / 2;
    std::vector<double> points;
    points.reserve((unsigned long) (numSteps + 1));
    points.push_back(startY);
    double k1,k2,k3,k4;
    double x = startX;
    double y = startY;
    for(int i = 1; i <= numSteps; i++) {
        k1 = function(x, y);
        k2 = function(x + halfStep, y + halfStep * k1);
        k3 = function(x + halfStep, y + halfStep * k2);
        k4 = function(x + stepSize, y + stepSize * k3);
        y = y + (stepSize/6) * (k1 + 2 * k2 + 2 * k3 + k4);
        x = x + stepSize;
        points.push_back(y);
    }
    return points;
}


#endif //CFD_RUNGEKUTTA4_H
