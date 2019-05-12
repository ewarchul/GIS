//
// Created by Konstantin on 20.04.2019.
//

#include "generator/RollTree.h"

SNode RollTree::selectNode() const {
    // generate number
    //search
    std::cout << "sel node" << std::endl;
    RollNode* rnode = root;
    RollNodeLeaf* result;
    while((result = dynamic_cast<RollNodeLeaf*>(rnode)) == nullptr) { //todo fix?
        unsigned long limit = rollSeed(rnode);
        if(limit < rnode->getLWeight())
            rnode = rnode->leftChild;
        else
            rnode = rnode->rightChild;
    }

    SNode chosenNode =  result->bucket->randomSelection(r);
    // wait for select confirmation
    this->selectedNode = chosenNode;
    this->selectedLeaf = result;

    return chosenNode;
}

unsigned long RollTree::rollSeed(const RollNode* node) const {
    std::cout << "roll seed" << std::endl;
    ulong rweight = 0;
    ulong lweight = 0;
    if(node->rightChild != nullptr)
        rweight = node->rightChild->weight;
	if (node->leftChild != nullptr)
		lweight = node->leftChild->weight;
    const unsigned long limit = lweight + rweight;
    std::cout << "roll done" << std::endl;
    return r->getLong(limit);
}

RollTree::~RollTree() {
    delete root;
}

RollTree::RollTree() : r(new RandomImp), root(new RollNode()) {}

void RollTree::deleteNode(RollNodeLeaf *node) {
    std::cout << "del node" << std::endl;
    // todo fix proper function
    auto it = buckets.find(node->bucket->bucketDegree);
    buckets.erase(it);

    RollNode* parent = node->parent;
    RollNode* sibling = nullptr;
    if(parent->leftChild == node) {
        parent->leftChild = nullptr;
        sibling = parent->rightChild;
    }
    else if(parent->rightChild == node) {
        parent->rightChild = nullptr;
        sibling = parent->leftChild;
    }
    else // todo debug fix
    {
        std::cout<<"WTF deleting";
    }
    // if root return
    if(parent == root) {
        updateNodeWeight(parent);
        return;
    }
    if(sibling != nullptr) {
        RollNode* grandParent = parent->parent;
        if(grandParent->leftChild == parent)
            grandParent->leftChild = sibling;
        else if(grandParent->rightChild == parent)
            grandParent->rightChild = sibling;
        else
            std::cout << "WTF sibling replacing";
        sibling->parent = grandParent;
        updateAncestorWeights(sibling);
    }
}

void RollTree::confirmSelection() {
    std::cout << "conf sel" << std::endl;
    // we know what is the node & bucket
    updateTree(selectedNode, selectedLeaf);
	std::cout << "conf sel done" << std::endl;
}

void RollTree::updateTree(SNode &node, RollNodeLeaf *leaf) {
    std::cout << "up tree" << std::endl;
    Bucket& oldBucket = *(leaf->bucket);
    // calc degree
    const int oldDegree = oldBucket.bucketDegree;
    // remove node from bucket
    oldBucket.removeNode(node);
    if(oldBucket.isEmpty())
        deleteNode(leaf);
    else {
        updateWeights(leaf);
    }
    // move node to the next bucket
    insertNode(node, oldDegree + 1);
}

void RollTree::updateWeights(RollNodeLeaf *node) {
    std::cout << " update";

    Bucket& bucket = *(node->bucket);
    
    const ulong newWeight = bucket.getSize() * bucket.bucketDegree;
	node->weight = newWeight;
    updateAncestorWeights(node);
}


void RollTree::updateAncestorWeights(RollNode *node) {
    std::cout << "update ancestors" << std::endl;
    while(node->parent != nullptr) { // reaching root
        node = node->parent;
        updateNodeWeight(node);
    }
}

void RollTree::insertBucket(SNode &vNode, int degree) {
    std::cout << "insert bucket" << std::endl;
    // create bucket
    RollNodeLeaf* leaf = new RollNodeLeaf(degree);

    buckets[degree] = leaf;
    leaf->bucket->addNode(vNode);

    // insert bucket in a tree
    RollNode* node = this->root;
    RollNodeLeaf* result = nullptr;
    std::cout << " insert1";

    while((result = dynamic_cast<RollNodeLeaf*>(node)) == nullptr) {
        std::cout << " while1";
        if(node->leftChild == nullptr) {
            node->leftChild = leaf;
            leaf->parent = node;
            break;
        }

        if(node->rightChild == nullptr) {
            node->rightChild = leaf;
            leaf->parent = node;
            break;
        }
        std::cout << " while2";
        if(node->rightChild->weight >= node->leftChild->weight)
            node = node->leftChild;
        else
            node = node->rightChild;
    }
    std::cout << " insert2";

    if(result != nullptr) {
        std::cout << " insert med node";
        auto *branchNode = new RollNode();
		branchNode->parent = node->parent;

		branchNode->leftChild = node;
		node->parent = branchNode;
		
		branchNode->rightChild = leaf;
		leaf->parent = branchNode;

		RollNode *parent = branchNode->parent;
		if (parent->leftChild == node)
			parent->leftChild = branchNode;
		else if (parent->rightChild == node)
			parent->rightChild = branchNode;
		else
			std::cout << "WTF insert bucket";
       /* branchNode->rightChild = node;
        branchNode->leftChild = leaf;
        leaf->parent = branchNode;
		result->parent = branchNode;

        RollNode *parent = node->parent;
        branchNode->parent = parent;
        if (parent->leftChild == node)
            parent->leftChild = branchNode;
        else
            parent->rightChild = branchNode;*/
    }
    updateWeights(leaf);
}

void RollTree::insertNode(SNode &node, int degree) {
    std::cout << "in node" << std::endl;
    RollNodeLeaf* newBucketNode = buckets[degree];
    std::cout << " insert";
    // create bucket if absent
    if(newBucketNode == nullptr) {
        insertBucket(node, degree);
    } else {
        // add node to bucket
        Bucket& newBucket = *(newBucketNode->bucket);
        newBucket.addNode(node);
        updateWeights(newBucketNode);
    }
    std::cout << " insert done";
}



