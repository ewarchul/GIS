//
// Created by Konstantin on 16.04.2019.
//
#include "generator/BAModel.h"
#include <iostream>
Graph* BAModel::generateBAGraph(const int N, const int m, const int m0) {
    initModel(m0);

    generateGraph(N, m, m0);

    return g.get();
}

void BAModel::connectNode(SNode &d, std::set<SNode> &blackList) {
    bool isSelected = false;
    while(!isSelected) {
        // select vertext based on roulette
        SNode s = roulette->selectNode();
        if(blackList.find(s) == blackList.end()) { // what if an infinite loop? replace with for?
            g->addArc(s, d);
            blackList.insert(s);
            roulette->confirmSelection();
            isSelected = true;
        }
    }

}

void BAModel::initModel(int m0) { // initialize graph
    std::vector<SNode> createdNodes;
    for(int i = 0; i < m0; ++i) {
        SNode&& n = g->addNode();
        std::for_each(createdNodes.begin(), createdNodes.end(), [&](SNode&  x) {
            g->addArc(n, x);
        });
        createdNodes.push_back(n);
    }
    // update pref attachement buckets
    std::for_each(createdNodes.begin(), createdNodes.end(), [&](SNode& x) {
        roulette->insertNode(x, m0);
    });
}

void BAModel::generateGraph(const int N, const int m, const int m0) {
    for(int i = m0 + 1; i <= N; i++) {
        // create node
        SNode&& n = g->addNode();
        //connect to m nodes
        std::set<SNode> connectedNodes; // already connected nodes, can't connect twice the same node
        for(int j = 0; j < m; j++) {
            connectNode(n, connectedNodes);
        }
        // add new node to corresponding bucket
		roulette->insertNode(n, m);

    }
}
