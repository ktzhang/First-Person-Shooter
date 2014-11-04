#include "Reader.h"
using namespace std;

Reader::Reader(std::string input)  
{
	this->fileName = input;
	populateFiles();
	convertToVectors();
}

void Reader::populateFiles()
{
	if (this->fileName.empty()) return;
	float buffer;
	FILE * fp;
	fp = fopen(this->fileName.c_str(), "r+");
	while (fscanf(fp, "%f ", &buffer) != EOF) {
		imageNums.push_back(buffer);
	}
	fclose(fp);
}

void Reader::convertToVectors()
{
	for (std::vector<float>::size_type i = 0; i < imageNums.size(); i += 6) {
		if (imageNums[i] > maxX) {
			maxX = imageNums[i];
		}
		if (imageNums[i + 1] > maxY) {
			maxY = imageNums[i + 1];
		}
		if (imageNums[i + 2] > maxZ) {
			maxZ = imageNums[i + 3];
		}
		if (imageNums[i] < minX) {
			minX = imageNums[i];
		}
		if (imageNums[i + 1] < minY) {
			minY = imageNums[i + 1];
		}
		if (imageNums[i + 2] < minZ) {
			minZ = imageNums[i + 2];
		}

		normalVertices.push_back(imageNums[i + 3]);
		normalVertices.push_back(imageNums[i + 4]);
		normalVertices.push_back(imageNums[i + 5]);

		positionVertices.push_back(imageNums[i]);
		positionVertices.push_back(imageNums[i + 1]);
		positionVertices.push_back(imageNums[i + 2]);
	}
	calculateMean();
}

void Reader::calculateMean() 
{
	this->meanX = (this->maxX + this->minX) / 2;
	this->meanY = (this->maxY + this->minY) / 2;
	this->meanZ = (this->maxZ + this->minZ) / 2;

}

Reader::~Reader()
{
}
