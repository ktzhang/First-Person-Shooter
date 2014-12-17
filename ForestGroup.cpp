#include "ForestGroup.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "cube.h"
#include "TreeObject.h"
#include <cstdlib>

extern TreeObject *treeObj;
extern double forestX[10];
extern double forestY[10];

using namespace std;


ForestGroup::ForestGroup() {
	forest = new Group();
	numTrees = 10;
}

void ForestGroup::prerender() {
	Matrix4 ident;
	ident.identity();

	glutIndex = glGenLists(1);
	glNewList(glutIndex, GL_COMPILE);
		double treeShrinkFactor = 0.0025;
		Matrix4 treeShrinkMatrix;
		treeShrinkMatrix.identity();
		treeShrinkMatrix.makeScale(treeShrinkFactor, treeShrinkFactor, treeShrinkFactor);

		Matrix4 treeMoveMatrix;
		Matrix4 treeRotateMatrix;
		for (int i = 0; i < numTrees; i++) {
			treeRotateMatrix.makeRotateY(forestX[i] * 360);
			treeMoveMatrix.makeTranslate(forestX[i], 0, forestY[i]);
			Matrix4 finalMatrix;
			finalMatrix = treeRotateMatrix * treeMoveMatrix * treeShrinkMatrix;

			MatrixTransform *treeTrans = new MatrixTransform(finalMatrix);
			treeTrans->addChild(treeObj);
			forest->addChild(treeTrans);
		}

		forest->draw(ident);
	glEndList();
}

void ForestGroup::draw(Matrix4 matrix) {
	glPushMatrix();
	glMultMatrixd(matrix.getPointer());
	glCallList(glutIndex);
	glPopMatrix();
}

void ForestGroup::update(Matrix4 worldMatrix) {
	forest->update(worldMatrix);
}

void ForestGroup::drawBoundingSpheres(Matrix4 worldMatrix) {
	forest->drawBoundingSpheres(worldMatrix);
}

ForestGroup::~ForestGroup() {
	delete forest;
}
