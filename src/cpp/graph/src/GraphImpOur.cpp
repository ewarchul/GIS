#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include "graph/NodeImpOur.h"
#include "graph/GraphImpOur.h"

GraphImpOur::GraphImpOur() : vertexList{}, edgesList{} {}

bool GraphImpOur::addVertex(Vertex v){
	std::size_t org_size{this->vertexList.size()};
	this->vertexList.push_back(v);
	return this->vertexList.size() == org_size + 1;
}
bool GraphImpOur::isVertex(Vertex &v){
	if(std::find(this->vertexList.begin(), this->vertexList.end(), v) != this->vertexList.end()){
		return true;
	}
	return false;
}


bool GraphImpOur::addEdge(Vertex &v, Vertex &u) { // todo consider uncheck node
	if(!v.adjNodes.count(u.label)){
		v.adjNodes.insert(u.label);
		u.adjNodes.insert(v.label);
	}
	v.degInc(1);
	u.degInc(1);
	this->edgesList[v.label]=v.adjNodes;
	this->edgesList[u.label]=u.adjNodes;
	return true;
}

void GraphImpOur::vertexEdges(Vertex const &v){
	std::cout<<"Vertex "<<v.label<<" has edges with nodes: [ ";
	for(auto i: v.adjNodes)
		std::cout<<i<<" ";
	std::cout<<"]\n";
}
void GraphImpOur::graphInfo(){
	for(auto i=this->edgesList.begin(); i != this->edgesList.end(); i++){
		std::cout<<"Vertex ";
		std::cout<<i->first<<" has edges with nodes [ ";
		for(auto k: i->second)
			std::cout<<k<<" ";
		std::cout<<"] and has degree "<<i->second.size()<<".\n";
	}
}

std::ostream &operator<<(std::ostream &output, GraphImpOur &G){
	for(auto i=G.edgesList.begin(); i != G.edgesList.end(); i++){
		for(auto k: i->second){
			output<<i->first-1<<" ";
			output<<k-1<<"\n";
		}
	}
	return output;
}

SNode GraphImpOur::addNode() {
	auto vertex = std::make_shared<Vertex>();
	this->addVertex(*vertex);
	return vertex;
}

void GraphImpOur::addArc(SNode &node, SNode &sNode) {
	this->addEdge(*static_cast<Vertex*>(node.get()), *static_cast<Vertex*>(sNode.get()));
}

