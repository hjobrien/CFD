//
// Created by Hank O'Brien on 2/23/16.
//

#ifndef CFD_NO_VALUE_H
#define CFD_NO_VALUE_H

#include <exception>

class no_value: public std::exception{
    const char* what() const throw(){
        return "Symbolic variable has not been set to a value";
    }
};


#endif //CFD_NO_VALUE_H
