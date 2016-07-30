//
// Created by Hank O'Brien on 7/4/16.
//

#include "Cell.h"

Cell::Cell(float sideLength, float topLeftX, float topLeftY) {
//TODO: construct cell
    setSize(sideLength);
    setTopLeft(topLeftX, topLeftY);

}

Cell::Cell(float sideLength, float topLeftX, float topLeftY, double r, double g, double b) {
    setSize(sideLength);
    setTopLeft(topLeftX, topLeftY);
    this->r = r;
    this->g = g;
    this->b = b;
}


//take cell's state, copy them 4 times by value, store them in 4 new cells and add it to the container
Container& Cell::split() {
    Container* c = new Container(this->cloneToSmallerCell(), this->cloneToSmallerCell(), this->cloneToSmallerCell(),
                                 this->cloneToSmallerCell());
    return *c;
}

Node* Cell::update() {
    if(willSplit){
        return &split();
    }else
    {
        //TODO: do math here
    }
}

bool Cell::getWillSplit() {
    return willSplit;
}

bool Cell::canMerge() {
    return ableToMerge;
}

Cell *Cell::cloneToSmallerCell() {
    return this->clone()->shrink();
}
















