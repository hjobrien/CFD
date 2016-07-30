//
// Created by Hank O'Brien on 7/3/16.
//

#include <iostream>
#include "Graphics/Node.h"
#include "Graphics/Cell.h"

using std::cout;

int main(){
    Node* n = new Cell();
    n = n->update();
    cout << n->toString() << "/n";
    n = n->update();
    cout << n->toString();
    return 0;
}