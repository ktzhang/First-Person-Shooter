#ifndef _GEODE_H_
#define _GEODE_H_

#include "Node.h"
#include "Matrix4.h"

using namespace std;
extern Vector3 planes[12];
extern int cullingEnabled;

class Geode : public Node {
	int shouldRenderObj = 1;
public:
	Matrix4 modelview;
	Geode(){};
	void setModelView(Matrix4 matrix);
	void unsetModelView();
	virtual void draw(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	virtual void render() = 0;
	virtual void update(Matrix4 matrix);
	void shouldRender(Matrix4 transformMatrix);
	~Geode(){};
};

#endif