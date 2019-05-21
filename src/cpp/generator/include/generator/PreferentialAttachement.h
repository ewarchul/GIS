//
// Created by Konstantin on 20.04.2019.
//

#ifndef BAGENERATOR_PREFERENTIALATTACHEMENT_H
#define BAGENERATOR_PREFERENTIALATTACHEMENT_H

#include "graph/Graph.h"
#include "graph/Node.h"

class PreferentialAttachement {
public:
	// select node from wheel
    virtual SNode selectNode() const = 0; 
	// confirm that selected node is valid
    virtual void confirmSelection() = 0;
	// insert new node to the wheel
    virtual void insertNode(SNode&, int degree) = 0;
};


#endif //BAGENERATOR_PREFERENTIALATTACHEMENT_H
