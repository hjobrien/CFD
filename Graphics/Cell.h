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


    Node* update();

    Container& split();

    bool getWillSplit();
    bool canMerge();

    Cell* cloneToSmallerCell();

    std::vector<double> getRgb();



    virtual Cell* clone() const
    {
        return new Cell( *this );
    }

private:
    bool ableToMerge = true;
    bool willSplit = true;

    double h, s, l;


    double density;
    double pressure;
    double velocity;

    std::string toString(){
        return "Cell";
    }

    Cell* shrink(){
        setSize((float) (getSize() / 2.0));
    }
};


#endif //CFD_CELL2_H
