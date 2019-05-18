//
// Created by Konstantin on 19.04.2019.
//

#ifndef BAGENERATOR_GRAPH_H
#define BAGENERATOR_GRAPH_H

#include "Node.h"
#include <iostream>
#include <vector>

class Graph {
public:
    virtual SNode addNode() = 0;
    virtual void addArc(SNode&, SNode&) = 0;
};


#endif //BAGENERATOR_GRAPH_H
