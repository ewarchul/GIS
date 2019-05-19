//
// Created by Konstantin on 19.04.2019.
//

#ifndef BAGENERATOR_NODE_H
#define BAGENERATOR_NODE_H

#include <memory>

class Node {
public:
	inline virtual long getLabel() const = 0;
	inline virtual bool operator ==(const Node& other) { return this->getLabel() == other.getLabel();  }
    bool operator !=(const Node& r) { return !(*this == r);}
};

typedef std::shared_ptr<Node> SNode;

#endif //BAGENERATOR_NODE_H
