//
// Created by Hank O'Brien on 7/30/16.
//

#include <vector>
#include <cmath>
#include <iostream>


namespace colorConverter {

    static double hueToRgb(double p, double q, double t) {
        if (t < 0)
            t += 1;
        if (t > 1)
            t -= 1;
        if (t < 1.0 / 6.0)
            return p + (q - p) * 6 * t;
        if (t < 1.0 / 2.0)
            return q;
        if (t < 2.0 / 3.0)
            return p + (q - p) * (2.0 / 3.0 - t) * 6;
        return p;
    }

    /**
    * Converts an HSL color value to RGB. Conversion formula
    * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
    * Assumes h, s, and l are contained in the set [0, 1] and
    * returns r, g, and b in the set [0, 255].
    *
    * @param   {number}  h       The hue
    * @param   {number}  s       The saturation
    * @param   {number}  l       The lightness
    * @return  {Array}           The RGB representation
    */
    static const std::vector<double>& hslToRgb(double h, double s, double l) {
        double r, g, b;

        if (s == 0) {
            r = g = b = l; // achromatic
        } else {
            double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            double p = 2 * l - q;
            r = hueToRgb(p, q, h + 1.0 / 3.0);
            g = hueToRgb(p, q, h);
            b = hueToRgb(p, q, h - 1.0 / 3.0);
        }
        std::vector<double> *rgb = new std::vector<double>;
        rgb->push_back((r));
        rgb->push_back((g));
        rgb->push_back((b));
        return *rgb;
    }




    /**
     * Converts an RGB color value to HSL. Conversion formula
     * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
     * Assumes r, g, and b are contained in the set [0, 255] and
     * returns h, s, and l in the set [0, 1].
     *
     * @param   {number}  r       The red color value
     * @param   {number}  g       The green color value
     * @param   {number}  b       The blue color value
     * @return  {Array}           The HSL representation
     */
    static const std::vector<double>& rgbToHsl(const int r, const int g, const int b) {
        int max = std::max(std::max(r, g), b);
        int min = std::min(std::min(r, g), b);
        double h, s, l;
        l = ((double) (max + min)) / 2 / 255;

        if (max == min) {
            h = s = 0; // achromatic
        } else {
            double d = max - min;
            s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
            if (max == r) {
                h = (g - b) / d + (g < b ? 6 : 0);
            } else if (max == g) {
                h = (b - r) / d + 2;
            } else if (max == b) {
                h = (r - g) / d + 4;
            } else {
                std::cout << "switch statement could not match max to r, g, or b, now setting it to the b case";
                h = (r - g) / d + 4;
            }
            h /= 6;
        }
        std::vector<double> *hsl = new std::vector<double>;
        hsl->push_back(h);
        hsl->push_back(s);
        hsl->push_back(l);
        return *hsl;

    }
}