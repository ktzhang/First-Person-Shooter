#include "Group.h"


Group::Group()
{
}

bool Group::hasChildren() {
	return children.size() > 0;
}

void Group::addChild(Node* child) {
	children.push_back(child);
	child->setParent(this);
}

vector<Node*> Group::getChildren() {
	return children;
}

void Group::draw(Matrix4 matrix) {
	for (vector<Node*>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->draw(matrix);
	}
}

void Group::drawBoundingSpheres(Matrix4 worldMatrix) {
	for (vector<Node*>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->drawBoundingSpheres(worldMatrix);
	}
}


void Group::update(Matrix4 worldMatrix) {
	for (vector<Node*>::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->update(worldMatrix);
	}
}