#pragma once

#include <string>
#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>


using namespace std;
class Reader
{
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	float meanX;
	float meanY;
	float meanZ;

	string fileName;
	vector<float> imageNums; // Stores the number of images in a vector

	vector<float> normalVertices;
	vector<float> positionVertices;


	vector<Vector4> positionVectors;
	vector<Vector4> normalVectors;

	void populateFiles();
	void convertToVectors();
	void calculateMean();

public:
	Reader() {};
	Reader::Reader(std::string input) : fileName(input){
		populateFiles();
		convertToVectors();
	};
	~Reader();

	float Reader::getMeanX() {
		return meanX;
	}

	float Reader::getMeanY() {
		return meanY;
	}

	float Reader::getMeanZ() {
		return meanZ;
	}

	float Reader::getSize() {
		std::cout << "Max x " << maxX << " Min X" << minX;
		return maxX - minX;
	}

	float Reader::getNumPoints() {
		return positionVectors.size();
	}

	vector<float> getPosVertices() {
		return positionVertices;
	}

	vector<float> getNormalVertices() {
		return normalVertices;
	}

	vector<Vector4> getPosVectors() {
		return positionVectors;
	}

	vector<Vector4> getNormalVectors() {
		return normalVectors;
	}
};

