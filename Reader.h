#pragma once

#include <string>
#include <vector>
class Reader
{
public:
	Reader(std::string input);
	~Reader();

private:
	float maxX = FLT_MAX;
	float maxY = FLT_MAX;
	float maxZ = FLT_MAX;

	float minX = FLT_MIN;
	float minY = FLT_MIN;
	float minZ = FLT_MIN;

	float meanX;
	float meanY;
	float meanZ;
	
	float getMeanX() {
		return meanX;
	}

	float getMeanY() {
		return meanY;
	}

	float getMeanZ() {
		return meanZ;
	}

	string fileName;
	vector<float> imageNums; // Stores the number of images in a vector

	vector<float> normalVertices;
	vector<float> positionVertices;


	void populateFiles();
	void convertToVectors();
	void calculateMean();
};

