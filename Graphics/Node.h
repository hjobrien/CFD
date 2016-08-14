//
// Created by Hank O'Brien on 7/4/16.
//

#ifndef CFD_NODE2_H
#define CFD_NODE2_H


#include <string>
#include <vector>


struct clonable {
    virtual ~clonable() {}
    virtual clonable* clone() const = 0;
};

class Node : public clonable{

public:
    virtual void update() = 0;
    virtual bool canMerge() = 0;
    virtual Node* clone() const = 0;
    virtual std::string toString() const = 0;

    const std::vector<Node*>& getSubNodesAsList() const;

    float getSize();
    void setSize(float size);
    void setTopLeft(float x, float y);

    float getX();
    float getY();

    Node* topLeft;
    Node* topRight;
    Node* bottomRight;
    Node* bottomLeft;

private:
    float topLeftX, topLeftY;
    float size;

};


#endif //CFD_NODE2_H
