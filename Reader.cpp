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
	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	float r, g, b;  // vertex color
	int c1, c2;    // characters read from file
	float v1, v2, v3, n1, n2, n3;
	int d1, d2, d3, dn1, dn2, dn3;

	fp = fopen(fileName.c_str(), "rb");
	if (fp == NULL) { cerr << "error loading file" << endl; exit(-1); }

	while (!feof(fp)) {
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		if (c1 == '#') {
			fscanf(fp, "%*[^\n]\n", NULL);
			continue;
		}
		if ((c1 == 'v') && (c2 == ' ')) {
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			positionVectors.push_back(Vector3(x, y, z));
			vectorColors.push_back(Color{ r, g, b });
		}
		else if (c1 == 'v') {
			fscanf(fp, "%f %f %f", &x, &y, &z);
			normalVectors.push_back(Vector4(x, y, z, 1));
		}
		else if (c1 == 'f') {
			fscanf(fp, "%d%*2[ /]%d%*1[ ]%d%*2[ /]%d%*1[ ]%d%*2[ /]%d", &d1, &dn1, &d2, &dn2, &d3, &dn3);
			triangleVectors.push_back(Triangle{ { d1, d2, d3 }, { dn1, dn2, dn3 } });
		} 
		
	}
	fclose(fp);   // make sure you don't forget to close the file when done
}

void Reader::calculateMeanPosition()
{
	for (int k = 0; k < 3; k++) {
		means[k] = 0;
	}

	for (std::vector<Vector3>::iterator it = positionVectors.begin(); it != positionVectors.end(); ++it) {
		for (int i = 0; i < 3; i++) {
			double temp = it->m[i];
			if (temp > maxes[i])
				maxes[i] = temp;
			if (temp < mins[i])
				mins[i] = temp;
		}
	}
	for (int j = 0; j < 3; j++) {
		means[j] = (maxes[j] + mins[j]) / 2;
	}
}


void Reader::render() {
	glBegin(GL_TRIANGLES);
	vector<Vector3> posVectors = this->getPosVectors();
	vector<Vector4> normalVectors = this->getNormalVectors();
	vector<Triangle> triangleVectors = this->getTriangles();
	vector<Color> colors = this->getColors();
	for (std::vector<int>::size_type i = 0; i != triangleVectors.size(); i++) {
		int tempColor = triangleVectors[i].normal[0] - 1;
		double r = colors[tempColor].r;
		double g = colors[tempColor].g;
		double b = colors[tempColor].b;
		if (r < 0 || r > 1) {
			r = color.r;
		}
		if (g < 0 || g > 1) {
			g = color.g;
		}
		if (b < 0 || b > 1) {
			b = color.b;
		}
		glColor3f(r, g, b);
		for (int j = 0; j < 3; j++) {
			int iNormal = triangleVectors[i].normal[j] - 1;
			int iVector = triangleVectors[i].vector[j] - 1;
			glNormal3d(normalVectors[iNormal].m[0], normalVectors[iNormal].m[1], normalVectors[iNormal].m[2]);
			glVertex3d(posVectors[iVector].m[0], posVectors[iVector].m[1], posVectors[iVector].m[2]);
			//cout << "st:: " << posVectors[iVector].m[0] << " " << posVectors[iVector].m[1] << " " << posVectors[iVector].m[2] << "\n";
			//cout << normalVectors[iNormal].m[0] << " " << normalVectors[iNormal].m[1] << " " << normalVectors[iNormal].m[2] << "\n";
		}
	}
	glEnd();
}




Reader::~Reader()
{
	delete maxes;

}
