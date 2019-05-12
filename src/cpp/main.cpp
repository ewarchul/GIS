#include <iostream>
#include "generator/BAModel.h"
using namespace std;
int main()
{
    BAModel m;
    std::cout << "h1";
    GraphImpOur g;
    m.generateBAGraph(1000000, 2, 2);
//    lemon::ListGraph& g = static_cast<GraphImpOur*>(m.generateBAGraph(20, 2, 4))->mGraph;
//
//   // g.addEdge(c,a);
//    //std::cout << "deg" << (a == a);
//    for (ListGraph::NodeIt n(g); n != INVALID; ++n) {
//        int cnt = 0;
//        for (ListGraph::IncEdgeIt e(g, n); e != INVALID; ++e) {
//            cnt++;
//        }
//        std::cout << "deg(" << g.id(n) << ") = " << cnt << std::endl;
//    }
//    cout << "We have a directed graph with " << countNodes(g) << " nodes "
//         << "and " << countArcs(g) << " arc." << endl;
    return 0;
}