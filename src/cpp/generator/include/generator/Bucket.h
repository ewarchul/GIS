//
// Created by Konstantin on 19.04.2019.
//

#ifndef BAGENERATOR_BUCKET_H
#define BAGENERATOR_BUCKET_H

#include <vector>
#include <map>
#include <algorithm>
#include "graph/Node.h"
#include "Random.h"


class Bucket { // todo consider abstract
private:
    std::map<long, SNode> nodes; // todo consider set
   // std::vector<SNode>::const_iterator findNode(SNode& node) const;
public:
    const int bucketDegree;
    bool addNode(SNode &n);
    void removeNode(SNode &n);
    inline size_t getSize() const { return nodes.size(); }
    inline bool isEmpty() const { return nodes.empty(); }
    SNode randomSelection(const std::unique_ptr<Random>& random) const;

    Bucket(const int bucketDegree) : bucketDegree(bucketDegree) {}
};


#endif //BAGENERATOR_BUCKET_H
