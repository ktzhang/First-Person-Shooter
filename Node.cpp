#include "Node.h"
#include <iostream>
using namespace std;

Node::Node() {

}

Node::~Node() {

}

bool Node::hasParent() {
	return parent != nullptr;
}

Node* Node::getParent() {
	return parent;
}

void Node::setParent(Node* node) {
	parent = node;
}