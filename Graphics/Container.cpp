//
// Created by Hank O'Brien on 7/4/16.
//

#include "Container.h"



Container::Container(float containerWidth, float topLeftX, float topLeftY) {
    this->topLeft = new Cell(containerWidth / 2, topLeftX, topLeftY);
    this->topRight = new Cell(containerWidth / 2, topLeftX, topLeftY);
    this->bottomRight = new Cell(containerWidth / 2, topLeftX, topLeftY);
    this->bottomLeft = new Cell(containerWidth / 2, topLeftX, topLeftY);
}


Container::Container(Node *topLeft, Node *topRight, Node *bottomRight, Node *bottomLeft) {
    this->topLeft = topLeft;
    this->topRight = topRight;
    this->bottomRight = bottomRight;
    this->bottomLeft = bottomLeft;
}


//should take values from instance's fields, perform an average, and create a new cell with those values
Cell* Container::merge() {
    Cell* mergedResult = new Cell(0, topLeft->getX(), topLeft->getY());//todo: change
    return mergedResult;
}

//order of updates doesnt matter, order only matters when data gets shifted from one cell to the next
void Container::update() {
    Node* updatedTL = new Cell(0, 0, 0);//this->topLeft->update();
    Node* updatedTR = new Cell(0, 0, 0);//this->topRight->update();
    Node* updatedBR = new Cell(0, 0, 0);//this->bottomRight->update();
    Node* updatedBL = new Cell(0, 0, 0);//this->bottomLeft->update();
    if(updatedTL->canMerge() && updatedTR->canMerge() && updatedBR->canMerge() && updatedBL->canMerge())
    {
//        return merge();
    }
//    return 0;

}

bool Container::canMerge() {
    return false;
}









