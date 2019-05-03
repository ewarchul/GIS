#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "vertex.h"
int Vertex::vertexId;
Vertex::Vertex(){
	vertexId++;
	label = vertexId;
	vertexDeg = 0;
}
void Vertex::vertexInfo(){
	std::cout<<"Vertex id := "<<this->label<<"\t Vertex deg := "<<this->vertexDeg<<"\n";
}

void Vertex::degInc(int incval){
	this->vertexDeg = this->vertexDeg + incval;
}
void Vertex::degDec(int decval){
	this->vertexDeg = this->vertexDeg - decval;
}
bool operator==(const Vertex &lhs, const Vertex &rhs){
	if(lhs.label == rhs.label)
		return true;
	else
		return false;
}
bool operator!=(const Vertex &lhs, const Vertex &rhs){
	if(lhs.label != rhs.label)
		return true;
	else
		return false;
}
