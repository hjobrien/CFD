//
// Created by Hank O'Brien on 7/4/16.
//

#ifndef CFD_CELL2_H
#define CFD_CELL2_H

class Container;
#include "Node.h"
#include "Container.h"
#include "ColorConverter.cpp"

class Cell : public Node{

public:

    Cell(float sideLength, float topLeftX, float topLeftY);

    Cell(float sideLength, float topLeftX, float topLeftY, double density);


    void update();

    Container& split();

    bool getWillSplit() const;
    bool canMerge();

    Cell* cloneToSmallerCell();

    double getDensity() const{
        return this->density;
    }

    virtual Cell* clone() const
    {
        return new Cell( *this );
    }

private:
    bool ableToMerge = true;
    bool willSplit = true;


    double density;
    double pressure;
    double velocity;

    std::string toString() const{
        return "Cell";
    }

    Cell* shrink(){
        setSize((float) (getSize() / 2.0));
        //todo: return
    }
};


#endif //CFD_CELL2_H
