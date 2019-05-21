#ifndef ROLL_NODE_H
#define ROLL_NODE_H

class RollTree;

typedef unsigned long ulong;
//basic node of a tree
class RollNode {
	friend class RollTree;
protected:
	ulong weight;

	RollNode* parent;
	RollNode* leftChild;
	RollNode* rightChild;
public:
	virtual ~RollNode() {
		delete leftChild;
		delete rightChild;
	}

	inline ulong getLWeight() const {
		return  this->leftChild != nullptr ? this->leftChild->weight : 0;
	}

	inline ulong getRWeight() const {
		return  this->rightChild != nullptr ? this->rightChild->weight : 0;
	}

	RollNode() : weight(0), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
};

// leaf of a tree containing a bucket
class RollNodeLeaf : public RollNode {
	friend class RollTree;
private:
	std::unique_ptr<Bucket> bucket;

public:

	~RollNodeLeaf() {}

	RollNodeLeaf(const int nodeDegree) : RollNode(), bucket(new Bucket(nodeDegree)) {}
};

#endif // !ROLL_NODE_H

