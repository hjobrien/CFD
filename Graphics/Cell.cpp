//
// Created by Hank O'Brien on 7/4/16.
//

#include "Cell.h"

Cell::Cell(float sideLength, float topLeftX, float topLeftY) {
//TODO: construct cell
    setSize(sideLength);
    setTopLeft(topLeftX, topLeftY);

}

Cell::Cell(float sideLength, float topLeftX, float topLeftY, double density, double xVelocity, double internalEnergy) {
    setTopLeft(topLeftX, topLeftY);
    setSize(sideLength);
    this->density = density;
    this->xVelocity = xVelocity;
    this->internalEnergy = internalEnergy;
}


//take cell's state, copy them 4 times by value, store them in 4 new cells and add it to the container
//Container& Cell::split() {
//    Container* c = new Container(this->cloneToSmallerCell(), this->cloneToSmallerCell(), this->cloneToSmallerCell(),
//                                 this->cloneToSmallerCell());
//    return *c;
//}

void Cell::update() {
//    if(willSplit){
//        return &split();
//    }else
//    {
        this->density += 0.05;
        this->xVelocity += 0.05;
        this->internalEnergy += 0.025;
        //TODO: do math here
//    }
}

bool Cell::getWillSplit() const{
    return willSplit;
}

bool Cell::canMerge() {
    return ableToMerge;
}

//Cell *Cell::cloneToSmallerCell() {
//    return this->clone()->shrink();
//}






















