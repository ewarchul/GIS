//
// Created by Konstantin on 19.04.2019.
//

#include "generator/Bucket.h"
#include <iostream>

std::vector<SNode>::const_iterator Bucket::findNode(SNode &node) const {
    return std::find_if(nodes.begin(), nodes.end(), [&node](const SNode& mNode) {
        return *mNode == *node;
    });
}

void Bucket::removeNode(SNode &n) {
    nodes.erase(findNode(n));
}

bool Bucket::addNode(SNode &n) {
    nodes.push_back(n);
    return true;
}


SNode Bucket::randomSelection(const std::unique_ptr<Random> &random) const {
    unsigned long res = random->getLong(nodes.size());
	std::cout << " s " << nodes.size() <<  " r " << res << std::endl;
    return nodes[res];
}


