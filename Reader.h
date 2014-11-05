#pragma once

#include <string>
#include <vector>
#include "Vector4.h"


using namespace std;
class Reader
{
	float maxX = FLT_MAX;
	float maxY = FLT_MAX;
	float maxZ = FLT_MAX;

	float minX = FLT_MIN;
	float minY = FLT_MIN;
	float minZ = FLT_MIN;

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

