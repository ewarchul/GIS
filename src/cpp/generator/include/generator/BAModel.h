//
// Created by Konstantin on 16.04.2019.
//

#ifndef BAGENERATOR_BAMODEL_H
#define BAGENERATOR_BAMODEL_H

#include "graph/GraphImpOur.h"
#include "RollTree.h"
#include <memory>
#include <set>
class BAModel {
    std::shared_ptr<Graph> g;
    std::unique_ptr<PreferentialAttachement> roulette;

    inline void initModel(int m0);
    inline void generateGraph(int N, int m, int m0);
    inline void connectNode(SNode &d, std::set<SNode> &);
public:
    Graph* generateBAGraph(int N, int m, int m0);
    BAModel() {
        g = std::make_shared<GraphImpOur>();
        roulette = std::unique_ptr<PreferentialAttachement>(new RollTree);
    }
};

#endif //BAGENERATOR_BAMODEL_H
