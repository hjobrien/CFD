//
// Created by Hank O'Brien on 7/4/16.
//

#ifndef CFD_CONTAINER_H
#define CFD_CONTAINER_H

class Cell;
#include "Node.h"
#include "Cell.h"

class Container : public Node
{

public:

    Container(float containerWidth, float topLeftX, float topLeftY);

    Container(Node* topLeft, Node* topRight, Node* bottomRight, Node* bottomLeft);

    void update();

    bool canMerge();

    virtual Container* clone() const
    {
        return new Container( *this );
    }

private:


    Cell* merge();

    std::string toString(){
        return "Container";
    }
};


#endif //CFD_CONTAINER_H
