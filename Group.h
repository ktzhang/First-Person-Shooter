#pragma once
#include "Node.h"
#include <string>
#include <vector>

using namespace std;

class Group : public Node
{
protected:
	vector<Node*> children;
public:
	Group();
	bool hasChildren();
	vector<Node*> getChildren();
	void addChild(Node* child);
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	~Group(){};
};



