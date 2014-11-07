#include "ZBuffer.h"


ZBuffer::ZBuffer()
{
}

void ZBuffer::resetBuffer() {
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++) {
			zBuffer[i][j] = 1.0;
		}
	}
}

double ZBuffer::getValue(int x, int y) {
	return zBuffer[x][y];
}
void ZBuffer::setValue(int x, int y, double value) {
	zBuffer[x][y] = value;
}

bool ZBuffer::checkAndReplace(int x, int y, double value) {
	if (zBuffer[x][y] > value) {
		zBuffer[x][y] = value;
		return true;
	}
	else {
		return false;
	}
}


ZBuffer::~ZBuffer()
{
}
