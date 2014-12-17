#include <math.h>

#include "Matrix4.h"

using namespace std;

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4::Matrix4(double n[4][4]) {
	for (int i = 0; i<4; ++i)
	{
		for (int j = 0; j<4; ++j)
		{
			m[i][j] = n[i][j];
		}
	}
}

Matrix4::Matrix4(double n[16]) {
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++) {
			m[i][j] = n[i * 4 + j];
		}
	}
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) {
	Matrix4 n;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int x = 0; x < 4; x++){
				n.m[j][i] += this->m[x][i] * m2.m[j][x];
			}
		}
	}
	return n;
}


Vector4 Matrix4::operator*(const Vector4& v) { // : multiply matrix with vector
	Vector4 v2(0, 0, 0, 0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			v2.m[i] += this->m[j][i] * v.m[j];
			//std::cout << "\n adding " << this->m[j][i] << " with " << v.m[j];
		}
	}

	return v2;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}



// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}


// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

void Matrix4::makeRotateX(double angle) {
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[1][1] = cos(angle);
	m[2][1] = sin(angle);
	m[1][2] = -sin(angle);
	m[2][2] = cos(angle);
}


// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateZ(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[1][0] = sin(angle);
	m[0][1] = -sin(angle);
	m[1][1] = cos(angle);
}

// : Make a rotation matrix about an arbitrary axis
void Matrix4::makeRotate(double angle, const Vector3& axis) {
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	double t = 1 - cos(angle);
	double s = sin(angle);
	double c = cos(angle);
	double X = axis.m[0];
	double Y = axis.m[1];
	double Z = axis.m[2];

	identity();
	m[0][0] = t*X*X + c;
	m[0][1] = t*X*Y - s*Z;
	m[0][2] = t*X*Z + s*Y;
	m[1][0] = t*X*Y + s*Z;
	m[1][1] = t*Y*Y + c;
	m[1][2] = t*Y*Z - s*X;
	m[2][0] = t*X*Z - s*Y;
	m[2][1] = t*Y*Z + s*X;
	m[2][2] = t*Z*Z + c;
}

// : make a non - uniform scaling matrix
void Matrix4::makeScale(double sx, double sy, double sz) {
	identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
}

// : make a translation matrix
void Matrix4::makeTranslate(double tx, double ty, double tz) {
	identity();
	m[3][0] = tx;
	m[3][1] = ty;
	m[3][2] = tz;
}

void Matrix4::print(std::string& comment) {
	comment.append("\n| "
		+ to_string(m[0][0]) + " "
		+ to_string(m[1][0]) + " "
		+ to_string(m[2][0]) + " "
		+ to_string(m[3][0]) + " |\n| "
		+ to_string(m[0][1]) + " "
		+ to_string(m[1][1]) + " "
		+ to_string(m[2][1]) + " "
		+ to_string(m[3][1]) + " |\n| "
		+ to_string(m[0][2]) + " "
		+ to_string(m[1][2]) + " "
		+ to_string(m[2][2]) + " "
		+ to_string(m[3][2]) + " |\n| "
		+ to_string(m[0][3]) + " "
		+ to_string(m[1][3]) + " "
		+ to_string(m[2][3]) + " "
		+ to_string(m[3][3]) + " |");
}

void Matrix4::printToSt() {
	std::string comment;
	comment.append("\n| "
		+ to_string(m[0][0]) + " "
		+ to_string(m[1][0]) + " "
		+ to_string(m[2][0]) + " "
		+ to_string(m[3][0]) + " |\n| "
		+ to_string(m[0][1]) + " "
		+ to_string(m[1][1]) + " "
		+ to_string(m[2][1]) + " "
		+ to_string(m[3][1]) + " |\n| "
		+ to_string(m[0][2]) + " "
		+ to_string(m[1][2]) + " "
		+ to_string(m[2][2]) + " "
		+ to_string(m[3][2]) + " |\n| "
		+ to_string(m[0][3]) + " "
		+ to_string(m[1][3]) + " "
		+ to_string(m[2][3]) + " "
		+ to_string(m[3][3]) + " |");
	std::cout << comment;
}