#pragma once

#include <string>
#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>
#include "Header.h"
#include "Geode.h"
#include <gl\glut.h>

using namespace std;
class Reader : public Geode
{
	float* maxes;
	float* mins;
	float* means;
	Color color;

	string fileName;
	vector<Vector3> positionVectors;
	vector<Color> vectorColors;
	vector<Vector4> normalVectors;

	vector<Triangle> triangleVectors;

	void populateFiles();
	void calculateMeanPosition();

public:
	Reader() {};
	Reader::Reader(std::string input, Color color = Color{ 0.9, 0.3, 0.9 }) : fileName(input) {
		maxes = new float[3]{FLT_MIN, FLT_MIN, FLT_MIN};
		mins = new float[3]{FLT_MAX, FLT_MAX, FLT_MAX};
		means = new float[3];
		populateFiles();
		calculateMeanPosition();
		this->color = color;
	};
	~Reader();

	void render();

	float Reader::getMeanX() {
		return means[0];
	}

	float Reader::getMeanY() {
		return means[1];
	}

	float Reader::getMeanZ() {
		return means[2];
	}

	float* Reader::getMeans() {
		return means;
	}

	float* Reader::getMaxes() {
		return maxes;
	}

	vector<Triangle> Reader::getTriangles() {
		return triangleVectors;
	}

	float* Reader::getMins() {
		return mins;
	}


	float Reader::getNumPoints() {
		return positionVectors.size();
	}

	vector<Vector3> getPosVectors() {
		return positionVectors;
	}

	vector<Vector4> getNormalVectors() {
		return normalVectors;
	}
	vector<Color> getColors() {
		return vectorColors;
	}
};

