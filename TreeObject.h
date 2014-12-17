#pragma once
#include "MatrixTransform.h"
#include "Group.h"
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>
#include "Vector3.h"
#include "Group.h"
#include <GL/glut.h>

class TreeObject :
	public Group {
	double ratioStep;
	double angle;
	//Map containing all the rules
	std::unordered_map<char, string> rulesMap;
	int depth;
	double length;
	int maxDepth;
	string axiom;
	Vector3 currentPos;
	Group* treeObj;
	int glutIndex;


private:
	//Draws each rule 
	int TreeObject::drawRule(string currentRule);
	int TreeObject::drawChar(char drawLetter, int depth, vector<Matrix4>& transformationStack, double& ratio);
	MatrixTransform TreeObject::drawBranch(Matrix4 trans, char letter, double ratio);
	Matrix4 TreeObject::convertVectorToMatrix(vector<Matrix4> transformationStack);
public:
	TreeObject();
	TreeObject(int maxDepth, double length, double angle, double ratioStep);

	// Initializing tree with a map
	void setRulesMap(std::unordered_map<char, pair<vector<char>, double>>);
	void addRule(char ruleLetter, string rule, double length);
	vector<char> convertStringtoVector(string input);
	void TreeObject::update(Matrix4 worldMatrix);
	void TreeObject::draw(Matrix4 matrix);
	void TreeObject::setMaxDepth(int depth);
	void TreeObject::setAxiom(string ax);
	
	void TreeObject::prerender();
	
	string TreeObject::generateFinalRule(string start, int depth);
	~TreeObject();
};

