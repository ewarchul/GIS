#ifndef VERTEX_H
#define VERTEX_H

#include "Node.h"

class Vertex : public Node {
public:
	static int vertexId;
	int label;
	int vertexDeg;
	std::set<int> adjNodes;
	void vertexInfo();
	void degInc(int incval);
	void degDec(int decval);
	//friend bool operator==(const Vertex &lhs, const Vertex &rhs);
	//friend bool operator!=(const Vertex &lhs, const Vertex &rhs);
	Vertex();

	inline long getLabel() const override { return label; }
};

#endif
