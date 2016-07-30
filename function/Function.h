//
// Created by Hank O'Brien on 2/26/16.
//

#ifndef CFD_FUNCTION_H
#define CFD_FUNCTION_H


class Function {
public:
    template<typename F> double applyValues(double x, double y, F f){
        return f(x,y);
    }


};


#endif //CFD_FUNCTION_H
