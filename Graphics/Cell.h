//
// Created by Hank O'Brien on 7/4/16.
//

#ifndef CFD_CELL2_H
#define CFD_CELL2_H

class Container;
#include "Node.h"
#include "Container.h"

class Cell : public Node{

public:

    Cell(float sideLength, float topLeftX, float topLeftY);

    Cell(float sideLength, float topLeftX, float topLeftY, double r, double g, double b);

    Node* update();

    Container& split();

    bool getWillSplit();
    bool canMerge();

    Cell* cloneToSmallerCell();

    double getR(){
        return r;
    }

    double getG(){
        return g;
    }

    double getB(){
        return b;
    }



    virtual Cell* clone() const
    {
        return new Cell( *this );
    }

private:
    bool ableToMerge = true;
    bool willSplit = true;

    double r,g,b;


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
