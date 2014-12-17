#pragma once
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
class ZBuffer
{
	int sizeX;
	int sizeY;
	vector<vector<double>> zBuffer;

public:
	ZBuffer();
	ZBuffer(const int sizeX, const int sizeY) : sizeX(sizeX), sizeY(sizeY) {
		zBuffer.resize(sizeX);
		for (int i = 0; i < sizeX; ++i) {
			zBuffer[i].resize(sizeY);
		}
		resetBuffer();
	};
	double getValue(int x, int y);
	void setValue(int x, int y, double value);
	bool ZBuffer::checkAndReplace(int x, int y, double value);

	~ZBuffer();
	void resetBuffer();

};

