#include "Reader.h"
using namespace std;

//Reader::Reader(std::string input)
//{
//	fileName = input;
//	populateFiles();
//	convertToVectors();
//}

void Reader::populateFiles()
{
	if (fileName.empty()) return;
	float buffer;
	FILE * fp;
	fp = fopen(fileName.c_str(), "r+");
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

		normalVectors.push_back(Vector4(imageNums[i + 3], imageNums[i + 4], imageNums[i + 5], 1));

		positionVertices.push_back(imageNums[i]);
		positionVertices.push_back(imageNums[i + 1]);
		positionVertices.push_back(imageNums[i + 2]);

		positionVectors.push_back(Vector4(imageNums[i], imageNums[i + 1], imageNums[i + 2], 1));
	}
	calculateMean();
}

void Reader::calculateMean()
{
	meanX = (maxX + minX) / 2;
	meanY = (maxY + minY) / 2;
	meanZ = (maxZ + minZ) / 2;

}

Reader::~Reader()
{
}
