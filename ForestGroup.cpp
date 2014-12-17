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

void ForestGroup::draw(Matrix4 matrix) {
	double treeShrinkFactor = 0.0005;
	Matrix4 treeShrinkMatrix;
	treeShrinkMatrix.identity();
	treeShrinkMatrix.makeScale(treeShrinkFactor, treeShrinkFactor, treeShrinkFactor);
	
	Matrix4 treeMoveMatrix;
	for (int i = 0; i < numTrees; i++) {
		treeMoveMatrix.makeTranslate(forestX[i], 0, forestY[i]);
		Matrix4 finalMatrix;
		finalMatrix = treeMoveMatrix * treeShrinkMatrix;

		MatrixTransform *treeTrans = new MatrixTransform(finalMatrix);
		treeTrans->addChild(treeObj);
		forest->addChild(treeTrans);
	}

	forest->draw(matrix);
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
