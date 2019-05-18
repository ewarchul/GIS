#ifndef __GRAPH__
#define __GRAPH__

#include <set>
#include <map>
#include "Graph.h"
#include "NodeImpOur.h"

class GraphImpOur : public Graph {
private:
	std::vector<Vertex> vertexList;
	std::map<int,std::set<int>> edgesList;
public:
	bool addVertex(Vertex v);
	bool isVertex(Vertex &v);
	bool addEdge(Vertex &v, Vertex &u);
	void vertexEdges(Vertex const &v);
	void graphInfo();
	bool delVertex(Vertex &v);
	bool delEdge(const int& from, const int& to);
	bool isConnected();
	friend std::ostream &operator<<(std::ostream &output, GraphImpOur &G);
	GraphImpOur();

	SNode addNode() override;

	void addArc(SNode &node, SNode &sNode) override;
};

#endif
