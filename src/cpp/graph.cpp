#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include "vertex.h"
#include "graph.h"
Graph::Graph() : vertexList{}, edgesList{} {}
bool Graph::addVertex(Vertex v){
	std::size_t org_size{this->vertexList.size()};
	this->vertexList.push_back(v);
	if(this->vertexList.size() == org_size + 1)
		return true;
	else
		return false;
}
bool Graph::isVertex(Vertex &v){
	if(std::find(this->vertexList.begin(), this->vertexList.end(), v) != this->vertexList.end()){
		return true;
	}
	return false;
}
bool Graph::addEdge(Vertex &v, Vertex &u){
	if(this->isVertex(v) && this->isVertex(u)){
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
	else{
		std::cout<<"Missing vertex in graph: v = "<<this->isVertex(v)<<"\t u = "<<this->isVertex(u)<<".\n";
		return false;
	}
}
void Graph::vertexEdges(Vertex const &v){
	std::cout<<"Vertex "<<v.label<<" has edges with nodes: [ ";
	for(auto i: v.adjNodes)
		std::cout<<i<<" ";
	std::cout<<"]\n";
}
void Graph::graphInfo(){
	for(auto i=this->edgesList.begin(); i != this->edgesList.end(); i++){
		std::cout<<"Vertex ";
		std::cout<<i->first<<" has edges with nodes [ ";
		for(auto k: i->second)
			std::cout<<k<<" ";
		std::cout<<"] and has degree "<<i->second.size()<<".\n";
	}
}
std::ostream &operator<<(std::ostream &output, Graph &G){
	for(auto i=G.edgesList.begin(); i != G.edgesList.end(); i++){
		for(auto k: i->second){
			output<<i->first-1<<" ";
			output<<k-1<<"\n";
		}
	}
	return output;
}
