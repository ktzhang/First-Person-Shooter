#include "TreeObject.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "cube.h"
#include <string.h>
#include "Cylinder.h"
#include <unordered_map>
#include <vector>

using namespace std;


TreeObject::TreeObject() {
	angle = 30;
	depth = 0;
	maxDepth = 1;
	length = 1;
	ratioStep = 1;
	treeObj = new Group();
}

TreeObject::TreeObject(int maxDepth, double length, double angle, double ratioStep) {
	this->angle = angle;
	depth = 0;
	this->length = length;
	this->maxDepth = maxDepth;
	this->ratioStep = ratioStep;
	treeObj = new Group();
}

//Parsing the string with the input characters
std::vector<char> TreeObject::convertStringtoVector(string input){
	return std::vector<char>(input.begin(), input.end());
}

void TreeObject::setAxiom(string ax) {
	axiom = ax;
}

void TreeObject::addRule(char ruleLetter, string rule, double length) {
	//vector<char> ruleVector = convertStringtoVector(rule);
	//string pair = make_pair(ruleVector, length);
	rulesMap.insert(make_pair(ruleLetter, rule));
}


int TreeObject::drawRule(string currentRule) {
	vector<Matrix4> transformationStack;
	Matrix4 iden = Matrix4();
	iden.identity();
	transformationStack.push_back(iden);

	int errors = 0;
	int count = 0;
	// Iterating though the rule vector
	stack<vector<Matrix4>> matrixStack;
	double ratio = 1.0;
	double savedRatio = 1;

	for (string::iterator it = currentRule.begin(); it != currentRule.end(); ++it) {
		if (*it == '[') {
			matrixStack.push(transformationStack);
			savedRatio = ratio;
		}
		else if (*it == ']') {
			transformationStack = matrixStack.top();
			matrixStack.pop();
			ratio = savedRatio;
		}
		else if (!drawChar(*it, depth, transformationStack, ratio)) errors += 1;
		count++;
	}
	return errors == 0;
}


string TreeObject::generateFinalRule(string startRule, int depth) {
	if (depth == maxDepth) {
		return startRule;
	}

	string tempString;
	for (std::string::iterator it = startRule.begin(); it != startRule.end(); ++it) {
		std::unordered_map<char, string>::const_iterator got = rulesMap.find(*it);
		//Didn't find it
		if (got == rulesMap.end()) {
			tempString += *it;
		}
		// Found it
		else {
			tempString += rulesMap.at(*it);
		}
	}
	return generateFinalRule(tempString, depth + 1);
}


void TreeObject::setMaxDepth(int depth) {
	maxDepth = depth;
}

// Returns 0 if error
int TreeObject::drawChar(char drawLetter, int depth, vector<Matrix4>& transformationStack, double& ratio) {
	int shouldDraw = depth == maxDepth;
	Matrix4 rotationMatrix;
	rotationMatrix.identity();

	switch (drawLetter) {
	// if space, exit
	case ' ': 
		break;
	//Turn left by angle amount
	case '+':
		rotationMatrix.makeRotateX(angle);
		transformationStack.push_back(rotationMatrix);

		break;
	case '-':
		rotationMatrix.makeRotateX(-angle);
		transformationStack.push_back(rotationMatrix);
		break;
	case '&':
		rotationMatrix.makeRotateY(angle);
		transformationStack.push_back(rotationMatrix);
		break;

	case '^':
		rotationMatrix.makeRotateY(-angle);
		transformationStack.push_back(rotationMatrix);
		break;

	case '>':
		rotationMatrix.makeRotateZ(angle);
		transformationStack.push_back(rotationMatrix);
		break;

	case '<':
		rotationMatrix.makeRotateZ(-angle);
		transformationStack.push_back(rotationMatrix);
		break;


	default:
		ratio *= ratioStep;
		drawBranch(convertVectorToMatrix(transformationStack), drawLetter, ratio);

		Matrix4 shiftMatrix;
		shiftMatrix.identity();
		//TODO: change length
		shiftMatrix.makeTranslate(0, length * ratio, 0);
		transformationStack.push_back(shiftMatrix);
		break;
	}
	return 1;
}

Matrix4 TreeObject::convertVectorToMatrix(vector<Matrix4> transformationStack) {
	Matrix4 finalMatrix;
	finalMatrix.identity();
	for (std::vector<Matrix4>::iterator it = transformationStack.begin(); it != transformationStack.end(); ++it) {
		finalMatrix = finalMatrix * (*it);
	}
	return finalMatrix;
}


MatrixTransform TreeObject::drawBranch(Matrix4 trans, char letter, double ratio) {
	Matrix4 rotateCyl;
	rotateCyl.makeRotateX(90);
	double radius = 1;
	trans = trans * rotateCyl;
	MatrixTransform* transform = new MatrixTransform(trans);
	transform->addChild(new Cylinder(length* ratio, radius, ratio, ratioStep));
	treeObj->addChild(transform);
	Matrix4 tras;
	trans.identity();
	//treeObj->draw(trans);
	return *transform;
}

void TreeObject::prerender() {
	glutIndex = glGenLists(1);
	glNewList(glutIndex, GL_COMPILE);
		Matrix4 ident = Matrix4();
		ident.identity();
		vector<Matrix4> transformationStack;
		transformationStack.push_back(ident);
		string finalRule = generateFinalRule(axiom, depth);
		drawRule(finalRule);
		treeObj->draw(ident); //Since its prerendered, pass in ident
	glEndList();
}

/* 
 * Sort of hacky method to render the tree object, as it doesnt draw the objects in 
 * draw but draws it in prerender.
 */
void TreeObject::draw(Matrix4 matrix) {
	glPushMatrix();
	glMultMatrixd(matrix.getPointer());
	glCallList(glutIndex);
	glPopMatrix();
}

void TreeObject::update(Matrix4 worldMatrix) {
	treeObj->update(worldMatrix);
}


TreeObject::~TreeObject()
{
	delete treeObj;

}
