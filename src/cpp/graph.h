#ifndef __GRAPH__
#define __GRAPH__
class Graph{
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
	friend std::ostream &operator<<(std::ostream &output, Graph &G);
	Graph();
};

#endif
