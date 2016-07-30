//
// Created by Hank O'Brien on 7/4/16.
//

#include "Node.h"

const std::vector<Node *>& Node::getSubNodesAsList() const{
    std::vector<Node *> subNodes;
    subNodes.push_back(topLeft);
    subNodes.push_back(topRight);
    subNodes.push_back(bottomRight);
    subNodes.push_back(bottomLeft);
    return subNodes;
}

float Node::getSize() {
    return  size;
}

void Node::setSize(float size){
    this->size = size;
}

float Node::getY() {
    return this->topLeftY;
}

float Node::getX() {
    return this->topLeftX;
}

void Node::setTopLeft(float x, float y) {
    this->topLeftX = x;
    this->topLeftY = y;
}











