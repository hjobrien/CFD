//
// Created by Hank O'Brien on 6/28/16.
//

#ifndef CFD_RKC45_H
#define CFD_RKC45_H

#include <cmath>
#include "assert.h"
#include <algorithm>

namespace IntegrationConstants
{
    const double a2 = 1.0 / 5,
            a3 = 3.0 / 10,
            a4 = 3.0 / 5,
            a5 = 1,
            a6 = 7.0 / 8;
    const double b21 = 1.0 / 5,
            b31 = 3.0 / 40,         b32 = 9.0 / 40 ,
            b41 = 3.0 / 10,         b42 = -9.0 / 10,    b43 = 6.0 / 5 ,
            b51 = -11.0/54,         b52 = 5.0 / 2  ,    b53 = -70.0/27,         b54 = 35.0 / 27,
            b61 = 1631.0 / 55296,   b62 = 175.0 / 512,  b63 = 575.0 / 13824,    b64 = 44275.0 / 110592, b65 = 253.0 / 4096; //Numerical recepies
    const double c1 = 37.0 / 378,   cs1 = 2825.0 / 27648,
            c2 = 0,             cs2 = 0,
            c3 = 250.0 / 621,   cs3 = 18575.0 / 48384,
            c4 = 125.0 / 594,   cs4 = 13525.0 / 55296,
            c5 = 0,             cs5 = 277.0 / 14336,
            c6 = 512.0 / 1771,  cs6 = 1.0 / 4;
    const double cd1 = c1 - cs1,
            cd2 = c2 - cs2,
            cd3 = c3 - cs3,
            cd4 = c4 - cs4,
            cd5 = c5 - cs5,
            cd6 = c6 - cs6;
    const double S = 0.875;

    const double minRatio = 0.125 * 0.125 * 0.125 * 0.125;// 1/8^4
    const double maxRatio = 8*8*8*8*8;//8^5


}

template<typename F> double RKCK45adaptive(double x, double y, double distance, double maxErr, const F& dydx, double h)
{

    using namespace IntegrationConstants;
    double xC = 0, yC = 0;
    double endX = x + distance;
    while(x < endX)
    {
        while(true)
        {
            double k1 = h*dydx(x, y);
            double k2 = h*dydx(x + a2*h, y + b21*k1);
            double k3 = h*dydx(x + a3*h, y + b31*k1 + b32*k2);
            double k4 = h*dydx(x + a4*h, y + b41*k1 + b42*k2 + b43*k3);
            double k5 = h*dydx(x + a5*h, y + b51*k1 + b52*k2 + b53*k3 + b54*k4);
            double k6 = h*dydx(x + a6*h, y + b61*k1 + b62*k2 + b63*k3 + b64*k4 + b65*k5);

            double increment = c1*k1 + c2*k2 + c3*k3 + c4*k4 + c5*k5 + c6*k6;
            double error = fabs(cd1*k1 + cd2*k2 + cd3*k3 + cd4*k4 + cd5*k5 + cd6*k6);

            double desiredError = fabs(increment) * maxErr / distance; // What if predicted slope is 0, yet function isn't actually totally flat? Perhaps floor of 10^-9?
            double ratio = desiredError / error;

            if(error > desiredError)
            {
                if(ratio < minRatio)    h *= S * 0.125;
                else                    h *= S * pow(ratio, 0.25);
                assert(xC + h != xC);
                continue;
            }
            //Kahan sum both x and y
            double dx = h - xC;
            double xt = x + dx;
            xC = (xt - x) - dx;
            x = xt;

            double dy = increment - yC;
            double yt = y + dy;
            yC = (yt - y) - dy;
            y = yt;
            h *= S * ((ratio >= maxRatio) ? 8 : pow(ratio, 0.2));
            h = std::min(h, endX - x);
            break;
        }
    }
    return y;
}
#endif //CFD_RKC45_H
