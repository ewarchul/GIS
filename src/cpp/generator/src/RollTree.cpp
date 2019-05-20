//
// Created by Konstantin on 20.04.2019.
//

#include "generator/RollTree.h"

SNode RollTree::selectNode() const {
    // generate number
    //search
   
    RollNode* rnode = root;
    RollNodeLeaf* result;
    while((result = dynamic_cast<RollNodeLeaf*>(rnode)) == nullptr) { 
        ulong&& limit = rollSeed(rnode);
        if(limit <= rnode->getLWeight())
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
    return r->getLong(node->weight);
}

RollTree::~RollTree() {
    delete root;
}

RollTree::RollTree() : r(new RandomImp), root(new RollNode()) {}

void RollTree::deleteNode(RollNodeLeaf *node) {
    
    // find node in a bucket
    auto it = buckets.find(node->bucket->bucketDegree);
    buckets.erase(it);

    RollNode* parent = node->parent;
    RollNode* sibling = nullptr;
    if (parent->leftChild == node) {
        parent->leftChild = nullptr;
        sibling = parent->rightChild;
	}
	else {
        parent->rightChild = nullptr;
        sibling = parent->leftChild;
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
        else
            grandParent->rightChild = sibling;
        
        sibling->parent = grandParent;
        updateAncestorWeights(sibling);
    }
}

void RollTree::confirmSelection() {
    // we know what is the node & bucket
    updateTree(selectedNode, selectedLeaf);
}

void RollTree::updateTree(SNode &node, RollNodeLeaf *leaf) {
    
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
    Bucket& bucket = *(node->bucket);
    
    const ulong newWeight = bucket.getSize() * bucket.bucketDegree;
	node->weight = newWeight;
    updateAncestorWeights(node);
}


inline void RollTree::updateAncestorWeights(RollNode *node) {
    while(node->parent != nullptr) { // reaching root
        node = node->parent;
        updateNodeWeight(node);
    }
}

void RollTree::insertBucket(SNode &vNode, int degree) {
    // create bucket
    RollNodeLeaf* leaf = new RollNodeLeaf(degree);
	buckets[degree] = leaf;
    leaf->bucket->addNode(vNode);

    // insert bucket in a tree
    RollNode* node = this->root;
    RollNodeLeaf* result = nullptr;

    while((result = dynamic_cast<RollNodeLeaf*>(node)) == nullptr) {
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
        if(node->rightChild->weight >= node->leftChild->weight)
            node = node->leftChild;
        else
            node = node->rightChild;
    }

    if(result != nullptr) {
        auto *branchNode = new RollNode();
		branchNode->parent = node->parent;

		branchNode->leftChild = node;
		node->parent = branchNode;
		
		branchNode->rightChild = leaf;
		leaf->parent = branchNode;

		RollNode *parent = branchNode->parent;
		if (parent->leftChild == node)
			parent->leftChild = branchNode;
		else
			parent->rightChild = branchNode;
    }
    updateWeights(leaf);
}

void RollTree::insertNode(SNode &node, int degree) {
    RollNodeLeaf* newBucketNode = buckets[degree];
    // create bucket if absent
    if(newBucketNode == nullptr) {
        insertBucket(node, degree);
    } else {
        // add node to bucket
        Bucket& newBucket = *(newBucketNode->bucket);
        newBucket.addNode(node);
        updateWeights(newBucketNode);
    }
}



