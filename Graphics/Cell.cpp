//
// Created by Hank O'Brien on 7/4/16.
//

#include "Cell.h"

Cell::Cell(float sideLength, float topLeftX, float topLeftY) {
//TODO: construct cell
    setSize(sideLength);
    setTopLeft(topLeftX, topLeftY);

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
        ++(this->density);
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

std::vector<double> Cell::getRgb() {
    return colorConverter::hslToRgb(h, s, l);
}

Cell::Cell(float sideLength, float topLeftX, float topLeftY, double density) {
    setTopLeft(topLeftX, topLeftY);
    setSize(sideLength);
    this->density = density;
    this->h = density * 265 / 360;
    this->s = 1;
    this->l = 0.5;
//    std::cout << density << " " << h << " " << s << " " << l << "\n";

}




















